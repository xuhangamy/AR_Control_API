#include <ardrone/at/CommandId.h>
#include <iostream>
using namespace whu::ardrone;

CommandId::CommandId() {
	id = -1;
}
CommandId::~CommandId() {}

// TODO  ���̰߳�ȫ�ģ���Ҫ����������֤
// ���Ǳ����򲻻�һֱ������Ϊ�����ܿ��ǣ�����Ҫ������
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