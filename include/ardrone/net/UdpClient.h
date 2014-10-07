/**
* @file UdpClient.h
*
* @brief udp�ͻ�����
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* udp�ͻ����࣬�������ݵ��������ͽ��շ�����������
*
* Copyright 2014.All rights reserved.
*/

#ifndef _TK_UDPCLIENT_H_
#define _TK_UDPCLIENT_H_

namespace whu {
	/**
	* @brief socketָ����߾��
	*/
	typedef void* socket_t;
	/**
	 * @class UdpClient UdpClient.h ardrone/UdpClient.h
	 *
	 * @brief udp�ͻ����࣬�������ݵ��������ͽ��շ�����������
	 */
	class UdpClient {
	private:
		//socket_t* socket; ///< socketָ�����
		class socket_impl; ///< socket�ľ���ʵ���ඨ��
		socket_impl* sck_impl; /// socketʵ��
		bool valid; ///< udp��socket�Ƿ���Ч
		UdpClient();
		UdpClient(const UdpClient&);
		UdpClient& operator=(const UdpClient&);
	public:
		/**
		* @brief ��������
		*/
		~UdpClient();
		/**
		 * @brief �в������캯��
		 * @param ip ������ip
		 * @param port ������udp�˿�
		 */
		UdpClient(const char* ip, short port);
		/**
		 * @breif ʹudp�ͻ��˲�����
		 */
		void set_invalid();
		/**
		 * @brief udp�ͻ����Ƿ���Ч
		 * @return udp�ͻ����Ƿ���Ч
		 */
		bool is_valid();
		/**
		 * @brief �������ݵ�������
		 * @param[in] data ���͵�������ʼ��ַ
		 * @param[in] len ���͵����ݳ���
		 * @return �����Ƿ�ɹ�
		 * @attention ���ͳɹ������ȡ����socket�Ƿ���Ч�����ݲ�һ���ܵ��������
		 */
		bool send(const char* data,int len);
		/**
		 * @brief �ӷ�������������
		 * @param data ���ڱ����������
		 * @param callback �ص����������յ����ݻ�ͻ����
		 * @return �����Ƿ�ɹ�
		 * @attention ���ճɹ����ȡ����socket�Ƿ���Ч��������ջ�����
		 */
		bool recv(char* data,int len,void (*callback)(void*param));
	};
}


#endif // _TK_UDPCLIENT_H_