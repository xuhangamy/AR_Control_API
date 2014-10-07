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
#include <ardrone/navdata/NavdataParser.h>
#include <ardrone/os/win/thread.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;
using namespace whu;
using namespace whu::ardrone;

#pragma comment(lib,"ARDrone.lib")

UdpClient* recvClient;
UdpClient* atclient;
CommandId& cmdid = CommandId::Create();
ATCmdGenerator& gen = ATCmdGenerator::Create(&cmdid);
stringstream altitude_data;
bool init(void* param);
Timer initTimer(30, init, nullptr,false); // 每200ms接收一次数据
int i = 0;
bool stopit = false;

void handleData(void* param) {
	
}

bool init(void* param) {
	char data[MAX_BUFF_SIZE];
	recvClient->recv(data, MAX_BUFF_SIZE, handleData);
	NavdataParser parser(data, 2048);

	if (!parser.state_bootstrap()) { // 已经退出bootstrap模式
		parser.read_option_list();
		cout << parser.idata.altitude << endl;
		altitude_data << parser.idata.altitude << "\n";
		i++;
		cout << "---------------->" << i << endl;
	}
	if (i >= 100) {
		cout << "stop" << endl;
		stopit = true;
		return false; // 时钟停止
	}
	
	return true; // 时钟继续
}
bool wtdog(void* param) {
	if (stopit==true) {
		return false;
	}
	string cmd;
	cmd = gen.cmd_watchdog();
	atclient->send(cmd.c_str(), cmd.size());
	return true;
}

thread_dw_ret takeoff_land(void* param) {
	Sleep(100);
	string cmd = gen.cmd_takeoff();
	atclient->send(cmd.c_str(), cmd.size());
	
	for (size_t i = 0; i < 1000; i++) {
		cmd = gen.cmd_watchdog();
		atclient->send(cmd.c_str(), cmd.size());
	}
	cmd = gen.cmd_land();
	atclient->send(cmd.c_str(), cmd.size());

	Timer wt(50, wtdog, nullptr, true);
	return 0;
}

thread_dw_ret recv_data(void*param) {
	initTimer.start();
	return 0;
}

__CLAIM_THREAD_TABLE__

int main() {
	net_prepare();
	recvClient = new UdpClient(ARDRONE_IP, NAVDATA_PORT);
	recvClient->send("\1", 1); // 开始接收数据

	atclient = new UdpClient(ARDRONE_IP, AT_PORT);
	gen.cmd_watchdog();
	string cmd = gen.cmd_config("general:navdata_demo", "TRUE");
	atclient->send(cmd.c_str(),cmd.size());
	cmd = gen.cmd_control(5, 0);
	atclient->send(cmd.c_str(), cmd.size());

	THREAD_TABLE_EXEC();

	ofstream fs("data.csv");
	fs << altitude_data.str();
	fs.close();
	net_end();
	return 0;
}

THREAD_TABLE_START(2)
CREATE_THREAD(takeoff_land)
CREATE_THREAD(recv_data)
THREAD_TABLE_END