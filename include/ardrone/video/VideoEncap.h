/**
 * @file video_getdata.h
 * @ brief 从tcp流中获取原始视频数据
 * 
 * @author tkorays
 * @date 2014-6-20
 * @since 1.0.0
 *
 * 原始的视频帧分布在不同的数据包中，因此需要将许多包搜集起来。
 */

#ifndef _TK_VIDEO_GETDATA_H_
#define _TK_VIDEO_GETDATA_H_

namespace whu {
	namespace ardrone {
		/**
		 * @class VideoEncap VideoEncap.h ardrone/video/VideoEncap.h
		 * @brief 用于视频解包
		 */
		class VideoEncap {
		private:
			void* data; // 得到的视频数据
			int data_index; // 当前视频内部数据索引，用于复制数据
			int data_size;
			bool data_over;
			char left_buf[1460*2];
			int left_size;

			void handle_left(void* tcpdata);
		public:
			VideoEncap();
			/*!< tcp包的大小 */
			static int TcpPackSize; 
			/**
			 * @brief 处理tcp数据
			 * @param 原始tcp数据
			 * @return 处理完成
			 */
			bool process(void* tcpdata);
			bool get_h264(void* tcpdata);
			int get_data_size();
			void* get_data() const;
		};
	}
}

#endif // _TK_VIDEO_GETDATA_H_