#ifndef _TK_H264DECODER_H_
#define _TK_H264DECODER_H_
#include "../basic/type.h"

struct AVFormatContext;
struct AVCodecContext;
struct AVIOContext;
struct AVCodec;
struct AVFrame;
struct AVPacket;

namespace whu{
	struct buffer_data {
		uint8_t *ptr;
		size_t size; 
	};
	class H264Decoder{
	private:
		AVFormatContext* pFormatCtx;
		AVCodecContext* pCodecCtx;
		AVIOContext* pIOCtx;
		AVCodec* pCodec;
		AVFrame* pFrame;
		AVFrame* pFrameYUV;
		void error_handle();

		uint8_t* buffer;
		uint8_t* avio_ctx_buffer;
		size_t buffer_size;
		int avio_ctx_buffer_size;
		uint8_t* out_buffer;
		AVPacket* packet;

		

		bool isOpen;
		bool valid;
		int skip;
	public:
		struct buffer_data bd;
		H264Decoder();
		~H264Decoder();
		bool is_ok();
		void process(void* data, int size, void(*callback)(void*p));
		void* img_data;
		bool data_ready;
	};
}
#endif // _TK_H264DECODER_H_