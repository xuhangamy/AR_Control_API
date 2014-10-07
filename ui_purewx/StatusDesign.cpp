#include "StatusDesign.h"
#include "wxinc.h"

StatusDesign::StatusDesign(wxWindow* parent){
	status_bar = new wxStatusBar(parent, wxID_ANY, 0, _T("statusBar"));
	int __wxStatusBarWidths_1[1] = { -10 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	status_bar->SetFieldsCount(1, __wxStatusBarWidths_1);
	status_bar->SetStatusStyles(1, __wxStatusBarStyles_1);
	status_bar->SetStatusText(_T("Ready..."));

}

wxStatusBar* StatusDesign::getStatusBar(){
	return status_bar;
}