#ifndef _TK_WINDOWEVENT_H_
#define _TK_WINDOWEVENT_H_

#include "wxinc.h"

class WindowEvents :public wxTopLevelWindow{
public:
	WindowEvents(wxFrame* win);
	void OnClose(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnFileOpen(wxCommandEvent& event);
	void OnCloseButton(wxMouseEvent& event);
};


#endif // _TK_WINDOWEVENT_H_