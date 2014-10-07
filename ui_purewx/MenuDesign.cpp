#include "MenuDesign.h"
#include "wxinc.h"

const long MenuDesign::ID_MENU_OPEN = 1;
const long MenuDesign::ID_MENU_HELP = 2;


MenuDesign::MenuDesign(){
	wxMenu* menu_file = new wxMenu();
	wxMenuItem* menu_file_open = new wxMenuItem(menu_file, ID_MENU_OPEN, _T("打开\tCtrl+0"), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* menu_file_exit = new wxMenuItem(menu_file, wxID_EXIT, _T("退出\tCtrl+E"), wxEmptyString, wxITEM_NORMAL);
	menu_file->Append(menu_file_open);
	menu_file->Append(menu_file_exit);

	wxMenu* menu_help = new wxMenu();
	wxMenuItem* menu_help_abut = new wxMenuItem(menu_help, wxID_ABOUT, _T("关于\tCtrl+A"), wxEmptyString, wxITEM_NORMAL);
	menu_help->Append(menu_help_abut);

	menu_bar = new wxMenuBar();
	menu_bar->Append(menu_file, _T("文件"));
	menu_bar->Append(menu_help, _T("帮助"));
}

wxMenuBar* MenuDesign::getMenuBar(){
	return menu_bar;
}



