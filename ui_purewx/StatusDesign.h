#ifndef _TK_STATUSDESIGN_H_
#define _TK_STATUSDESIGN_H_

class wxStatusBar;
class wxWindow;
class StatusDesign{
private:
	wxStatusBar* status_bar;
public:
	StatusDesign(wxWindow* parent);
	wxStatusBar* getStatusBar();
};


#endif // _TK_STATUSDESIGN_H_