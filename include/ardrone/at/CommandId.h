/**
 * @file CommandId.h
 * 
 * @brief ATָ����
 * 
 * @author tkorays
 * @date 2014-06-04
 * @since 1.0.0
 * 
 * �Զ�ά��ATָ�����ţ�ʹָ��������ط��͡�
 * 
 * Copyright 2014.All rights reserved.
 */
#ifndef _TK_COMMAND_ID_H_
#define _TK_COMMAND_ID_H_

namespace whu {
	namespace ardrone {
		/**
		 * @class CommandId CommandId.h ardrone/CommandId.h
		 *
		 * @brief ָ����
		 *
		 * ָ���Ŵ�0��ʼ�������û�ȡ��ź���ʱ�����Ը��ݲ��������Ƿ��Զ�������š�
		 * �����ֻ��ͨ��create����������ֻ�ܴ���һ��
		 */
		class CommandId {
		private:
			long id; ///< �����ı��

			CommandId();
			~CommandId();
			CommandId(const CommandId&);
			const CommandId& operator=(const CommandId&);
		public:
			/**
			 * @brief ����CommandId����
			 * @return ����һ��CommandId��������
			 */
			static CommandId& Create();
			/**
			 * @brief �������
			 */
			void operator++();
			/**
			 * @brief ��ȡid
			 * @param[in] auto_inc ��ȡ���ʱ���Ƿ��Զ�����id
			 * @return ��ǰ���
			 */
			long get_id(bool auto_inc);
			/**
			 * @brief ����id
			 */
			void reset();
		};
	}
}
#endif // _TK_COMMAND_ID_H_