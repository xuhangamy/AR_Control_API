/**
 * @file XClient.h
 * @author tkorays
 * @date 2014/7/5
 * 
 * @brief ������������
 */

#ifndef _TK_XCLIENT_H_
#define _TK_XCLIENT_H_

class XClient {
public:
	/// ��ʼ��ϵͳ����ARDrone�ĳ�ʼ����Kinect��
	void Init(); 

private:
	int control_mod; /// ����ģʽ
};

#endif // _TK_XCLIENT_H_