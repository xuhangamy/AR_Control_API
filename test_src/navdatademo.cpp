#include <ardrone/config.h>
#include <ardrone/at/CommandId.h>
#include <ardrone/at/ATCmdGenerator.h>
#include <ardrone/basic/Mutex.h>
#include <ardrone/net/UdpClient.h>
#include <ardrone/basic/helper.h>
#include <ardrone/basic/basic_struct.h>
#include <ardrone/navdata/common.h>
#include <ardrone/navdata/state.h>
#include <ardrone/basic/kbpress.h>
#include <ardrone/basic/timer.h>
#include <iostream>
#include <iomanip>
using namespace std;
using namespace whu;
using namespace whu::ardrone;

#pragma comment(lib,"ARDrone.lib")

UdpClient* recvClient;
UdpClient* atClient;
CommandId& cmdid = CommandId::Create();
ATCmdGenerator& gen = ATCmdGenerator::Create(&cmdid);

void check_option(void* p) {
	// ǰ���������...

	const navdata_option_t* option = ((navdata_t*)((data_pack*)p)->data)->options;
	cout << "---------------------" << endl;
	if (option->tag==navdata_tag_t::NAVDATA_CKS_TAG) {
		cout << "����һ��У��͡�����" << endl;
	}
	cout << "---------------------" << endl;
}

void data_recv_func(void* param) {
	// �������������
	char data[2048];
	recvClient->recv(data, 2048, check_option); // �ص���������Ĳ���Ϊdata
	const navdata_t* nvdt = (navdata_t*)data;
	
	cout << "��Ϣͷ: 0x" << hex <<setw(8) << setfill('0') << nvdt->header << endl;
	cout << "vision: " << nvdt->vision_defined << endl;
	cout << "���: 0x" << hex << setw(8) << setfill('0') << nvdt->sequence << endl;
	cout << "����״̬:" << (ardrone_get_mask(nvdt->ardrone_state, ARDRONE_FLY_MASK) ? "������" : "���ڷ���")<<endl;
	cout << "ģʽ�� " << (ardrone_get_mask(nvdt->ardrone_state, ARDRONE_NAVDATA_BOOTSTRAP) ? "bootstrapģʽ" : "�Ѿ��˳���bootstrapģʽ") << endl;
	cout << "demo: " << (ardrone_get_mask(nvdt->ardrone_state, ARDRONE_NAVDATA_DEMO_MASK) ? "demo" : "not demo") << endl;
	cout << endl;
	// ���Ϳ��Ź����÷��������Ϸ������ݹ�����
	string cmd = gen.cmd_watchdog();
	atClient->send(cmd.c_str(), cmd.size());
	
}

int main(int argc,char** argv) {
	net_prepare();
	
	recvClient = new UdpClient(ARDRONE_IP, NAVDATA_PORT);
	
	if (!recvClient->is_valid()) {
		cout << "udp client invalid..." << endl;
		return 0;
	}
	// ����֮ǰò�Ʊ���÷���һ��������������
	recvClient->send("\1", 1);
	Sleep(200);

	/*
 	 * �˳�demoģʽ����
	 */
	
	atClient = new UdpClient(ARDRONE_IP, AT_PORT);
	// ���Ϊ0,ȥ��
	gen.cmd_watchdog();
	string cmd = gen.cmd_config("general:navdata_demo","TRUE");
	atClient->send(cmd.c_str(), cmd.size());
	cmd = gen.cmd_control(5, 0);
	atClient->send(cmd.c_str(), cmd.size());
	

	cout << "Recieve data every 50ms.." << endl;
	Timer timer(100, data_recv_func, nullptr, false);
	timer.start();

	net_end();
	return 0;
}