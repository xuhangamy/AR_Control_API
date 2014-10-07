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

// ���ջ��̣߳�������
DWORD WINAPI recv_data(PVOID param) {
	
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
int main(int argc, char** argv) {
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

	arClient->SendATCmd(arClient->atgen.cmd_takeoff()); // ���
	cout << "now takeoff..." << endl;
	Timer::sleep(3000);

	// �Զ�����
	Timer timer_ctrl(50, auto_control, nullptr, false);
	timer_ctrl.start();

	arClient->SendATCmd(arClient->atgen.cmd_land()); // ����


	delete arClient;
	return 0;
}
