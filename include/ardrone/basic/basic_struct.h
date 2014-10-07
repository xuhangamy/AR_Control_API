/**
* @file basic_struct.h
*
* @brief 基本的结构体定义
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* 基本结构体，用于封装参数等
*
* Copyright 2014.All rights reserved.
*/
#ifndef _TK_BASIC_STRUCT_H_
#define _TK_BASIC_STRUCT_H_

#include <string>

namespace whu {
	namespace ardrone {
		/**
		 * @brief at指令封装
		 */
		typedef struct _at_cmd {
			long id; ///< 指令编号
			std::string cmd; ///< 指令
		} at_cmd;
		/**
		 * @brief navdata回调函数参数打包
		 */
		typedef struct _navdata_callback_param {
			int len; ///< 数据长度
			void* data; ///< 数据内容指针
		} navdata_callback_param;
		/**
		* @brief 数据打包
		*/
		typedef struct _data_pack {
			int len; ///< 数据长度
			void* data; ///< 数据内容指针
		} data_pack;
	}
}
#endif // _TK_BASIC_STRUCT_H_