#ifndef _TK_XWINDOW_H_
#define _TK_XWINDOW_H_

#include <wx/frame.h>
#include "VideoThread.h"

class XWindow :public wxFrame {
public:
	XWindow();
	virtual ~XWindow();
private:
	
	VideoThread* video_thead;

	void OnCloseButton(wxMouseEvent& event);
	wxDECLARE_EVENT_TABLE();
};

#endif // _TK_XWINDOW_H_