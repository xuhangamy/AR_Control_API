// 解决socket头文件包含错误
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
		wxMessageBox(wxT("视频流初始化错误"), wxT("警告"));
		abort();
	}
	run = true;
}
// 在这里面处理视频吧
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
	av_register_all(); // 注册组件
	avformat_network_init(); // 支持网络流

	pFormatCtx = avformat_alloc_context(); // 初始化AVFormatContext
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
		if (encap.process(buf)) { // 一帧处理好了
			// 数据： encap.get_data()
			// 数据大小: encap.get_data_size()
			if (avformat_find_stream_info(pFormatCtx,NULL)<0) { // 查找信息
				continue; // 继续
			}
			// 获取视频流id
			for (int i = videoIndex+1; i < pFormatCtx->nb_streams; i++) {
				if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
					videoIndex = i;
					break;
				}
			}
			// 没有找到视频流
			if (videoIndex == -1) {
				continue;
			}
			if (pCodecCtx == NULL) {
				pCodecCtx = pFormatCtx->streams[videoIndex]->codec;
				pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
				out_buffer = new uint8_t[avpicture_get_size(PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height)];//分配AVFrame所需内存
			}
			if (pCodec == NULL || avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
				wxMessageBox(wxT("解码器错误"), wxT("错误"));
				abort();
			} 
			
			
			avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);//填充AVFrame
			packet = (AVPacket*)malloc(sizeof(AVPacket)); // 解码器前存储AVPacket
			av_new_packet(packet, pCodecCtx->width*pCodecCtx->height);
			while (av_read_frame(pFormatCtx,packet)>0) { // 循环获取
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