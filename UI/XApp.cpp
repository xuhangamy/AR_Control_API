#include "XApp.h"
#include "XConfig.h"
#include "XWindow.h"
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>

IMPLEMENT_APP(XApp)

bool XApp::OnInit() {
	wxInitAllImageHandlers();
	wxXmlResource::Get()->InitAllHandlers();
	if (!wxXmlResource::Get()->Load(wxT(XRC_FILE))) {
		wxAbort();
	}
	XWindow* win = new XWindow();
	win->Show();
	return true;
}