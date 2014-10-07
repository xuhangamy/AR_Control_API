/**
* @file UdpClient.h
*
* @brief udp客户端类
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* udp客户端类，发送数据到服务器和接收服务器的数据
*
* Copyright 2014.All rights reserved.
*/

#ifndef _TK_UDPCLIENT_H_
#define _TK_UDPCLIENT_H_

namespace whu {
	/**
	* @brief socket指针或者句柄
	*/
	typedef void* socket_t;
	/**
	 * @class UdpClient UdpClient.h ardrone/UdpClient.h
	 *
	 * @brief udp客户端类，发送数据到服务器和接收服务器的数据
	 */
	class UdpClient {
	private:
		//socket_t* socket; ///< socket指针或句柄
		class socket_impl; ///< socket的具体实现类定义
		socket_impl* sck_impl; /// socket实现
		bool valid; ///< udp的socket是否有效
		UdpClient();
		UdpClient(const UdpClient&);
		UdpClient& operator=(const UdpClient&);
	public:
		/**
		* @brief 析构函数
		*/
		~UdpClient();
		/**
		 * @brief 有参数构造函数
		 * @param ip 服务器ip
		 * @param port 服务器udp端口
		 */
		UdpClient(const char* ip, short port);
		/**
		 * @breif 使udp客户端不可用
		 */
		void set_invalid();
		/**
		 * @brief udp客户端是否有效
		 * @return udp客户端是否有效
		 */
		bool is_valid();
		/**
		 * @brief 发送数据到服务器
		 * @param[in] data 发送的数据起始地址
		 * @param[in] len 发送的数据长度
		 * @return 发送是否成功
		 * @attention 发送成功与否是取决于socket是否有效，数据不一定能到达服务器
		 */
		bool send(const char* data,int len);
		/**
		 * @brief 从服务器接收数据
		 * @param data 用于保存接收数据
		 * @param callback 回调函数，接收到数据会就会调用
		 * @return 接收是否成功
		 * @attention 接收成功与否取决于socket是否有效，这里接收会阻塞
		 */
		bool recv(char* data,int len,void (*callback)(void*param));
	};
}


#endif // _TK_UDPCLIENT_H_