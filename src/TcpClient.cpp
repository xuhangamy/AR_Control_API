#include <ardrone/net/TcpClient.h>
#include <ardrone/os/win/inc.h>
#include <ardrone/basic/basic_struct.h>
using namespace whu;
using namespace whu::ardrone;

class TcpClient::socket_impl {
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
		sck = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sck==INVALID_SOCKET) {
			socket_impl::valid = false;
		} else {
			socket_impl::valid = true;
		}
		sckaddr.sin_family = AF_INET;
		sckaddr.sin_addr.S_un.S_addr = inet_addr(ip);
		sckaddr.sin_port = ntohs(port);

		int status = connect(sck, (sockaddr*)&sckaddr, sizeof(sockaddr));

		if (status==SOCKET_ERROR) {
			valid = false;
		}
	}
	bool send(const char* data, int len) {
		if (!valid) {
			return false;
		}
		int status = ::send(sck, data, len, 0);
		if (status == SOCKET_ERROR) {
			return false;
		}
		return true;
	}
	bool recv(char* data, int len, void(*callback)(void* param)) {
		if (!valid) {
			return false;
		}
		if (::recv (sck, data, len, 0) < 0) {
			valid = false;
			return false;
		}
		data_pack dp;
		dp.len = len;
		dp.data = data;
		// 用引用！信剑哥，得永生。
		if (callback) {
			callback(&dp);
		}
		return true;
	}
	bool is_valid() {
		return socket_impl::valid;
	}
	bool reconnect () {
		int status = connect (sck, (sockaddr*)&sckaddr, sizeof(sockaddr));
		valid = true;
		if (status == SOCKET_ERROR) {
			valid = false;
			return false;
		}
		return true;
	}
};
// ------------------------------------------------------
TcpClient::~TcpClient() {
	if (sck_impl->is_valid()) {
		delete sck_impl;
		sck_impl = nullptr;
	}
}
TcpClient::TcpClient(const char* ip,short port) {
	valid = false;
	sck_impl = new socket_impl(ip, port);
	valid = sck_impl->is_valid();
}
bool TcpClient::is_valid() {
	return valid;
}
bool TcpClient::send(const char* data, int len) {
	return sck_impl->send(data, len);
}
bool TcpClient::recv(char* data, int len, void(*callback)(void* param)) {
	return sck_impl->recv(data, len, callback);
}
bool TcpClient::reconnect () {
	return sck_impl->reconnect ();
}