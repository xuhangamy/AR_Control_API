#include "App.h"
#include "MainWindow.h"
#include "AppConfig.h"

wxIMPLEMENT_APP(App);

bool App::OnInit(){
	// ´´½¨´°¿Ú
	app_config config;
	MainWindow* window = new MainWindow(config.title,config.pos,config.size,config.winstyle);
	window->Show();
	return true;
}