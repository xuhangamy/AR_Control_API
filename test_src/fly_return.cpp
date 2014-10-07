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
bool is_forward = true;
int move_count=0;

bool auto_control(void*) {
	if (is_forward && move_count<60) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, -0.2f, -0.25f, 0.0f, 0.0f));
		move_count++;
		if (move_count>=60) {
			is_forward = false;
		}
	}else if (!is_forward && move_count<=120) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, -0.05f, 0.15f, 0.0f, 0.0f));
		move_count++;
	} else {
		return false;
	}
	return true;
}

// 接收机线程，不处理
DWORD WINAPI recv_data(PVOID param) {
	
	return 0;
}
// 不是看门狗，数据发了一段时间如果不回复，他会停止发送，所以隔一段时间就要发送一次通知
DWORD WINAPI watch_dog(LPVOID param) {
	while (true) {
		arClient->RequestData(); // 请求数据
		Timer::sleep(2000);
	}
	return 0;
}
int main(int argc, char** argv) {
	arClient = new ARDroneClient();
	arClient->InitARDrone();
	// 开启线程接收数据

	recv_thread = CreateThread(NULL, 0, recv_data, NULL, 0, &tid);
	DWORD wd_tid;
	wd_thread = CreateThread(NULL, 0, watch_dog, NULL, 0, &wd_tid);

	// 发送看门狗
	arClient->SendATCmd(arClient->atgen.cmd_watchdog());
	// flat trims
	arClient->SendATCmd(arClient->atgen.cmd_ftrims());
	// 发送看门狗
	arClient->SendATCmd(arClient->atgen.cmd_watchdog());

	arClient->SendATCmd(arClient->atgen.cmd_takeoff()); // 起飞
	cout << "now takeoff..." << endl;
	Timer::sleep(3000);

	// 自动飞行
	Timer timer_ctrl(50, auto_control, nullptr, false);
	timer_ctrl.start();

	arClient->SendATCmd(arClient->atgen.cmd_land()); // 降落


	delete arClient;
	return 0;
}
