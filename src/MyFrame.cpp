///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../header/MyFrame.h"
#include <wx/log.h> 
#include <wx/panel.h> 
#include<thread>
#include<chrono>
#include<hv/requests.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/msw/registry.h>
#include "hv/icmp.h"
#include <wx/msgdlg.h>

#include "../resources/app_icon.xpm"


///////////////////////////////////////////////////////////////////////////

MyFrame::MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size, style),
	config("GXU_Tools", "DleXoX", "config.ini", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH)
{
	SetSize(FromDIP(wxSize(271, 200)));
	SetIcon(wxIcon(app_icon));


	// 读取配置数据
	wxString account, password;
	int ISPValue;
	bool popAboutDialog;
	config.Read("Login/Account", &account, wxT(""));
	config.Read("Login/Password", &password, wxT(""));
	config.Read("Login/ISP", &ISPValue, 0);
	config.Read("POP_WHEN_START", &popAboutDialog, true);
	config.Read("SELF_START", &selfStart, false);
	
	if(popAboutDialog) ad->Show();


	this->SetSizeHints(FromDIP(wxSize(-1, 1)), wxDefaultSize);

	loginPanel = new wxPanel(this);
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer(3, 2, 0, 0);
	fgSizer2->AddGrowableCol(0);
	fgSizer2->SetFlexibleDirection(wxBOTH);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText1 = new wxStaticText(loginPanel, wxID_ANY, wxT("账    号"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	fgSizer2->Add(m_staticText1, 0, wxALIGN_CENTER_VERTICAL | wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	accountInput = new wxTextCtrl(loginPanel, wxID_ANY, account, wxDefaultPosition, wxDefaultSize, 0);
	//accountInput->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("微软雅黑")));
	accountInput->SetMinSize(FromDIP(wxSize(200, 30)));


	fgSizer2->Add(accountInput, 1, wxALIGN_CENTER_VERTICAL | wxALL | wxEXPAND, 5);

	m_staticText2 = new wxStaticText(loginPanel, wxID_ANY, wxT("密    码"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	fgSizer2->Add(m_staticText2, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 5);

	passwordInput = new wxTextCtrl(loginPanel, wxID_ANY, password, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	passwordInput->SetMinSize(FromDIP(wxSize(200, 30)));

	fgSizer2->Add(passwordInput, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);


	m_staticText3 = new wxStaticText(loginPanel, wxID_ANY, wxT("运 营 商"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);

	fgSizer2->Add(m_staticText3, 1, wxALIGN_CENTER_VERTICAL | wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
	wxBoxSizer* bSizer21 = new wxBoxSizer(wxHORIZONTAL);


	wxArrayString ISPChoices;

	ISPChoices.push_back(wxString::FromUTF8("中国移动"));
	ISPChoices.push_back(wxString::FromUTF8("中国联通"));
	ISPChoices.push_back(wxString::FromUTF8("中国电信"));
	ISPChoices.push_back(wxString::FromUTF8("校园网"));

	ISP = new wxChoice(loginPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, ISPChoices, 0);
	ISP->SetSelection(ISPValue);
	ISP->SetMaxSize(FromDIP(wxSize(150, -1)));
	 
	selfBoostChecker = new wxCheckBox(loginPanel, wxID_ANY, wxT("开机自启"), wxDefaultPosition, wxDefaultSize, 0);
	selfBoostChecker->SetValue(selfStart);
	bSizer21->Add(ISP, 1, wxALL, 5);
	bSizer21->Add(selfBoostChecker, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	fgSizer2->Add(bSizer21, 1, wxEXPAND, 5);

	bSizer2->Add(fgSizer2, 5, wxEXPAND, 5);

	loginBtn = new wxButton(loginPanel, wxID_ANY, L"登录", wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(loginBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);
	 
	loginPanel->SetSizerAndFit(bSizer2);
	this->Layout() ;
	this->Centre(wxBOTH);

	m_statusBar1 = this->CreateStatusBar(2, wxSTB_SIZEGRIP, wxID_ANY);
	m_statusBar1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));



	int widhts[] = { 60,-1 };
	m_statusBar1->SetStatusWidths(2, widhts);
	conectStatus = new wxStaticText(this->m_statusBar1, wxID_ANY, "未连接", wxPoint(5, 5));
	conectStatus->SetForegroundColour(wxColor(220, 20, 60));



	examFrame = new ExamFrame(this);
	taskBarIcon = new MyTaskBarIcon();


	loginBtn->Bind(wxEVT_BUTTON, &MyFrame::loginBtnClickHandler, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MyFrame::onClose, this);
	loginPanel->Bind(wxEVT_CHAR_HOOK, &MyFrame::onKeyDown, this);
	taskBarIcon->Bind(wxEVT_TASKBAR_LEFT_DCLICK, &MyFrame::onTaskBarIconDoubleLeftClick, this);
	taskBarIcon->Bind(wxEVT_MENU, &MyFrame::onExit, this, wxID_EXIT);
	taskBarIcon->Bind(wxEVT_MENU, &MyFrame::onLogout, this, LOGOUT);
	taskBarIcon->Bind(wxEVT_MENU, &MyFrame::onEducationSystem, this, EDUCATION_SYSTEM);
	taskBarIcon->Bind(wxEVT_MENU, &MyFrame::onNetworkLoginer, this, NETWORK_LOGINER);
	taskBarIcon->Bind(wxEVT_MENU, &MyFrame::onShowAboutDialog, this, ABOUT);
	selfBoostChecker->Bind(wxEVT_CHECKBOX, &MyFrame::OnSelfBoostChecker, this);

	if(selfStart) targetLoginBtn();


	std::thread checkOnline([this] {
		while (this->running) {
			this->checkConection();
		}
		});
	checkOnline.detach();




}

MyFrame::~MyFrame()
{
	delete taskBarIcon;
	delete ad;

}


void MyFrame::loginBtnClickHandler(wxEvent& event) {
	loging_in = !loging_in;
	if (!loging_in) {
		loginBtn->SetLabelText(L"登  录");
		enableLoginPageInput();
		m_statusBar1->SetStatusText(L"自动登录服务未运行", 1);
		return;
	}

	wxString url = "http://172.17.0.2:801/eportal/?c=ACSetting&a=login&wlanacname=ME60-1&wlanacip=172.17.0.2";
	wxString cno = accountInput->GetValue();
	wxString pwd = passwordInput->GetValue();
	std::map<int, wxString> ispMap{ {0,"@cmcc"},{1,"@unicom"}, {2,"@telecom"}, {3,""} };
	int isp = ISP->GetSelection();
	url << "&DDDDD=" << cno << ispMap[ISP->GetSelection()] << "&upass=" << pwd;
	wxLogDebug(wxString::Format(wxT("url=%s\tselect=%d"), url, isp));

	std::thread loginThread([this, url] {
		wxDateTime currentTime;
		int hour,weekDay;
		bool inValidTime = false;
		while (this->loging_in) {
			currentTime = wxDateTime::Now();
			hour = currentTime.GetHour();
			weekDay = currentTime.GetWeekDay();
			//周一到周五凌晨6点是断网时间
			inValidTime = (hour < 6) && (weekDay >= 1 && weekDay <= 5);
			if (!online && !inValidTime||true) {
				requests::get(url);
				wxSleep(3);
			}
			else wxSleep(10);
		}
		});
	loginThread.detach();
	disableLoginPageInput();
	loginBtn->SetLabelText(L"停  止");
	m_statusBar1->SetStatusText(L"自动登录服务运行中！", 1);
	return;

}


void MyFrame::onClose(wxCloseEvent& event)
{

	this->Hide();
}

void MyFrame::onLogout(wxEvent& event)
{
	if (!loging_in) {
		wxMessageBox(L"自动登录服务未运行", L"注销失败", wxOK);
		return;
	}
	std::thread logoutThread([] {
		requests::get("http://172.17.0.2:801/eportal/?c=ACSetting&a=Logout&loginMethod=1&protocol=http%3A&hostname=172.17.0.2&port=&iTermType=1&wlanuserip=null&wlanacip=null&wlanacname=null&redirect=null&session=null&vlanid=undefined&mac=00-00-00-00-00-00&ip=&queryACIP=0&jsVersion=2.4.3");
		});
	logoutThread.detach();
	targetLoginBtn();
	wxMessageBox(L"若注销不成功,请前往自服务中心手动下线设备：\n\
				http://self.gxu.edu.cn/",
		L"注销完成", wxOK);
	this->Show();
}

void MyFrame::onEducationSystem(wxEvent& event)
{
	if (examFrame->IsShown()) {
		examFrame->Hide();
	}
	else {
		examFrame->Show();
	}
}

void MyFrame::onNetworkLoginer(wxEvent& event)
{
	if (IsShown()) Hide();
	else Show();
}

void MyFrame::onExit(wxEvent& event)
{
	wxFileConfig config("GXU_Tools", "DleXoX", "config.ini", "",
		wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	config.Write("Login/Account", accountInput->GetValue());
	config.Write("Login/Password", passwordInput->GetValue());
	config.Write("Login/ISP", ISP->GetSelection());


	// 确保写入数据被保存到文件
	config.Flush();
	
	loging_in = false;
	running = false;
	examFrame->Destroy();
	Destroy();
}

void MyFrame::onKeyDown(wxKeyEvent& event) {

	//wxLogDebug(wxString::Format(wxT("%i,to,%i"), event.GetKeyCode()), WXK_RETURN);
	if (event.GetKeyCode() != WXK_RETURN && event.GetKeyCode() != WXK_NUMPAD_ENTER) event.Skip();
	else targetLoginBtn();
}

void MyFrame::onShowAboutDialog(wxEvent& event)
{
	ad->Show();
}

void MyFrame::onTaskBarIconDoubleLeftClick(wxTaskBarIconEvent& event) {
	if (examFrame->IsShown())  examFrame->Hide();
	else  examFrame->Show();
}







void MyFrame::disableLoginPageInput()
{
	accountInput->Disable();
	passwordInput->Disable();
	ISP->Disable();
}
void MyFrame::enableLoginPageInput()
{
	accountInput->Enable();
	passwordInput->Enable();
	ISP->Enable();
}

void MyFrame::OnSelfBoostChecker(wxCommandEvent& event)
{
	wxRegKey regKey(wxRegKey::HKCU, "Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if (event.IsChecked()) {
		wxString exePath = wxStandardPaths::Get().GetExecutablePath();
		regKey.SetValue("GXU_Tools", exePath);
		config.Write("SELF_START", true);
		selfStart = true;
	}
	else {
		regKey.DeleteValue("GXU_Tools");
		config.Write("SELF_START", false);
		selfStart = false;
	}
	config.Flush();

}

void MyFrame::checkConection()
{
	if (online != isConnected()) {
		online = !online;
	}

	if (online) {
		conectStatus->SetForegroundColour(wxColor(46, 139, 87));
		conectStatus->SetLabelText(L"已连接");
	}
	else {
		conectStatus->SetForegroundColour(wxColor(220, 20, 60));
		conectStatus->SetLabelText(L"未连接");
	}
	if(this->IsShown()) wxSleep(1);
	else wxSleep(10);

}

void MyFrame::targetLoginBtn()
{
	wxCommandEvent e(wxEVT_BUTTON, loginBtn->GetId());
	loginBtn->GetEventHandler()->ProcessEvent(e);

}




