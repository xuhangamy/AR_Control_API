/**
* @file ATCmdGenerator.h
*
* @brief ATָ�������
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* ����ATָ��
*
* Copyright 2014.All rights reserved.
*/
#ifndef _TK_AT_CMD_GENERATOR_H_
#define _TK_AT_CMD_GENERATOR_H_

#include <string>

namespace whu {
	namespace ardrone {

		// CommandId���� 
		class CommandId;

		/**
		 * @class ATCmdGenerator ATCmdGenerator.h ardrone/ATCmdGenerator.h
		 * @brief ����ATָ��
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
			 * @brief ������
			 * @param[in] cmdid CommandId����ָ��
			 * @return ATCmdGenerator��������
			 */
			static ATCmdGenerator& Create(CommandId* cmdid);

			/// @name �ɻ�����ATָ��
			//@{

			/// @brief ���
			/// @return ���ָ��
			std::string cmd_takeoff();

			/// @brief ����
			/// @return ����ָ��
			std::string cmd_land();

			/// @brief ����
			/// @return ����ָ��
			std::string cmd_emergency();

			/// @brief �ƶ�
			/// @param flag ��־
			/// @param roll ����
			/// @param pitch ǰ��
			/// @param gaz ...
			/// @param yaw ...
			/// @return �ƶ�ָ��
			std::string cmd_move(bool flag, float roll, float pitch, float gaz, float yaw);

			/// @brief �ƶ��߼�
			/// @param flag ��־
			/// @param roll ����
			/// @param pitch ǰ��
			/// @param gaz ...
			/// @param yaw ...
			/// @param psi ...
			/// @param psiacr ...
			/// @return �ƶ��߼�ָ��
			std::string cmd_move_adv(bool flag, float roll, float pitch, float gaz, float yaw, float psi, float psiacr);

			/// @brief AT*FTRIM
			/// @return AT*FTRIMָ��
			std::string cmd_ftrims();

			/// @brief AT*CALIB
			/// @param device �豸
			/// @return AT*CALIBָ��
			std::string cmd_calib(int device);

			/// @breif ����
			/// @param name ��������
			/// @param value ����ֵ
			/// @return ����ָ��
			std::string cmd_config(std::string name, std::string value);

			/// @brief ����ids
			/// @param sid ...
			/// @param uid ...
			/// @param caid ...
			/// @return ָ��
			std::string cmd_config_ids(std::string sid, std::string uid, std::string caid);

			/// @brief ���Ź�
			/// @return ���Ź�ָ��
			std::string cmd_watchdog();

			/// @brief ����
			/// @param a ��֪��ɶ
			/// @param b ��֪��ɶ
			/// @return ָ��
			std::string cmd_control(int a, int b);
			//@}

			/// @brief ��ȡ��ǰCommandId��id
			/// @return id
			long get_current_id();

			/// @name ָ����
			//@{

			/// @brief ָ����
			/// @brief һ��ָ��
			void operator<<(const std::string cmd);

			/// @brief �����
			void clear_pack();

			/// @brief ���ָ�������
			/// @return ָ���
			std::string get_cmd_pack();

			//@}
		};
	}

}


#endif // _TK_AT_CMD_GENERATOR_H_