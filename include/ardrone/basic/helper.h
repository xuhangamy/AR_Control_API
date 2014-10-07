/**
* @file helper.h
*
* @brief 帮助文件，一些常用函数
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* 常用函数
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
 * 是否自动链接windows的库
 */
#ifdef LIB_AUTO_LINK
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#endif
#endif

namespace whu {
	namespace ardrone {
		/**
		* @brief 32位float与int调整
		* @param  num 输入的float
		* @return 转换后的int
		*/
		int f32_int32_adjust(const float num);

		/**
		* @brief windows里面网络准备
		*/
		void net_prepare();

		/**
		* @brief windows里面网络资源释放
		*/
		void net_end();

		/**
		* @brief 获取本机ip
		* @return ip字符串
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
		* @brief 0=黑色 1=蓝色 2=绿色 3=湖蓝色 4=红色 5=紫色
		*        6=黄色 7=白色 8=灰色 9=淡蓝色 A=淡绿色 B=淡浅绿色
		*        C=淡红色 D=淡紫色 E=淡黄色 F=亮白色
		*/
		void console_color_set(unsigned short color);
	}

}


#endif // _TK_HELPER_