#include <ardrone/ardrone.h>
#include <ardrone/video/video_encapsulation.h>
#include <ardrone/video/VideoEncap.h>
#include <ardrone/basic/fixit.h>
#include <iostream>
#include <fstream>

#pragma comment(lib,"ARDrone.lib")

using namespace whu;
using namespace whu::ardrone;
using namespace std;


int main(int argc, char** argv) {
	net_prepare();

	// Connect the AR.Drone video port
	TcpClient* videoClient = new  TcpClient(ARDRONE_IP, VIDEO_PORT);
	if (!videoClient->is_valid()) {
		cerr << "can't connnected to the video tcp..." << endl;
		abort();
	}

	int count = 0; // control the size of frames
	std::ofstream videoIO("video.h264", ios::binary);

	const int max_buf_size = VideoEncap::TcpPackSize;
	char* buf = (char*)malloc(max_buf_size);
	VideoEncap encap;
	while (true) {
		if (count>300) {
			break;
		}
		videoClient->recv(buf, max_buf_size, NULL);
		//vardump_hex(buf, max_buf_size); // output the data (hex format)
		if (encap.process(buf)) {
			videoIO.write((char*)encap.get_data(), encap.get_data_size());
			count++;
			//vardump_hex(encap.get_data(), encap.get_data_size());
		}
	}
	videoIO.close();
	net_end();
	return 0;
}
