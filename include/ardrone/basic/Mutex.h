/**
* @file Mutex.h
*
* @brief 互斥锁
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* 一个互斥锁类，实现了lock与unlock等方法。
*
* Copyright 2014.All rights reserved.
*/

#ifndef _TK_MUTEX_H_
#define _TK_MUTEX_H_

namespace whu {
	/**
	 * @var typedef void* mutex_t
	 * 保存互斥锁指针（或者windows里面的句柄）
	 */
	typedef void* mutex_t;

	class Mutex {
	private:
		mutex_t mutex; ///< 互斥锁指针或句柄
		bool valid; ///< 互斥锁是否有效
	public:
		/**
		 * @brief 构造函数
		 */
		Mutex();
		/**
		 * @brief 析构函数
		 */
		~Mutex();
		/** 
		 * @brief 互斥锁上锁
		 * @param wait_time 设置等待时间
		 * @return 是否锁定成功
		 */
		bool lock(unsigned long wait_time);
		/** 
		 * @brief 互斥锁解锁
		 * @return 是否解锁成功
		 */
		bool unlock();
		/**
		 * @brief 使互斥锁功能失效
		 */
		void set_invalid();
	};
}

#endif // _TK_MUTEX_H_