#include <ardrone/ardrone.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

using namespace whu;
using namespace whu::ardrone;
#pragma comment(lib,"ARDrone.lib")

HANDLE recv_thread;
HANDLE wd_thread;
DWORD tid;
ARDroneClient* arClient;
bool is_onland = true;
stringstream ss;
ofstream ofs("data.csv");

bool kb_control(void*) {
	if (key_press(KEY_SPACE)) {
		if (is_onland) {
			arClient->SendATCmd(arClient->atgen.cmd_takeoff());
			Timer::sleep(2000);
			is_onland = false;
		} else {		
			arClient->SendATCmd(arClient->atgen.cmd_land());
			Timer::sleep(2000);
			is_onland = true;
		}
	}
	if (key_press(KEY_LEFT)) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, -0.2f, 0.0f, 0.0f, 0.0f));
	}
	if (key_press(KEY_RIGHT)) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, 0.2f, 0.0f, 0.0f, 0.0f));
	}
	if (key_press(KEY_UP)) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, 0.0f, -0.2f, 0.0f, 0.0f));
	}
	if (key_press(KEY_DOWN)) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, 0.0f, 0.2f, 0.0f, 0.0f));
	}
	if (key_press(VK_ESCAPE)) {
		arClient->SendATCmd (arClient->atgen.cmd_move (true, 0.0f, 0.0f, 0.0f, 0.5f));
	}
	if (key_press ('A')) {
		arClient->SendATCmd (arClient->atgen.cmd_move (true, 0.0f, 0.0f, 0.2f, 0.0f));
	}
	if (key_press(KEY_RETURN)) {
		CloseHandle(recv_thread);
		CloseHandle(wd_thread);
		return false;
	}
	return true;
}
// �����Ĵ�����,����ֻ��ȡ�˸߶ȵ���Ϣ
void handle_recv_data(void* dt_pck) {
	data_pack* dt = (data_pack*)dt_pck;
	NavdataParser parser(dt->data,dt->len);
	
	if (!parser.state_bootstrap()) { 
		// ����Ѿ��˳�bootstrapģʽ���������ص���Ϣ
		parser.read_option_list();
		const navdata_demo_t* demo = ((navdata_demo_t*)((navdata_t*)dt->data)->options);
		printf("\n----------------------------------------------\n");
		printf("�߶�:\t%d\n", parser.idata.altitude);
		printf("����:\t%d%%\n", parser.idata.voltage);
		printf("vx:\t%f\n", parser.idata.vx);
		printf("vy:\t%f\n", parser.idata.vy);
		printf("vz:\t%f\n", parser.idata.vz);
		ss << parser.idata.altitude << "\n";
	}
}
// ���ջ��̣߳�������
DWORD WINAPI recv_data(PVOID param) {
	while (true) {
		arClient->RecvData(handle_recv_data);
		Timer::sleep(30);
	}
	return 0;
}
// ���ǿ��Ź������ݷ���һ��ʱ��������ظ�������ֹͣ���ͣ����Ը�һ��ʱ���Ҫ����һ��֪ͨ
DWORD WINAPI watch_dog(LPVOID param) {
	while (true) {
		arClient->RequestData(); // ��������
		Timer::sleep(2000);
	}
	return 0;
}
int main(int argc,char** argv){
	arClient = new ARDroneClient();
	arClient->InitARDrone();
	// �����߳̽�������
	
	recv_thread = CreateThread(NULL, 0, recv_data, NULL, 0, &tid);
	DWORD wd_tid;
	wd_thread = CreateThread(NULL, 0, watch_dog, NULL, 0, &wd_tid);

	// ���Ϳ��Ź�
	arClient->SendATCmd(arClient->atgen.cmd_watchdog());
	// flat trims
	arClient->SendATCmd(arClient->atgen.cmd_ftrims());
	// ���Ϳ��Ź�
	arClient->SendATCmd(arClient->atgen.cmd_watchdog());
	
	// ���̿���
	Timer timer_ctrl(50,kb_control,nullptr,false);
	timer_ctrl.start();
	ofs << ss.str();
	ofs.close();
	
	delete arClient;
	return 0;
}
