#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern "C"{
#ifdef HAVE_AV_CONFIG_H
#undef HAVE_AV_CONFIG_H
#endif

#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <SDL.h>
}

int main(int argc, char** argv) {
	AVFormatContext* pFormatCtx;
	int i, videoindex;
	AVCodecContext* pCodeCtx;
	AVCodec* pCodec;

	char filepath[] = "test.h264";

	av_register_all(); // 注册组件

	avformat_network_init(); // 支持网络流

	pFormatCtx = avformat_alloc_context();

	AVFrame* pFrame, *pFrameYUV;
	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();

	uint8_t *out_buffer;



	delete[] out_buffer;
	av_free(pFrameYUV);
	avcodec_close(pCodeCtx);
	avformat_close_input(&pFormatCtx);
}