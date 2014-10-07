#ifndef _TK_APPCONFIG_H_
#define _TK_APPCONFIG_H_

#include "wxinc.h"
#include <stdint.h>

typedef struct app_config_{
	wxString title = _T("ARDrone¿ØÖÆ³ÌÐò");
	wxString author = _T("tkorays");
	wxPoint pos = wxPoint((wxSystemSettings::GetMetric(wxSYS_SCREEN_X, NULL) - 900) / 2, (wxSystemSettings::GetMetric(wxSYS_SCREEN_Y, NULL) - 660) / 2);
	wxSize size = wxSize(900, 660);
	long winstyle = wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX & ~wxRESIZE_BORDER & wxFULLSCREEN_ALL;
	int left_client_width = 500;
	int right_client_width = 300;
} app_config;


#endif // _TK_APPCONFIG_H_