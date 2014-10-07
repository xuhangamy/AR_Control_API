/**
* @file ATCmdGenerator.h
*
* @brief AT指令产生器
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* 生成AT指令
*
* Copyright 2014.All rights reserved.
*/
#ifndef _TK_AT_CMD_GENERATOR_H_
#define _TK_AT_CMD_GENERATOR_H_

#include <string>

namespace whu {
	namespace ardrone {

		// CommandId声明 
		class CommandId;

		/**
		 * @class ATCmdGenerator ATCmdGenerator.h ardrone/ATCmdGenerator.h
		 * @brief 产生AT指令
		 */
		class ATCmdGenerator {
		private:
			CommandId* cmd_id;
			std::string cmdpack;
			ATCmdGenerator();
			ATCmdGenerator(const ATCmdGenerator&);
			const ATCmdGenerator& operator=(const ATCmdGenerator&);
		public:
			/**
			 * @brief 创建类
			 * @param[in] cmdid CommandId对象指针
			 * @return ATCmdGenerator对象引用
			 */
			static ATCmdGenerator& Create(CommandId* cmdid);

			/// @name 飞机控制AT指令
			//@{

			/// @brief 起飞
			/// @return 起飞指令
			std::string cmd_takeoff();

			/// @brief 降落
			/// @return 降落指令
			std::string cmd_land();

			/// @brief 紧急
			/// @return 紧急指令
			std::string cmd_emergency();

			/// @brief 移动
			/// @param flag 标志
			/// @param roll 左右
			/// @param pitch 前后
			/// @param gaz ...
			/// @param yaw ...
			/// @return 移动指令
			std::string cmd_move(bool flag, float roll, float pitch, float gaz, float yaw);

			/// @brief 移动高级
			/// @param flag 标志
			/// @param roll 左右
			/// @param pitch 前后
			/// @param gaz ...
			/// @param yaw ...
			/// @param psi ...
			/// @param psiacr ...
			/// @return 移动高级指令
			std::string cmd_move_adv(bool flag, float roll, float pitch, float gaz, float yaw, float psi, float psiacr);

			/// @brief AT*FTRIM
			/// @return AT*FTRIM指令
			std::string cmd_ftrims();

			/// @brief AT*CALIB
			/// @param device 设备
			/// @return AT*CALIB指令
			std::string cmd_calib(int device);

			/// @breif 配置
			/// @param name 配置名字
			/// @param value 配置值
			/// @return 配置指令
			std::string cmd_config(std::string name, std::string value);

			/// @brief 配置ids
			/// @param sid ...
			/// @param uid ...
			/// @param caid ...
			/// @return 指令
			std::string cmd_config_ids(std::string sid, std::string uid, std::string caid);

			/// @brief 看门狗
			/// @return 看门狗指令
			std::string cmd_watchdog();

			/// @brief 控制
			/// @param a 不知道啥
			/// @param b 不知道啥
			/// @return 指令
			std::string cmd_control(int a, int b);
			//@}

			/// @brief 获取当前CommandId的id
			/// @return id
			long get_current_id();

			/// @name 指令打包
			//@{

			/// @brief 指令打包
			/// @brief 一条指令
			void operator<<(const std::string cmd);

			/// @brief 清除包
			void clear_pack();

			/// @brief 获得指令包内容
			/// @return 指令包
			std::string get_cmd_pack();

			//@}
		};
	}

}


#endif // _TK_AT_CMD_GENERATOR_H_