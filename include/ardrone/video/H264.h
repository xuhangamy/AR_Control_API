//---------------------------------------------------------------------------
#ifndef H264H
#define H264H
//---------------------------------------------------------------------------
extern "C" {
#include "../../ffmpeg/libavcodec/avcodec.h"
#include "../../ffmpeg/libavformat/avformat.h"
#include "../../ffmpeg/libswscale/swscale.h"
};
//---------------------------------------------------------------------------
class H264 {
   unsigned char *buffer;
   unsigned char *outBuffer;
   unsigned char *displayBuffer;
   int bufferSize, maxBufferSize;
   unsigned char *currFrame;
   int currFrameSize;

   AVFrame *pFrame, *pFrameOutput;
   int frameFinished;
   AVPacket packet;
   struct SwsContext *img_convert_ctx;
   AVCodecContext *pCodecCtx;
   AVCodec *pCodec;
public:
   H264();
   ~H264();
   bool is_ok;
   void addFrame( unsigned char *buffer, int size );
   void add( unsigned char *buffer, int size );
   unsigned char *getImage();
};
//---------------------------------------------------------------------------
#endif
