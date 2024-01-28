#include "../header/MyTaskBar.h"
#include <wx/window.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <thread>


#include "../resources/app_icon.xpm"

MyTaskBarIcon::MyTaskBarIcon()
{
	

	//wxIcon icon;
	//icon.LoadFile(app_icon);
	SetIcon(wxIcon(app_icon));
	//this->Bind(wxEVT_TASKBAR_LEFT_DCLICK, wxTaskBarIconEventHandler(MyTaskBarIcon::onDoubleLeftClick),this);
	//Bind(wxEVT_MENU,wxMenuEventHandler(MyTaskBarIcon::onExit) , this, wxID_EXIT);
	//Bind(wxEVT_MENU,&MyTaskBarIcon::onLogout, this, LOGOUT);
}
MyTaskBarIcon::~MyTaskBarIcon()
{
	
}



wxMenu* MyTaskBarIcon::CreatePopupMenu() {
	wxMenu* menu = new wxMenu;
	menu->Append(LOGOUT, L"注销");
	menu->Append(NETWORK_LOGINER, L"校园网");
	menu->Append(EDUCATION_SYSTEM, L"教务系统");
	menu->Append(ABOUT, L"关于软件");
	menu->AppendSeparator();
	menu->Append(wxID_EXIT, L"退出软件");
	return menu;
}