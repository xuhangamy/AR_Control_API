#ifndef _TK_MAIN_WINDOW_H_
#define _TK_MAIN_WINDOW_H_

#include "wxinc.h"

class MainWindow :public wxFrame{
public:
	MainWindow(const wxString& title, const wxPoint& pos, wxSize& size, long style);
	~MainWindow();
	void OnLeftDown(wxMouseEvent& event);
	void OnLeftUp(wxMouseEvent& event);
	void OnLeftDrag(wxMouseEvent& event);
private:
	wxMenuBar* menuBar;
	wxToolBar* toolBar;
	wxStatusBar* statusBar;
	wxPoint offset;

	wxDECLARE_EVENT_TABLE();
};


#endif // _TK_MAIN_WINDOW_H_