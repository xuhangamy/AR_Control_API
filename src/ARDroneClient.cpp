#include <ardrone/ARDroneClient.h>
#include <ardrone/basic/com_def.h>
#include <ardrone/basic/helper.h>
using namespace whu;
using namespace whu::ardrone;

ARDroneClient::ARDroneClient() {
	net_prepare();
	atgen.cmd_watchdog();
	
	atClient = new UdpClient(ARDRONE_IP, AT_PORT);
	navClient = new UdpClient(ARDRONE_IP, NAVDATA_PORT);
}
ARDroneClient::~ARDroneClient() {
	net_end();
	delete atClient;
	delete navClient;
}

bool ARDroneClient::InitARDrone() {
	string cmd = "\1";
	navClient->send(cmd.c_str(), 1); // 开始准备接收数据
	cmd = atgen.cmd_config("general:navdata_demo", "TRUE");
	atClient->send(cmd.c_str(), cmd.size()); // 退出boostrap模式
	cmd = atgen.cmd_control(5, 0);
	atClient->send(cmd.c_str(), cmd.size()); // ack
	return true;
}

bool ARDroneClient::SendATCmd(std::string atgen_str) {
	return atClient->send(atgen_str.c_str(), atgen_str.size());
}

bool ARDroneClient::RecvData(void(*handle_func)(void* dt_pack)) {
	char dt[MAX_BUFF_SIZE];
	return navClient->recv(dt, MAX_BUFF_SIZE, handle_func);
}

void ARDroneClient::RequestData() {
	navClient->send("\1", 1);
}