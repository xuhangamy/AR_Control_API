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
	// 这个时钟会阻塞，因此还要修改
	Timer t(30, call_func, &i, false);
	t.start();
	Timer::sleep(20000);
	return 0;
}