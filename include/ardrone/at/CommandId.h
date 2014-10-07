/**
 * @file CommandId.h
 * 
 * @brief AT指令编号
 * 
 * @author tkorays
 * @date 2014-06-04
 * @since 1.0.0
 * 
 * 自动维护AT指令的序号，使指令能有序地发送。
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
		 * @brief 指令编号
		 *
		 * 指令编号从0开始，当调用获取编号函数时，可以根据参数决定是否自动自增编号。
		 * 这个类只能通过create创建，而且只能创建一个
		 */
		class CommandId {
		private:
			long id; ///< 自增的编号

			CommandId();
			~CommandId();
			CommandId(const CommandId&);
			const CommandId& operator=(const CommandId&);
		public:
			/**
			 * @brief 创建CommandId对象
			 * @return 返回一个CommandId单例对象
			 */
			static CommandId& Create();
			/**
			 * @brief 编号自增
			 */
			void operator++();
			/**
			 * @brief 获取id
			 * @param[in] auto_inc 获取编号时候是否自动增加id
			 * @return 当前编号
			 */
			long get_id(bool auto_inc);
			/**
			 * @brief 重置id
			 */
			void reset();
		};
	}
}
#endif // _TK_COMMAND_ID_H_