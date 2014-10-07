#include <ardrone/video/VideoEncap.h>
#include <ardrone/video/video_encapsulation.h>
using namespace whu::ardrone;
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ardrone/basic/fixit.h>

VideoEncap::VideoEncap() {
	data = malloc(30000);
	data_index = 0;
	left_size = 0;
}


void VideoEncap::handle_left(void* tcpdata){
	left_size = TcpPackSize - (data_size - data_index);
	memcpy(left_buf, (char*)tcpdata + data_size - data_index, left_size);
}

int VideoEncap::TcpPackSize = 1460;

bool VideoEncap::process(void* tcpdata) {
	
	const parrot_video_encapsulation_t* pave = \
		(parrot_video_encapsulation_t*)tcpdata;
	if (pave->signature[0]=='P' && pave->signature[1]=='a'\
		&& pave->signature[2]=='V' && pave->signature[3]=='E') {
		data_size = pave->payload_size;
		memcpy(data, (char*)tcpdata + pave->header_size, TcpPackSize - pave->header_size);
		data_index = TcpPackSize - pave->header_size; // 已经复制了这么多数据
		// 某个包里面只有一个帧
		if (pave->payload_size <= (TcpPackSize-pave->header_size)) {
			data_over = true;
			return true;
		}
		data_over = false;
		return false;
	} else {
		// 不是PaVE头，则直接复制数据

		// 最后一个,剩下的数据<=1460
		if (data_size-data_index<=TcpPackSize) {
			if (data_over) {
				memcpy(data, left_buf, left_size);
				memcpy((char*)data + left_size, (char*)tcpdata + 76, TcpPackSize-76);
				pave = (parrot_video_encapsulation_t*)data;
				data_size = pave->payload_size;
				// FIXIT: !!!
				data_over = true;
				return true; 
			}
			memcpy((char*)data + data_index, (char*)tcpdata, data_size - data_index);
			handle_left(tcpdata);
			// don't care about data_index
			data_index += (data_size - data_index);
			data_over = true;
			return true;
		}
		// else，否则直接复制数据就是了
		memcpy((char*)data + data_index, (char*)tcpdata, TcpPackSize);
		data_index += TcpPackSize;
		data_over = false;
		return false;
	}
}
void* VideoEncap::get_data() const {
	return data;
}
int VideoEncap::get_data_size() {
	return data_size;
}

// 这个倒是不是很占内存
bool VideoEncap::get_h264(void* tcpdata){
	
	memcpy (left_buf + left_size, tcpdata, TcpPackSize);
	left_size += TcpPackSize;
	
	const parrot_video_encapsulation_t* pave = \
		(parrot_video_encapsulation_t*)left_buf;
	// 检验这个是不是头
	if (pave->signature[0] == 'P' && pave->signature[1] == 'a'\
		&& pave->signature[2] == 'V' && pave->signature[3] == 'E') {
		data_size = pave->payload_size;
		data_index = 0;
		// 当完整的一帧刚好在left_buf时候
		if (data_size <= left_size-pave->header_size) {
			memcpy ((char*)data, left_buf + pave->header_size, data_size);
			left_size = left_size - (data_size + pave->header_size);
			// 剩下的数据 << 已经复制的数据,所以可以这么复制
			memcpy (left_buf, left_buf + data_size + pave->header_size, left_size);
			//printf ("短pave\n");
			return true;
		} else { // 一帧没完
			memcpy ((char*)data, left_buf + pave->header_size, left_size - pave->header_size);
			data_index = left_size - pave->header_size; 
			left_size = 0; // 数据已经完
			return false;
		}
	} else {
		// 剩下的数据在left_buf里面
		if (data_size-data_index <= left_size) {
			memcpy ((char*)data + data_index, left_buf, data_size - data_index);
			left_size = left_size - (data_size - data_index); // left - （总大小-已经复制的大小，即剩下要复制的）=遗留的
			// shift left
			for (int i = 0; i < left_size; i++) {
				left_buf[i] = left_buf[data_size - data_index + i];
			}
			return true; // 一帧完成
		} else {
			memcpy ((char*)data + data_index, left_buf, left_size);
			data_index += left_size;
			left_size = 0;
			return false;
		}
	}
	return true;
}