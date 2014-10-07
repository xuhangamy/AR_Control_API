#include "MainWindow.h"
#include "MenuDesign.h"
#include "ToolDesign.h"
#include "StatusDesign.h"
#include "ClientDesign.h"
#include "WindowEvents.h"

wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)
//EVT_MENU(MenuDesign::ID_MENU_OPEN,nullptr)
EVT_MENU(wxID_EXIT,WindowEvents::OnClose)
EVT_MENU(wxID_ABOUT, WindowEvents::OnAbout)
EVT_MENU(MenuDesign::ID_MENU_OPEN, WindowEvents::OnFileOpen)
wxEND_EVENT_TABLE()


MainWindow::MainWindow(const wxString& title, const wxPoint& pos, wxSize& size, long style) :\
	wxFrame(NULL, wxID_ANY, title, pos, size, style){

		wxInitAllImageHandlers();

		menuBar = nullptr;
		/* 设计菜单 
		MenuDesign* menu_design = new MenuDesign();
		menuBar = menu_design->getMenuBar();
		SetMenuBar(menuBar);
		*/
		toolBar = nullptr;
		/* 设计工具栏 
		ToolDesign* tool_design = new ToolDesign(this);
		toolBar = tool_design->getToolBar();
		SetToolBar(toolBar);
		*/

		statusBar = nullptr;
		/* 设计状态栏 
		StatusDesign* status_design = new StatusDesign(this);
		statusBar = status_design->getStatusBar();
		SetStatusBar(statusBar);
		*/

		ClientDesign* client_design = new ClientDesign(this);
}

MainWindow::~MainWindow(){

}
void MainWindow::OnLeftDown(wxMouseEvent& event){
	//this->CaptureMouse();
	wxPoint pos = this->ClientToScreen(event.GetPosition());
	wxPoint origin = this->GetPosition();
	offset.x = pos.x - origin.y;
	offset.y = pos.y - origin.y;
}

void MainWindow::OnLeftDrag(wxMouseEvent& event){
	wxPoint pt = event.GetPosition(); 
	if (event.Dragging() && event.LeftIsDown()){
		wxPoint pos = this->ClientToScreen(pt);
		this->Move(pos.x - offset.x, pos.y - offset.y);
	}
}

void MainWindow::OnLeftUp(wxMouseEvent& event){
	if (this->HasCapture()){
		//this->ReleaseMouse();
	}
}