#ifndef _TK_XAPP_H_
#define _TK_XAPP_H_
#include <wx/wxprec.h>
#include <wx/app.h>

class XApp :public wxApp {
public:
	virtual bool OnInit();
};


#endif // _TK_XAPP_H_