#include <ardrone/ardrone.h>
#include <ardrone/video/video_encapsulation.h>
#include <ardrone/video/VideoEncap.h>
#include <ardrone/basic/fixit.h>
using namespace whu;
using namespace whu::ardrone;
#pragma warning(disable:4996)
#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

#pragma comment(lib,"ARDrone.lib")
void cb(void* param) {

}
int main() {
	net_prepare();
	TcpClient* vc = new TcpClient(ARDRONE_IP, VIDEO_PORT);
	if (!vc->is_valid()) {
		printf("error");
		exit(-1);
	}
	int count = 0;
	FILE *f = fopen("fuck.h264", "w");
	const int max_buf_size = VideoEncap::TcpPackSize;
	char* buf = (char*)malloc(max_buf_size);
	VideoEncap encap;
	while (true) {
		if (count>300) {
			break;
		}
		vc->recv((char*)buf, max_buf_size, cb); // ��������
		if (encap.process(buf)) {
			vardump_hex(encap.get_data(), encap.get_data_size());
			fwrite(encap.get_data(), encap.get_data_size(), 1, f);
			cout << "������!����ͨ��encap.get_data()��ȡ����" << endl;
			//break;
		} else {
			cout << "�����С���" << endl;
		}
		count++;
	}
	fclose(f);
	delete vc;
	net_end();
	return 0;
}
