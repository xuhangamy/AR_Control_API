/**
 * @file TcpClient.h
 * @brief Tcp�ͻ���
 * 
 * @author tkorays
 * @date 2014-6-15
 * @since 1.0.0
 *
 * һ���򵥵�Tcp�ͻ��ˣ���֧��tcp�����Ĺ���
 */
#ifndef _TK_TCPCLINET_H_
#define _TK_TCPCLINET_H_

namespace whu {
	/**
	 * @class TcpClient TcpClient.h ardrone/net/TcpClient.h
	 * 
	 * @brief Tcp�ͻ���
	 */
	class TcpClient {
	private:
		class socket_impl;
		socket_impl* sck_impl;
		bool valid;
		TcpClient();
		TcpClient(const TcpClient&);
		TcpClient& operator=(const TcpClient&);
	public:
		~TcpClient();
		TcpClient(const char* ip, short port);
		void set_invalid();
		bool is_valid();
		bool send(const char* data, int len);
		bool recv(char* data, int len, void(*callback)(void*param));
		bool reconnect ();
	};
}


#endif // _TK_TCPCLINET_H_