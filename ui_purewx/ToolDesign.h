#ifndef _TK_TOOLDESIGN_H_
#define _TK_TOOLDESIGN_H_

class wxWindow;
class wxToolBar;
class ToolDesign{
private:
	wxToolBar* tool_bar;
public:
	ToolDesign(wxWindow* parent);
	wxToolBar* getToolBar();

	// id 
	static const long ID_TOOL_FILE_OPEN;
};

#endif // _TK_TOOLDESIGN_H_