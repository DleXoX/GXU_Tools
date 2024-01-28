#pragma once
#include <wx/taskbar.h>


class MyTaskBarIcon :public wxTaskBarIcon {
private:
	
public:
	MyTaskBarIcon();
	~MyTaskBarIcon(); 

	virtual wxMenu* CreatePopupMenu() override;
};

enum taskBarEnum
{
	LOGOUT = 10001,
	ABOUT,
	EDUCATION_SYSTEM,
	NETWORK_LOGINER
};