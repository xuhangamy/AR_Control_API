#ifndef _TK_TIMER_H_
#define _TK_TIMER_H_
#include "type.h"

namespace whu {
	/**
	 * @class Timer Timer.h ardrone/basic/timer.h
	 * @brief 一个简单的时钟，实现请在实现文件中修改
	 */
	class Timer {
	private:
		class Impl; /*!< 时钟实现类，字定义实现方法 */
		Impl* impl; 
		uint32_t interval; /*!< 执行时间间隔 */
		bool valid; /*!< 是否可用 */
		bool runing; /*!< 是否在运行 */
		bool(*func)(void* param); /*!< 回调函数 */
		void* func_param; /*!< 回调函数参数 */
		Timer();
	public:
		/**
		 * @brief 带参数默认构造函数
		 */
		Timer(uint32_t interval_, bool(*call_func)(void*param), void* param,bool auto_start = true);
		/**
		 * @brief 开始
		 */
		bool start();
		/**
		 * @brief 时钟停止，并且释放资源
		 * 这个实现的时候注意变量互斥等，可以由其他线程调用
		 */
		bool stop();
		/**
		 * @brief 线程挂起
		 */
		static void sleep(uint32_t sleep_time);
	};
}

#endif // _TK_TIMER_H_