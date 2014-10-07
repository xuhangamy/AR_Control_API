/**
* @file win_thread.h
*
* @brief 事件表for windows
*
* @author tkorays
* @date 2014-06-04
* @since 1.0.0
*
* 一个事件表的实现，for windows
*
* Copyright 2014.All rights reserved.
*/
#ifndef _TK_WIN_THREAD_H_
#define _TK_WIN_THREAD_H_

#include "../../basic/com_def.h"
#include "inc.h"

#define thread_dw_ret DWORD WINAPI

typedef HANDLE Thread_t;

#define __CLAIM_THREAD_TABLE__ void THREAD_TABLE_EXEC();
#define THREAD_TABLE_START(thread_num) void THREAD_TABLE_EXEC(){\
	int t_num = (thread_num); \
	Thread_t _thread_table[(thread_num)]; \
	DWORD _thread_id[(thread_num)]; \
	int count = 0;

#define CREATE_THREAD(func) if(count>=t_num){;}else{\
	_thread_table[count] = \
	CreateThread(NULL, 0, func, NULL, TRUE, (_thread_id + count)); \
	count++; }

#define THREAD_TABLE_END WaitForMultipleObjects(t_num,_thread_table,TRUE,INF); \
	return; }


#endif // _TK_WIN_THREAD_H_