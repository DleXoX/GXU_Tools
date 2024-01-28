////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../header/AboutDialog.h"
#include "../resources/app_icon.xpm"
#include "../resources/gxust80.xpm"
#include <wx/fileconf.h>


///////////////////////////////////////////////////////////////////////////



AboutDialog::AboutDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	SetSize(FromDIP(wxSize(321, 455)));
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer(0, 0);
	gbSizer1->SetFlexibleDirection(wxBOTH);
	gbSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	software_logo = new wxGenericStaticBitmap(this, wxID_ANY, wxBitmap(app_icon), wxDefaultPosition, wxDefaultSize, 0);
	software_logo->SetMinSize(FromDIP(wxSize(90, 90)));
	software_logo->SetScaleMode(wxStaticBitmapBase::ScaleMode::Scale_AspectFit);

	gbSizer1->Add(software_logo, wxGBPosition(0, 0), wxGBSpan(1, 1), wxTOP | wxLEFT | wxALIGN_RIGHT | wxALIGN_BOTTOM, 20);

	about_topic = new wxStaticText(this, wxID_ANY, wxT("GXU_Tools (V2.1)"), wxDefaultPosition, wxDefaultSize, 0);
	about_topic->SetLabelMarkup(wxT("GXU_Tools (V2.1)"));
	about_topic->Wrap(-1);
	about_topic->SetFont(wxFont(16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Times New Roman")));

	gbSizer1->Add(about_topic, wxGBPosition(0, 1), wxGBSpan(1, 3), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	author_text = new wxStaticText(this, wxID_ANY, wxT("作者：DleXoX"), wxDefaultPosition, wxDefaultSize, 0);
	author_text->Wrap(-1);
	author_text->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("微软雅黑")));

	gbSizer1->Add(author_text, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL, 5);

	friend_link_label = new wxStaticText(this, wxID_ANY, wxT("友情链接："), wxDefaultPosition, wxDefaultSize, 0);
	friend_link_label->Wrap(-1);
	friend_link_label->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("微软雅黑")));

	gbSizer1->Add(friend_link_label, wxGBPosition(4, 1), wxGBSpan(1, 1), wxALL, 5);

	github_link = new wxHyperlinkCtrl(this, wxID_ANY, wxT("项目GitHub链接"), wxT("https://github.com/DleXoX/GXU_Tools"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE);
	gbSizer1->Add(github_link, wxGBPosition(2, 1), wxGBSpan(1, 1), wxALL, 5);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);

	kx_logo = new wxStaticBitmap(this, wxID_ANY, wxBitmap(gxust80), wxDefaultPosition, wxDefaultSize, 0);
	kx_logo->SetMinSize(FromDIP(wxSize(80, 80)));

	bSizer4->Add(kx_logo, 0, wxALL, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	kx_text = new wxStaticText(this, wxID_ANY, wxT("关注科协喵~\n关注科协谢谢喵~"), wxDefaultPosition, wxDefaultSize, 0);
	kx_text->Wrap(-1);
	bSizer5->Add(kx_text, 0, wxTOP, 20);

	kx_link = new wxHyperlinkCtrl(this, wxID_ANY, wxT("科协B站"), wxT("https://space.bilibili.com/187447234"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE);
	bSizer5->Add(kx_link, 0, wxBOTTOM | wxRIGHT, 5);


	bSizer4->Add(bSizer5, 1, wxEXPAND, 5);


	gbSizer1->Add(bSizer4, wxGBPosition(5, 1), wxGBSpan(1, 1), wxEXPAND, 5);

	tips = new wxStaticText(this, wxID_ANY, wxT("温馨提示：\n   为保证您的注册表整洁，请在弃用本软件前\n关闭『开机自启功能』。"), wxDefaultPosition, wxDefaultSize, 0);
	tips->Wrap(-1);
	tips->SetForegroundColour(wxColour(255, 0, 0));

	gbSizer1->Add(tips, wxGBPosition(7, 0), wxGBSpan(1, 3), wxLEFT, 50);

	pop_when_start_checker = new wxCheckBox(this, wxID_ANY, wxT("启动时不再弹出此页面"), wxDefaultPosition, wxDefaultSize, 0);
	//pop_when_start_checker->SetValue(true);
	gbSizer1->Add(pop_when_start_checker, wxGBPosition(8, 0), wxGBSpan(1, 3), wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);


	bSizer3->Add(gbSizer1, 1, wxEXPAND, 5);


	this->SetSizer(bSizer3);
	this->Layout();

	this->Centre(wxBOTH);

	wxFileConfig config("GXU_Tools", "DleXoX", "config.ini", "",
		wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	bool popAboutDialog;
	config.Read("POP_WHEN_START", &popAboutDialog, false);
	pop_when_start_checker->SetValue(!popAboutDialog);


	this->Bind(wxEVT_CHECKBOX, &AboutDialog::OnCheckBoxClicked, this);
}

AboutDialog::~AboutDialog()
{
	wxFileConfig config("GXU_Tools", "DleXoX", "config.ini", "",
		wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	if (pop_when_start_checker->GetValue()) config.Write("POP_WHEN_START", false);
	else config.Write("POP_WHEN_START", true);

	config.Flush();
}

void AboutDialog::OnCheckBoxClicked(wxCommandEvent& event)
{
	wxFileConfig config("GXU_Tools", "DleXoX", "config.ini", "",
		wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	if(pop_when_start_checker->GetValue()) config.Write("POP_WHEN_START", false);
	else config.Write("POP_WHEN_START", true);

	config.Flush();

}

