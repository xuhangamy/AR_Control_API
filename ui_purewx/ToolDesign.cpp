#include "ToolDesign.h"
#include "wxinc.h"

const long ToolDesign::ID_TOOL_FILE_OPEN = 3;

ToolDesign::ToolDesign(wxWindow* parent){
	tool_bar = new wxToolBar(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER);

	/* wxToolBarToolBase* tb_open = \ */
	tool_bar->AddTool(ID_TOOL_FILE_OPEN, _T("Open"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("打开文件"), _T("打开文件"));

	tool_bar->Realize();
}

wxToolBar* ToolDesign::getToolBar(){
	return tool_bar;
}