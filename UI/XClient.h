/**
 * @file XClient.h
 * @author tkorays
 * @date 2014/7/5
 * 
 * @brief 管理整个流程
 */

#ifndef _TK_XCLIENT_H_
#define _TK_XCLIENT_H_

class XClient {
public:
	/// 初始化系统，如ARDrone的初始化，Kinect等
	void Init(); 

private:
	int control_mod; /// 控制模式
};

#endif // _TK_XCLIENT_H_