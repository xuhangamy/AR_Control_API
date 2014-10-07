#include <ardrone/basic/Timer.h>
#include <ardrone/os/win/inc.h>
using whu::Timer;

// 用于实现定时器功能，可以使用任何方法实现
class Timer::Impl {

};

whu::Timer::Timer() {
	valid = false;
	runing = false;
}
whu::Timer::Timer(uint32_t interval_, bool(*call_func)(void*param), void* param, bool auto_start) {
	interval = interval_;
	runing = false;
	// 如果调用的函数错误，则返回
	if (!call_func) {  
		valid = false;
		return;
	}
	func = call_func;
	func_param = param;
	valid = true;
	if (auto_start) {
		start();
	}
}
// 这个写的比较简单....
bool whu::Timer::start() {
	// 如果不可用（没初始化）或者正在运行
	if (!valid || runing) { 
		return false;
	}
	bool conti = true;
	// 这里貌似不会对参数检验
	while (conti) {
		conti = func(func_param);
		Sleep(interval);
	}
	
	return true;
}

bool whu::Timer::stop() {
	valid = false;
	return true;
}

void Timer::sleep(uint32_t sleep_time) {
	Sleep(sleep_time);
}

