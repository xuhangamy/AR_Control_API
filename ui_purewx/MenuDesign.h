#ifndef _TK_MENUDESIGN_H_
#define _TK_MENUDESIGN_H_

class wxMenuBar;
class MenuDesign{
private:
	wxMenuBar* menu_bar;
public:

	MenuDesign();
	wxMenuBar* getMenuBar();

	// id
	static const long ID_MENU_OPEN;
	static const long ID_MENU_HELP;

};



#endif // _TK_MENUDESIGN_H_