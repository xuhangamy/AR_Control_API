/**
 * @file com_def.h
 *
 * @brief 基本的宏定义
 *
 * @author tkorays
 * @date 2014-06-04
 * @since 1.0.0
 *
 * 本文件中包含了一些基本的宏定义，包括常用字符、数值定义；ARDrone相关的，比如：
 * ARDrone的ip，发送的命令代码，其端口；还包含一些函数的返回状态。
 * 
 * Copyright 2014.All rights reserved.
 */
#ifndef _TK_COMDEF_H_
#define _TK_COMDEF_H_
#pragma once

/// @def INF
/// 无穷大（32位，unsigned long）
#define INF 0xffffffff

/// @def MAX_BUFF_SIZE
/// 缓冲区最大长度
#define MAX_BUFF_SIZE 2048

/// @def WAIT_TIME_OUT
/// 等待超时时间
#define	WAIT_TIME_OUT 100

/// @def LF_DEF
/// 换行
#define LF_DEF '\x0a' // <LF>

/// @def CR_DEF
/// 回车
#define CR_DEF '\x0d' // <CR>

/// @def ARDRONE_IP
/// ARDrone的ip
#define ARDRONE_IP "192.168.1.1"

/// @def NAV_INIT_PKG
/// 第一次发送给NAVDATA_PORT的数据
#define NAV_INIT_PKG "\01"

/// @def TAKEOFF_CODE
/// 起飞指令AT*REF参数
#define TAKEOFF_CODE         0x11540200

/// @def LAND_CODE
/// 降落指令AT*REF参数
#define LAND_CODE            0x11540000

/// @def EMERG_CODE
/// 紧急状态指令AT*REF参数
#define EMERG_CODE           0x11540100



/// @def FTP_PORT
/// ARDrone的FTP端口
#define FTP_PORT	         5551

/// @def AUTH_PORT
/// ARDrone的认证端口
#define AUTH_PORT            5552

/// @def VIDEO_RECORDER_PORT
/// ARDrone视频录取端口
#define VIDEO_RECORDER_PORT  5553

/// @def NAVDATA_PORT
/// ARDrone导航数据端口
#define NAVDATA_PORT         5554

/// @def VIDEO_PORT
/// ARDrone的视频端口
#define VIDEO_PORT           5555

/// @def AT_PORT
/// ARDrone的AT指令端口
#define AT_PORT              5556

// @def RAW_CAPTURE_PORT
/// ARDrone的原始视频？端口
#define RAW_CAPTURE_PORT     5557

/// @def PRINTF_PORT
/// ARDrone的打印端口
#define PRINTF_PORT          5558

/// @def CONTROL_PORT
/// ARDrone的控制端口
#define CONTROL_PORT         5559

/// @var typedef int STATUS
/// 定义函数返回状态
typedef int STATUS;

/// @def TK_OK
/// 函数调用无错误
#define TK_OK                1

/// @def TK_WARNING
/// 警告，可能出现错误，也可能不出现
#define TK_WARNING           -1

/// @def TK_ERROR 
/// 错误
#define TK_ERROR             -2

/// @def TK_SOCK_ERROR
/// socket错误
#define TK_SOCK_ERROR        50

/// @def TK_INVALID_SCK
/// socket无效
#define TK_INVALID_SCK       51

/// @def TK_MUTEX_ERROR
/// 互斥锁错误
#define TK_MUTEX_ERROR       52

/// @def TK_ATCMD_ERROR
/// AT指令错误
#define TK_ATCMD_ERROR       53


#endif // _TK_COMDEF_H_