#include <ardrone/navdata/common.h>
#include <ardrone/basic/timer.h>
#include <iostream>
using namespace whu::ardrone;
using namespace std;

#pragma comment(lib,"ARDrone.lib")

void call_func(void* param) {

	cout << (*(int*)param)++ << endl;
}

int main(int argc,char** argv) {
	int i = 0;
	// ���ʱ�ӻ���������˻�Ҫ�޸�
	Timer t(30, call_func, &i, false);
	t.start();
	Timer::sleep(20000);
	return 0;
}