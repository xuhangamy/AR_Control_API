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
	// 前期设计问题...

	const navdata_option_t* option = ((navdata_t*)((data_pack*)p)->data)->options;
	cout << "---------------------" << endl;
	if (option->tag==navdata_tag_t::NAVDATA_CKS_TAG) {
		cout << "这是一个校验和。。。" << endl;
	}
	cout << "---------------------" << endl;
}

void data_recv_func(void* param) {
	// 这里面接收数据
	char data[2048];
	recvClient->recv(data, 2048, check_option); // 回调函数传入的参数为data
	const navdata_t* nvdt = (navdata_t*)data;
	
	cout << "消息头: 0x" << hex <<setw(8) << setfill('0') << nvdt->header << endl;
	cout << "vision: " << nvdt->vision_defined << endl;
	cout << "编号: 0x" << hex << setw(8) << setfill('0') << nvdt->sequence << endl;
	cout << "飞行状态:" << (ardrone_get_mask(nvdt->ardrone_state, ARDRONE_FLY_MASK) ? "飞行中" : "不在飞行")<<endl;
	cout << "模式： " << (ardrone_get_mask(nvdt->ardrone_state, ARDRONE_NAVDATA_BOOTSTRAP) ? "bootstrap模式" : "已经退出出bootstrap模式") << endl;
	cout << "demo: " << (ardrone_get_mask(nvdt->ardrone_state, ARDRONE_NAVDATA_DEMO_MASK) ? "demo" : "not demo") << endl;
	cout << endl;
	// 发送看门狗，让服务器不断发送数据过来。
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
	// 接收之前貌似必须得发送一个包到服务器。
	recvClient->send("\1", 1);
	Sleep(200);

	/*
 	 * 退出demo模式测试
	 */
	
	atClient = new UdpClient(ARDRONE_IP, AT_PORT);
	// 编号为0,去掉
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