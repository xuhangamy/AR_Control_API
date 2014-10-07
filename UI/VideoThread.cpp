// ���socketͷ�ļ���������
#define WIN32_LEAN_AND_MEAN

#include "VideoThread.h"
#include <wx/wx.h>
#include <ardrone/ardrone.h>
using namespace whu::ardrone;

extern "C"
{
#ifdef HAVE_AV_CONFIG_H
#undef HAVE_AV_CONFIG_H
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <SDL.h>
}



VideoThread::VideoThread(wxStaticBitmap* statbmp) {
	stat_bmp_ctrl = statbmp;
	videoClient = new whu::TcpClient(ARDRONE_IP, VIDEO_PORT);
	if (!videoClient->is_valid()) {
		wxMessageBox(wxT("��Ƶ����ʼ������"), wxT("����"));
		abort();
	}
	run = true;
}
// �������洦����Ƶ��
void* VideoThread::Entry() {
	if (!run) {
		return NULL;
	} // else

	/////////////////////////////////////////////////////
	uint8_t *out_buffer;
	uint8_t* iobuffer = (uint8_t*)av_malloc(32768);
	AVFormatContext* pFormatCtx = NULL;
	AVCodecContext* pCodecCtx = NULL;
	AVIOContext* pIOCtx = NULL;
	AVCodec* pCodec = NULL;
	av_register_all(); // ע�����
	avformat_network_init(); // ֧��������

	pFormatCtx = avformat_alloc_context(); // ��ʼ��AVFormatContext
	pIOCtx = avio_alloc_context(iobuffer, 32768, 0, out_buffer, NULL, NULL, NULL);
	pFormatCtx->pb = pIOCtx;

	int videoIndex = -1;
	AVFrame* pFrame;
	AVFrame* pFrameYUV;
	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();
	
	AVPacket* packet; 
	int got_picture;
	////////////////////////////////////////////////////
	const int max_buf_size = VideoEncap::TcpPackSize;
	char* buf = (char*)malloc(max_buf_size);
	VideoEncap encap;
	while (run) {
		videoClient->recv(buf, max_buf_size, NULL);
		if (encap.process(buf)) { // һ֡�������
			// ���ݣ� encap.get_data()
			// ���ݴ�С: encap.get_data_size()
			if (avformat_find_stream_info(pFormatCtx,NULL)<0) { // ������Ϣ
				continue; // ����
			}
			// ��ȡ��Ƶ��id
			for (int i = videoIndex+1; i < pFormatCtx->nb_streams; i++) {
				if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
					videoIndex = i;
					break;
				}
			}
			// û���ҵ���Ƶ��
			if (videoIndex == -1) {
				continue;
			}
			if (pCodecCtx == NULL) {
				pCodecCtx = pFormatCtx->streams[videoIndex]->codec;
				pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
				out_buffer = new uint8_t[avpicture_get_size(PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height)];//����AVFrame�����ڴ�
			}
			if (pCodec == NULL || avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
				wxMessageBox(wxT("����������"), wxT("����"));
				abort();
			} 
			
			
			avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);//���AVFrame
			packet = (AVPacket*)malloc(sizeof(AVPacket)); // ������ǰ�洢AVPacket
			av_new_packet(packet, pCodecCtx->width*pCodecCtx->height);
			while (av_read_frame(pFormatCtx,packet)>0) { // ѭ����ȡ
				if (packet->stream_index==videoIndex) {
					avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
				}
				if (got_picture) {
					
				}
				av_free_packet(packet);
			}
			
			
		}
	}
	return NULL;
}

bool VideoThread::decode(uint8_t* orgdata, int size, uint8_t* out_buf) {

	return true;
}