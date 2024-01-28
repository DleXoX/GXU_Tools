#pragma once

#include "hv/icmp.h"
#include "hv/hv.h"
#include "hv/json.hpp"
#include "wx/log.h"
#include <locale>
#include <codecvt>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/textctrl.h>
#include <wx/gbsizer.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/webview.h>
#include <wx/notifmsg.h>
#include <wx/generic/notifmsg.h>
#include <wx/stdpaths.h>
#include <wx/fileconf.h>
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ExamFrame
///////////////////////////////////////////////////////////////////////////////

struct ExamData {
	wxString kcmc;
	wxString kssj;
	wxString ksdd;
	wxString zwh;
	wxString xnm;
	wxString xqm;
	wxString kch;
	wxString pscj;
	wxString pszb = "0%";
	wxString kscj;
	wxString kszb = "0%";
	wxString zpcj = "-";
	wxString xf;
	long long examTime;

};


enum QueryType {
	AUTO_QUERY,
	QUERY
};



class ExamFrame : public wxFrame
{
private:

protected:
	wxFileConfig config;
	wxStaticText* labelAcademicYear;
	wxChoice* choiceYear;
	wxStaticText* labelSemester;
	wxChoice* choiceSemester;
	wxButton* btnAutoEvaluate;
	wxButton* btnQuery;
	wxStaticText* labelUpdateInfoNow;
	wxStaticText* updateTime;
	wxStaticText* accountLabel;
	wxStaticText* pwdLabel;

	wxButton* btnAutoQuery;
	wxStaticText* labelUpdateInfoNext;
	wxStaticText* updateTimeNxt;
	wxGrid* gridExamInfo;
	wxGrid* gridExamResult;
	wxTimer autoEvaTimer;
	wxStatusBar* statusBar;
	wxWebView* webView;
	wxTimer* timer;
	wxGenericNotificationMessage* examInfoNotice;
	wxGenericNotificationMessage* examResultNotice;
	std::map<wxString, ExamData> tmpExamDataMap;
	std::map<wxString, ExamData> ExamDataMap;


	void WidgetsInit();

	void AutoQuery();

	void GetSelectDate(wxString& xnm, wxString& xqm);
	void GetMonitorDate(wxString& xnm, wxString& xqm);
	void ParseExamDate(wxString jsonDate, long long& examTime);

	//void onAutoEvaluateClick(wxCommandEvent& event);
	//void onQueryClick(wxCommandEvent& event);
	//void onAutoQureyClick(wxCommandEvent& event);
	void targetQueryBtn();
	void onClose(wxCloseEvent& event);
	void onTimer(wxTimerEvent& event);
	void onQureyClick(wxCommandEvent& event);
	void onAutoEvaluatClick(wxCommandEvent& event);
	void onPageLoaded(wxWebViewEvent& event);
	void OnNotificationClick(wxCommandEvent& event);

	//void targetAutoQueryBtn();
	wxString ExamResultsQueryInit(QueryType qreryType);
	wxString ExamInfoQueryInit(QueryType qreryType);
	void ParseExamResultData(const nlohmann::json& json);
	void ParseExamInfoData(const nlohmann::json& json);

	// convert string to wstring
	inline std::wstring s2wstring(const std::string& input);
	// convert wstring to string 
	inline std::string wstring2s(const std::wstring& input);

	void FillGridExamResult();
	void FillGridExamInfo();


public:
	wxTextCtrl* examAccountInput;
	wxTextCtrl* examPwdInput;
	ExamFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("教务系统"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(931, 582), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~ExamFrame();

};
