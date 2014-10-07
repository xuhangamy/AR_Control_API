#ifndef _TK_VIDEO_THREAD_H_
#define _TK_VIDEO_THREAD_H_


#include <wx/thread.h>
#include <stdint.h>

namespace whu {
	class TcpClient;
}
class wxStaticBitmap;


class VideoThread :public wxThread {
public:
	bool run;
	VideoThread(wxStaticBitmap* statbmp);
	void* Entry();
private:
	wxStaticBitmap* stat_bmp_ctrl;

	whu::TcpClient* videoClient;

	/// 输出的会在函数里面分配内存
	bool decode(uint8_t* orgdata, int size, uint8_t* out_buf);
};

#endif // _TK_VIDEO_THREAD_H_