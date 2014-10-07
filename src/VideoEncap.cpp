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
		data_index = TcpPackSize - pave->header_size; // �Ѿ���������ô������
		// ĳ��������ֻ��һ��֡
		if (pave->payload_size <= (TcpPackSize-pave->header_size)) {
			data_over = true;
			return true;
		}
		data_over = false;
		return false;
	} else {
		// ����PaVEͷ����ֱ�Ӹ�������

		// ���һ��,ʣ�µ�����<=1460
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
		// else������ֱ�Ӹ������ݾ�����
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

// ������ǲ��Ǻ�ռ�ڴ�
bool VideoEncap::get_h264(void* tcpdata){
	
	memcpy (left_buf + left_size, tcpdata, TcpPackSize);
	left_size += TcpPackSize;
	
	const parrot_video_encapsulation_t* pave = \
		(parrot_video_encapsulation_t*)left_buf;
	// ��������ǲ���ͷ
	if (pave->signature[0] == 'P' && pave->signature[1] == 'a'\
		&& pave->signature[2] == 'V' && pave->signature[3] == 'E') {
		data_size = pave->payload_size;
		data_index = 0;
		// ��������һ֡�պ���left_bufʱ��
		if (data_size <= left_size-pave->header_size) {
			memcpy ((char*)data, left_buf + pave->header_size, data_size);
			left_size = left_size - (data_size + pave->header_size);
			// ʣ�µ����� << �Ѿ����Ƶ�����,���Կ�����ô����
			memcpy (left_buf, left_buf + data_size + pave->header_size, left_size);
			//printf ("��pave\n");
			return true;
		} else { // һ֡û��
			memcpy ((char*)data, left_buf + pave->header_size, left_size - pave->header_size);
			data_index = left_size - pave->header_size; 
			left_size = 0; // �����Ѿ���
			return false;
		}
	} else {
		// ʣ�µ�������left_buf����
		if (data_size-data_index <= left_size) {
			memcpy ((char*)data + data_index, left_buf, data_size - data_index);
			left_size = left_size - (data_size - data_index); // left - ���ܴ�С-�Ѿ����ƵĴ�С����ʣ��Ҫ���Ƶģ�=������
			// shift left
			for (int i = 0; i < left_size; i++) {
				left_buf[i] = left_buf[data_size - data_index + i];
			}
			return true; // һ֡���
		} else {
			memcpy ((char*)data + data_index, left_buf, left_size);
			data_index += left_size;
			left_size = 0;
			return false;
		}
	}
	return true;
}