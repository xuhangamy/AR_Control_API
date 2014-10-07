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
#include <iostream>
using namespace std;
using namespace whu;
using namespace whu::ardrone;

#pragma comment(lib,"ARDrone.lib")

CommandId& cmdid = CommandId::Create();
ATCmdGenerator& gen = ATCmdGenerator::Create(&cmdid);
UdpClient* atClient;

Mutex genMutex;

bool on_land = true;

// 生成pack
void exit_bootstrap(void* param) {
	const data_pack* dt = (data_pack*)param;
	// 检查是不是bootstrap模式
	const navdata_t* navdata = (navdata_t*)(dt->data);
	// 这里就不检验头是否对
	if (ardrone_get_mask(navdata->ardrone_state,ARDRONE_NAVDATA_BOOTSTRAP)) {
		cout << "处于bootstrap模式" << endl;
		genMutex.lock(500);
		gen << gen.cmd_config("general:navdata_demo", "TRUE");
		genMutex.unlock();
	}
	// ACK
	string cmd = gen.cmd_control(5, 0);
	atClient->send(cmd.c_str(), cmd.size());

}
void scan_kb_func(void*) {
	string cmd="";
	if (key_press(KEY_UP)) {
		cout << "Up..." << endl;
		
	}
	if (key_press(KEY_DOWN)) {
		cout << "Down..." << endl;
		
	}
	if (key_press(KEY_LEFT)) {
		cout << "Left..." << endl;
		
	}
	if (key_press(KEY_RIGHT)) {
		cout << "Right..." << endl;
		
	}
	if (key_press(KEY_SPACE)) {
		if (on_land) {
			cout << "take of..." << endl;
			cmd = gen.cmd_takeoff();
			atClient->send(cmd.c_str(),cmd.size());
			on_land = false;
			Timer::sleep(2000);
		}else {
			cout << "landing..." << endl;
			cmd = gen.cmd_land();
			atClient->send(cmd.c_str(), cmd.size());
			on_land = true;
			Timer::sleep(2000);
		}
	}
	if (key_press('A')) {
		cout << "A..Emergency" << endl;
	}
}

int main(int argc, char** argv) {
	net_prepare();
	atClient = new UdpClient(ARDRONE_IP, AT_PORT);
	UdpClient navClient(ARDRONE_IP, NAVDATA_PORT);

	string cmd;
	char recv_data[2048];
	cmd = "\1";
	// init for navdata
	navClient.send(cmd.c_str(), cmd.size());


	/**
	 * 下面这句为了测试中不阻塞就注释了。
	 */
	navClient.recv(recv_data, 2048, exit_bootstrap);

	// 对gen的pack操作要上锁
	genMutex.lock(500);
	cmd = gen.get_cmd_pack();
	gen.clear_pack();
	genMutex.unlock();

	if (cmd.size()>0) {
		// 发送指令退出bootstrap
		navClient.send(cmd.c_str(),cmd.size());
	}
	
	

	// 初始化完毕，接下来循环读取键盘输入
	Timer timer(50,scan_kb_func,nullptr,false);
	timer.start();

	net_end();
	return 0;
}