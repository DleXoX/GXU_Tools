#pragma once
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/checkbox.h>
#include"../header/MyTaskBar.h"
#include"../header/ExamFrame.h"
#include "AboutDialog.h"
#include <wx/fileconf.h>
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame
///////////////////////////////////////////////////////////////////////////////
class MyFrame : public wxFrame
{
private:

protected:
	wxPanel* loginPanel;
	wxStaticText* m_staticText1;
	wxTextCtrl* accountInput;
	wxStaticText* m_staticText2;
	wxTextCtrl* passwordInput;
	wxStaticText* m_staticText3;
	wxChoice* ISP;
	wxCheckBox* selfBoostChecker;
	wxButton* loginBtn;
	wxStatusBar* m_statusBar1;

	MyTaskBarIcon* taskBarIcon;
	ExamFrame* examFrame;
	wxStaticText* conectStatus;
	//wxStaticText* loginServiceStatus;

	AboutDialog* ad = new AboutDialog(nullptr);
	bool online = false;
	bool loging_in = false;
	bool running = true;
	int cont = 0;



	void loginBtnClickHandler(wxEvent& event);
	void onClose(wxCloseEvent& event);
	void onExit(wxEvent& event);
	void onLogout(wxEvent& event);
	void onEducationSystem(wxEvent& event);
	void onNetworkLoginer(wxEvent& event);
	void onKeyDown(wxKeyEvent& event);
	void onShowAboutDialog(wxEvent& event);
	void onTaskBarIconDoubleLeftClick(wxTaskBarIconEvent& event);
	void OnSelfBoostChecker(wxCommandEvent& event);
	void enableLoginPageInput();
	void disableLoginPageInput();



public:
	bool selfStart;
	wxFileConfig config;
	void checkConection();
	void targetLoginBtn();
	MyFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("校园网登录器"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(271, 220), long style = wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));

	~MyFrame();

};

