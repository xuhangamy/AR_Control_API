#ifndef _TK_TIMER_H_
#define _TK_TIMER_H_
#include "type.h"

namespace whu {
	/**
	 * @class Timer Timer.h ardrone/basic/timer.h
	 * @brief һ���򵥵�ʱ�ӣ�ʵ������ʵ���ļ����޸�
	 */
	class Timer {
	private:
		class Impl; /*!< ʱ��ʵ���࣬�ֶ���ʵ�ַ��� */
		Impl* impl; 
		uint32_t interval; /*!< ִ��ʱ���� */
		bool valid; /*!< �Ƿ���� */
		bool runing; /*!< �Ƿ������� */
		bool(*func)(void* param); /*!< �ص����� */
		void* func_param; /*!< �ص��������� */
		Timer();
	public:
		/**
		 * @brief ������Ĭ�Ϲ��캯��
		 */
		Timer(uint32_t interval_, bool(*call_func)(void*param), void* param,bool auto_start = true);
		/**
		 * @brief ��ʼ
		 */
		bool start();
		/**
		 * @brief ʱ��ֹͣ�������ͷ���Դ
		 * ���ʵ�ֵ�ʱ��ע���������ȣ������������̵߳���
		 */
		bool stop();
		/**
		 * @brief �̹߳���
		 */
		static void sleep(uint32_t sleep_time);
	};
}

#endif // _TK_TIMER_H_