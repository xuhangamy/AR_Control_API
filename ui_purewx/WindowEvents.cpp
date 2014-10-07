#include "WindowEvents.h"
#include "MenuDesign.h"

void WindowEvents::OnFileOpen(wxCommandEvent& event){
	wxMessageBox(_T("title"), _T("content"));
}
void WindowEvents::OnClose(wxCommandEvent& event){
	Close(true);
}
void WindowEvents::OnAbout(wxCommandEvent& event){
	wxMessageBox(_("help content"), _("help"));
}
void WindowEvents::OnCloseButton(wxMouseEvent& event){
	int trp = 255;
	for (size_t i = 0; i < 40; i++){
		Sleep(5);
		this->SetTransparent(trp = trp - 1);
	}
	Sleep(500);
	Close(true);
}