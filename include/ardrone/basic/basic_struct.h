/**
* @file basic_struct.h
*
* @brief �����Ľṹ�嶨��
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* �����ṹ�壬���ڷ�װ������
*
* Copyright 2014.All rights reserved.
*/
#ifndef _TK_BASIC_STRUCT_H_
#define _TK_BASIC_STRUCT_H_

#include <string>

namespace whu {
	namespace ardrone {
		/**
		 * @brief atָ���װ
		 */
		typedef struct _at_cmd {
			long id; ///< ָ����
			std::string cmd; ///< ָ��
		} at_cmd;
		/**
		 * @brief navdata�ص������������
		 */
		typedef struct _navdata_callback_param {
			int len; ///< ���ݳ���
			void* data; ///< ��������ָ��
		} navdata_callback_param;
		/**
		* @brief ���ݴ��
		*/
		typedef struct _data_pack {
			int len; ///< ���ݳ���
			void* data; ///< ��������ָ��
		} data_pack;
	}
}
#endif // _TK_BASIC_STRUCT_H_