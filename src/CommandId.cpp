#include <ardrone/at/CommandId.h>
#include <iostream>
using namespace whu::ardrone;

CommandId::CommandId() {
	id = -1;
}
CommandId::~CommandId() {}

// TODO  非线程安全的，需要互斥锁来保证
// 但是本程序不会一直创建，为了性能考虑，不需要创建。
CommandId& CommandId::Create() {
	static CommandId cmdid;
	return cmdid;
}

void CommandId::operator++() {
	id++;
}

long CommandId::get_id(bool auto_inc) {
	if (auto_inc) {
		this->id++;
	}
	return id;
}

void CommandId::reset() {
	id = -1;
}