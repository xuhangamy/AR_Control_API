#include <ardrone/net/UdpClient.h>
#include <ardrone/os/win/inc.h>
#include <ardrone/basic/basic_struct.h>
using whu::UdpClient;
using namespace whu::ardrone;

// Pimpl实现方法
class UdpClient::socket_impl {
private:
	SOCKET sck;
	sockaddr_in sckaddr;
	bool valid;
public:
	~socket_impl() {
		if (valid) {
			closesocket(sck);
		}
	}
	socket_impl(const char* ip,short port) {
		// 创建socket
		sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sck==INVALID_SOCKET) {
			valid = false;
		} else {
			valid = true;
		}
		sckaddr.sin_family = AF_INET;
		sckaddr.sin_addr.S_un.S_addr = inet_addr(ip);
		sckaddr.sin_port = ntohs(port);

		int status = connect(sck, (sockaddr*)&sckaddr, sizeof(sockaddr));

		if (status==SOCKET_ERROR) {
			valid = false;
		}
	}
	// socket 是否有效
	bool is_valid() {
		return socket_impl::valid;
	}
	bool send(const char* data,int len){
		if (!valid) {
			return false;
		}
		int status = sendto(sck, data, len, 0, \
			(sockaddr*)&sckaddr, sizeof(sockaddr));
		if (status==SOCKET_ERROR) {
			return false;
		}
		return true;
	}
	bool recv(char* data ,int len, void(*callback)(void*param)) {
		if (!valid) {
			return false;
		}
		int nsize = sizeof(sockaddr_in);
		int status = recvfrom(sck, data, len, 0, \
			(sockaddr*)&sckaddr, &nsize);
		if (status==SOCKET_ERROR) {
			return false;
		}
		data_pack dp;
		dp.len = len;
		dp.data = data;
		callback(&dp);
		return true;
	}
};

//-------------------------------------------------------
UdpClient::~UdpClient() {
	if (sck_impl->is_valid()) {
		delete sck_impl;
		sck_impl = nullptr;
	}
}
UdpClient::UdpClient() {
	valid = false;
}
UdpClient::UdpClient(const char* ip, short port) {
	valid = false;
	sck_impl = new socket_impl(ip, port);
	valid = sck_impl->is_valid();
}

bool UdpClient::is_valid() {
	return valid;
}

bool UdpClient::send(const char* data, int len) {
	return sck_impl->send(data, len);
}
bool UdpClient::recv(char* data, int len, void(*callback)(void*param)) {
	return sck_impl->recv(data, len, callback);
}