#include "XWindow.h"
#include "XConfig.h"
#include <wx/xrc/xmlres.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>

wxBEGIN_EVENT_TABLE(XWindow,wxFrame)

wxEND_EVENT_TABLE()

XWindow::XWindow() {
	
	if (!wxXmlResource::Get()->LoadFrame(this, NULL, wxT("esdc_mainwin"))) {
		abort(); // ������Ӧ�ú�������ؽ���
	}
	
	// �رհ�ť�¼�
	wxStaticText* closeBtn = XRCCTRL(*this, "close_btn", wxStaticText);
	closeBtn->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(XWindow::OnCloseButton),NULL,this);

	// ��Ƶ���̳߳�ʼ��
	wxStaticBitmap* video_ctrl = XRCCTRL(*this, "video_frame", wxStaticBitmap);
	video_thead = new VideoThread(video_ctrl);
}
XWindow::~XWindow() {

}

void XWindow::OnCloseButton(wxMouseEvent& event) {
	this->SetTransparent(240);
	wxStaticText* closeBtn = XRCCTRL(*this, "close_btn", wxStaticText);
	wxSleep(1);
	Close(true);
}