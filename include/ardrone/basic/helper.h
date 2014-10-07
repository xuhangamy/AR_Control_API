/**
* @file helper.h
*
* @brief �����ļ���һЩ���ú���
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* ���ú���
*
* Copyright 2014.All rights reserved.
*/

#ifndef _TK_HELPER_
#define _TK_HELPER_
#pragma once

#include <string>
using namespace std;
#include "com_def.h"


#ifdef WIN32
/**
 * @def LIB_AUTO_LINK
 * �Ƿ��Զ�����windows�Ŀ�
 */
#ifdef LIB_AUTO_LINK
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#endif
#endif

namespace whu {
	namespace ardrone {
		/**
		* @brief 32λfloat��int����
		* @param  num �����float
		* @return ת�����int
		*/
		int f32_int32_adjust(const float num);

		/**
		* @brief windows��������׼��
		*/
		void net_prepare();

		/**
		* @brief windows����������Դ�ͷ�
		*/
		void net_end();

		/**
		* @brief ��ȡ����ip
		* @return ip�ַ���
		*/
		string get_local_ip();

		/**
		* @brief check return status from functions
		* check status,but not handle mistakes.
		* this function is used for showing mistakes when developing.
		*/
		void check_status(STATUS status, const string msg);

		/**
		* @brief Exit bootstrap mode if the status sent by ardrone indicates that the drone is in bootstrap mode.
		* @return return bool* actually
		*/
		void* bootstrap_check(void* param);

		void console_color_reset();

		/**
		* @brief 0=��ɫ 1=��ɫ 2=��ɫ 3=����ɫ 4=��ɫ 5=��ɫ
		*        6=��ɫ 7=��ɫ 8=��ɫ 9=����ɫ A=����ɫ B=��ǳ��ɫ
		*        C=����ɫ D=����ɫ E=����ɫ F=����ɫ
		*/
		void console_color_set(unsigned short color);
	}

}


#endif // _TK_HELPER_