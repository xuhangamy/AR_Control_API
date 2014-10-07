/**
* @file Mutex.h
*
* @brief ������
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* һ���������࣬ʵ����lock��unlock�ȷ�����
*
* Copyright 2014.All rights reserved.
*/

#ifndef _TK_MUTEX_H_
#define _TK_MUTEX_H_

namespace whu {
	/**
	 * @var typedef void* mutex_t
	 * ���滥����ָ�루����windows����ľ����
	 */
	typedef void* mutex_t;

	class Mutex {
	private:
		mutex_t mutex; ///< ������ָ�����
		bool valid; ///< �������Ƿ���Ч
	public:
		/**
		 * @brief ���캯��
		 */
		Mutex();
		/**
		 * @brief ��������
		 */
		~Mutex();
		/** 
		 * @brief ����������
		 * @param wait_time ���õȴ�ʱ��
		 * @return �Ƿ������ɹ�
		 */
		bool lock(unsigned long wait_time);
		/** 
		 * @brief ����������
		 * @return �Ƿ�����ɹ�
		 */
		bool unlock();
		/**
		 * @brief ʹ����������ʧЧ
		 */
		void set_invalid();
	};
}

#endif // _TK_MUTEX_H_