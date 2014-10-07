/**
 * @file com_def.h
 *
 * @brief �����ĺ궨��
 *
 * @author tkorays
 * @date 2014-06-04
 * @since 1.0.0
 *
 * ���ļ��а�����һЩ�����ĺ궨�壬���������ַ�����ֵ���壻ARDrone��صģ����磺
 * ARDrone��ip�����͵�������룬��˿ڣ�������һЩ�����ķ���״̬��
 * 
 * Copyright 2014.All rights reserved.
 */
#ifndef _TK_COMDEF_H_
#define _TK_COMDEF_H_
#pragma once

/// @def INF
/// �����32λ��unsigned long��
#define INF 0xffffffff

/// @def MAX_BUFF_SIZE
/// ��������󳤶�
#define MAX_BUFF_SIZE 2048

/// @def WAIT_TIME_OUT
/// �ȴ���ʱʱ��
#define	WAIT_TIME_OUT 100

/// @def LF_DEF
/// ����
#define LF_DEF '\x0a' // <LF>

/// @def CR_DEF
/// �س�
#define CR_DEF '\x0d' // <CR>

/// @def ARDRONE_IP
/// ARDrone��ip
#define ARDRONE_IP "192.168.1.1"

/// @def NAV_INIT_PKG
/// ��һ�η��͸�NAVDATA_PORT������
#define NAV_INIT_PKG "\01"

/// @def TAKEOFF_CODE
/// ���ָ��AT*REF����
#define TAKEOFF_CODE         0x11540200

/// @def LAND_CODE
/// ����ָ��AT*REF����
#define LAND_CODE            0x11540000

/// @def EMERG_CODE
/// ����״ָ̬��AT*REF����
#define EMERG_CODE           0x11540100



/// @def FTP_PORT
/// ARDrone��FTP�˿�
#define FTP_PORT	         5551

/// @def AUTH_PORT
/// ARDrone����֤�˿�
#define AUTH_PORT            5552

/// @def VIDEO_RECORDER_PORT
/// ARDrone��Ƶ¼ȡ�˿�
#define VIDEO_RECORDER_PORT  5553

/// @def NAVDATA_PORT
/// ARDrone�������ݶ˿�
#define NAVDATA_PORT         5554

/// @def VIDEO_PORT
/// ARDrone����Ƶ�˿�
#define VIDEO_PORT           5555

/// @def AT_PORT
/// ARDrone��ATָ��˿�
#define AT_PORT              5556

// @def RAW_CAPTURE_PORT
/// ARDrone��ԭʼ��Ƶ���˿�
#define RAW_CAPTURE_PORT     5557

/// @def PRINTF_PORT
/// ARDrone�Ĵ�ӡ�˿�
#define PRINTF_PORT          5558

/// @def CONTROL_PORT
/// ARDrone�Ŀ��ƶ˿�
#define CONTROL_PORT         5559

/// @var typedef int STATUS
/// ���庯������״̬
typedef int STATUS;

/// @def TK_OK
/// ���������޴���
#define TK_OK                1

/// @def TK_WARNING
/// ���棬���ܳ��ִ���Ҳ���ܲ�����
#define TK_WARNING           -1

/// @def TK_ERROR 
/// ����
#define TK_ERROR             -2

/// @def TK_SOCK_ERROR
/// socket����
#define TK_SOCK_ERROR        50

/// @def TK_INVALID_SCK
/// socket��Ч
#define TK_INVALID_SCK       51

/// @def TK_MUTEX_ERROR
/// ����������
#define TK_MUTEX_ERROR       52

/// @def TK_ATCMD_ERROR
/// ATָ�����
#define TK_ATCMD_ERROR       53


#endif // _TK_COMDEF_H_