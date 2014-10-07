//---------------------------------------------------------------------------
#include <ardrone/video/H264.h>



//---------------------------------------------------------------------------
H264::H264()
{
   maxBufferSize = 1024 * 1024;
   buffer = new unsigned char[ maxBufferSize ];
   outBuffer = new unsigned char[ maxBufferSize ];
   displayBuffer = new unsigned char[ maxBufferSize ];
   bufferSize = 0;

   currFrame = new unsigned char[ maxBufferSize ];
   currFrameSize = 0;

   av_register_all();

   pCodec = avcodec_find_decoder( CODEC_ID_H264 );
   if( pCodec == NULL ) {
	   is_ok = false;
	   return;
   }

   pCodecCtx = avcodec_alloc_context3(pCodec);

   pCodecCtx->pix_fmt = PIX_FMT_YUV420P;
   pCodecCtx->skip_frame = AVDISCARD_DEFAULT;
   pCodecCtx->error_concealment = FF_EC_GUESS_MVS | FF_EC_DEBLOCK;
   pCodecCtx->skip_loop_filter = AVDISCARD_DEFAULT;
   pCodecCtx->workaround_bugs = FF_BUG_AUTODETECT;
   pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
   pCodecCtx->codec_id = CODEC_ID_H264;
   pCodecCtx->skip_idct = AVDISCARD_DEFAULT;

   if( avcodec_open2( pCodecCtx, pCodec ,NULL) < 0 ) {
	   is_ok = false;
	   return;
   }

   pFrame = av_frame_alloc ();

   pFrameOutput = av_frame_alloc ();
   pFrameOutput->data[ 0 ] = outBuffer;
   *pFrameOutput->linesize = 640 * 3;

   frameFinished = 1;

   img_convert_ctx = NULL;

   img_convert_ctx = sws_getCachedContext( img_convert_ctx, 640, 	360, pCodecCtx->pix_fmt, 640, 360, PIX_FMT_RGB24,
         SWS_FAST_BILINEAR, NULL, NULL, NULL );

   av_init_packet( &packet );
   is_ok = true;
}
//---------------------------------------------------------------------------
H264::~H264()
{
   delete[] buffer;
   delete[] outBuffer;
   delete[] displayBuffer;
}
//---------------------------------------------------------------------------
void H264::addFrame( unsigned char *buffer, int size )
{
   packet.data = buffer;
   packet.size = size;

   avcodec_decode_video2( pCodecCtx, pFrame, &frameFinished, &packet );
   sws_scale( img_convert_ctx, pFrame->data, pFrame->linesize, 0, 360,
              pFrameOutput->data, pFrameOutput->linesize );
}
//---------------------------------------------------------------------------
void H264::add( unsigned char *buffer, int size )
{
   if( bufferSize + size < maxBufferSize ) {
      memcpy( this->buffer + bufferSize, buffer, size );
      bufferSize += size;
   }
}
//---------------------------------------------------------------------------
unsigned char *H264::getImage()
{
   char b[ 200 ];
   unsigned short int *p16;
   int header, payload;
   int moreFrames;

   moreFrames = 1;
   while( moreFrames == 1 ) {
      moreFrames = 0;
      for( int i = 0; i < bufferSize; i++ ) {
         if( ( buffer[ i ] == 'P' ) &&
             ( buffer[ i + 1 ] == 'a' ) &&
             ( buffer[ i + 2 ] == 'V' ) &&
             ( buffer[ i + 3 ] == 'E' ) ) {

//         sprintf( b, "paVE %d =================", i );
//         FormMain->Memo->Lines->Add( b );

//         sprintf( b, "version %d", buffer[ i + 4 ] );
//         FormMain->Memo->Lines->Add( b );

//         sprintf( b, "video codec %d", buffer[ i + 5 ] );
//         FormMain->Memo->Lines->Add( b );

            p16 = ( unsigned short int * )( buffer + i + 6 );
            header = *p16;
//         sprintf( b, "header size %d", header );
//         FormMain->Memo->Lines->Add( b );

            p16 = ( unsigned short int * )( buffer + i + 8 );
            payload = *p16;
//         sprintf( b, "payload size %d", payload );
//         FormMain->Memo->Lines->Add( b );

//            sprintf( b, "frame type %d", buffer[ i + 30 ] );
//            FormMain->Memo->Lines->Add( b );

            if( header + payload < bufferSize ) {

               currFrameSize = header + payload;
               memcpy( currFrame, buffer + i, currFrameSize );

               memcpy( buffer, buffer + currFrameSize, bufferSize - currFrameSize );
               bufferSize -= currFrameSize;

               addFrame( currFrame, currFrameSize );

               // convert image for display
               unsigned char *src, *dst;
               unsigned char *p, q;

               //src = outBuffer + 359 * 640 * 3;
			   src = outBuffer;
               dst = displayBuffer;
			   
               for( int j = 0; j < 360; j++ ) {
                  memcpy( dst, src, 640 * 3 );

                  p = dst;
                  for( int i = 0; i < 640; i++ ) {
                     q = *p;
                     *p = *( p + 2 );
                     *( p + 2 ) = q;
                     p += 3;
                  }
                  dst += ( 640 * 3 );
                  src += ( 640 * 3 );
               }
			   
               moreFrames = 1;
            } else {
               moreFrames = 0;
            }
            break;
         }
      }
   }
   return( displayBuffer );
}
//---------------------------------------------------------------------------

