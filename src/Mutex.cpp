#include <ardrone/basic/Mutex.h>
using namespace whu;

// ʹ��windows��һЩ����������
#include <ardrone/os/win/inc.h>

Mutex::Mutex() {
	mutex = nullptr;
	valid = false;
	mutex = CreateMutex(NULL, FALSE, NULL);
	if (!mutex) {
		valid = true;
	}
}
Mutex::~Mutex() {}

bool Mutex::lock(unsigned long wait_time) {
	// �Ƿ����
	if (!valid) {
		return false;
	}
	DWORD ret = WaitForSingleObject(mutex, wait_time);
	if (ret!=WAIT_OBJECT_0) {
		return false;
	}
	return true;
}
bool Mutex::unlock() {
	if (!valid || !ReleaseMutex(mutex)) {
		return false;
	}
	return true;
}
void Mutex::set_invalid() {
	valid = false;
}