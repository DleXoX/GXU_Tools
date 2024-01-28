#include "../header/ExamFrame.h"
#include "../resources/app_icon.xpm"
#include <fstream>

using json = nlohmann::json;

std::string wxStringToString(const wxString& wxStr) {

	std::wstring tmpWstr = wxStr.ToStdWstring();
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(tmpWstr);
}

// ExamData到JSON的序列化函数
void to_json(json& j, const ExamData& p) {
	j = json{
		{"kcmc", wxStringToString(p.kcmc)},
		{"kssj", wxStringToString(p.kssj)},
		{"ksdd", wxStringToString(p.ksdd)},
		{"zwh", wxStringToString(p.zwh)},
		{"xnm", wxStringToString(p.xnm)},
		{"xqm", wxStringToString(p.xqm)},
		{"kch", wxStringToString(p.kch)},
		{"pscj", wxStringToString(p.pscj)},
		{"pszb", wxStringToString(p.pszb)},
		{"kscj", wxStringToString(p.kscj)},
		{"kszb", wxStringToString(p.kszb)},
		{"zpcj", wxStringToString(p.zpcj)},
		{"xf", wxStringToString(p.xf)},
		{"examTime", p.examTime}
	};
}

wxString StringToWxString(const std::string& str) {
	return wxString(str.c_str(), wxConvUTF8);
}

// JSON到ExamData的反序列化函数
void from_json(const json& j, ExamData& p) {
	p.kcmc = StringToWxString(j.at("kcmc").get<std::string>());
	p.kssj = StringToWxString(j.at("kssj").get<std::string>());
	p.ksdd = StringToWxString(j.at("ksdd").get<std::string>());
	p.zwh = StringToWxString(j.at("zwh").get<std::string>());
	p.xnm = StringToWxString(j.at("xnm").get<std::string>());
	p.xqm = StringToWxString(j.at("xqm").get<std::string>());
	p.kch = StringToWxString(j.at("kch").get<std::string>());
	p.pscj = StringToWxString(j.at("pscj").get<std::string>());
	p.pszb = StringToWxString(j.at("pszb").get<std::string>());
	p.kscj = StringToWxString(j.at("kscj").get<std::string>());
	p.kszb = StringToWxString(j.at("kszb").get<std::string>());
	p.zpcj = StringToWxString(j.at("zpcj").get<std::string>());
	p.xf = StringToWxString(j.at("xf").get<std::string>());
	p.examTime = j.at("examTime").get<long long>();
}
ExamFrame::ExamFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style), 
config("GXU_Tools", "DleXoX", "config.ini", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH)
{
	wxString account, password;
	config.Read("EduSystem/Account", &account, wxT(""));
	config.Read("EduSystem/Password", &password, wxT(""));


	SetSize(FromDIP(wxSize(931, 800)));
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* verticalSizerMain;
	verticalSizerMain = new wxBoxSizer(wxVERTICAL);

	wxGridBagSizer* horizontalSizerControls;
	horizontalSizerControls = new wxGridBagSizer(0, 0);
	horizontalSizerControls->SetFlexibleDirection(wxBOTH);
	horizontalSizerControls->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	labelAcademicYear = new wxStaticText(this, wxID_ANY, wxT("学年："), wxDefaultPosition, wxDefaultSize, 0);
	labelAcademicYear->Wrap(-1);
	horizontalSizerControls->Add(labelAcademicYear, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	wxArrayString choiceYearChoicesChoices;
	choiceYear = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceYearChoicesChoices, 0);
	choiceYear->SetSelection(0);
	horizontalSizerControls->Add(choiceYear, wxGBPosition(0, 1), wxGBSpan(1, 1), wxALL, 5);

	labelSemester = new wxStaticText(this, wxID_ANY, wxT("学期："), wxDefaultPosition, wxDefaultSize, 0);
	labelSemester->Wrap(-1);
	horizontalSizerControls->Add(labelSemester, wxGBPosition(0, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	wxArrayString choiceSemesterChoices;
	choiceSemester = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceSemesterChoices, 0);
	choiceSemester->SetSelection(0);
	horizontalSizerControls->Add(choiceSemester, wxGBPosition(0, 3), wxGBSpan(1, 1), wxALL, 5);

	btnAutoEvaluate = new wxButton(this, wxID_ANY, wxT("自动\n评教"), wxDefaultPosition, wxDefaultSize, 0);
	btnAutoEvaluate->SetMinSize(wxSize(60, -1));
	btnAutoEvaluate->SetMaxSize(wxSize(40, -1));
	horizontalSizerControls->Add(btnAutoEvaluate, wxGBPosition(0, 6), wxGBSpan(2, 1), wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);


	horizontalSizerControls->Add(FromDIP(30), 0, wxGBPosition(1, 5), wxGBSpan(1, 1), wxEXPAND, 5);

	btnQuery = new wxButton(this, wxID_ANY, wxT("手动\n查询"), wxDefaultPosition, wxDefaultSize, 0);

	horizontalSizerControls->Add(btnQuery, wxGBPosition(0, 4), wxGBSpan(2, 1), wxEXPAND| wxALL, 5);

	labelUpdateInfoNow = new wxStaticText(this, wxID_ANY, wxT("当前数据更新于："), wxDefaultPosition, wxDefaultSize, 0);
	labelUpdateInfoNow->Wrap(-1);
	horizontalSizerControls->Add(labelUpdateInfoNow, wxGBPosition(0, 7), wxGBSpan(1, 1), wxTOP | wxBOTTOM | wxLEFT | wxALIGN_BOTTOM, 5);

	updateTime = new wxStaticText(this, wxID_ANY, wxT("XXXX-XX-XX XX:XX"), wxDefaultPosition, wxDefaultSize, 0);
	updateTime->Wrap(-1);
	horizontalSizerControls->Add(updateTime, wxGBPosition(0, 8), wxGBSpan(1, 1), wxBOTTOM | wxRIGHT | wxALIGN_BOTTOM, 5);

	accountLabel = new wxStaticText(this, wxID_ANY, wxT("账号："), wxDefaultPosition, wxDefaultSize, 0);
	accountLabel->Wrap(-1);
	horizontalSizerControls->Add(accountLabel, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	examAccountInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	examAccountInput->SetValue(account);

	horizontalSizerControls->Add(examAccountInput, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL, 5);

	pwdLabel = new wxStaticText(this, wxID_ANY, wxT("密码："), wxDefaultPosition, wxDefaultSize, 0);
	pwdLabel->Wrap(-1);
	horizontalSizerControls->Add(pwdLabel, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	examPwdInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	examPwdInput->SetValue(password);
	horizontalSizerControls->Add(examPwdInput, wxGBPosition(1, 3), wxGBSpan(1, 1), wxALL | wxALIGN_CENTER_VERTICAL, 5);

	//btnAutoQuery = new wxButton(this, wxID_ANY, wxT("开始自动查询"), wxDefaultPosition, wxDefaultSize, 0);
	//horizontalSizerControls->Add(btnAutoQuery, wxGBPosition(1, 4), wxGBSpan(1, 1), wxALL | wxEXPAND, 5);

	labelUpdateInfoNext = new wxStaticText(this, wxID_ANY, wxT("下次自一动更新："), wxDefaultPosition, wxDefaultSize, 0);
	labelUpdateInfoNext->Wrap(-1);
	horizontalSizerControls->Add(labelUpdateInfoNext, wxGBPosition(1, 7), wxGBSpan(1, 1), wxBOTTOM | wxLEFT, 5);

	updateTimeNxt = new wxStaticText(this, wxID_ANY, wxT("XXXX-XX-XX XX:XX"), wxDefaultPosition, wxDefaultSize, 0);
	updateTimeNxt->Wrap(-1);
	horizontalSizerControls->Add(updateTimeNxt, wxGBPosition(1, 8), wxGBSpan(1, 1), wxRIGHT, 20);


	horizontalSizerControls->AddGrowableCol(5);

	verticalSizerMain->Add(horizontalSizerControls, 0, wxEXPAND, 5);

	wxBoxSizer* verticalSizerGrid;
	verticalSizerGrid = new wxBoxSizer(wxVERTICAL);

	gridExamInfo = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	gridExamInfo->CreateGrid(5, 10);
	gridExamInfo->EnableEditing(false);
	gridExamInfo->EnableGridLines(true);
	gridExamInfo->SetGridLineColour(wxColour(202, 202, 202));
	gridExamInfo->EnableDragGridSize(false);
	gridExamInfo->SetMargins(0, 0);

	// Columns

	gridExamInfo->SetColSize(0, FromDIP(240));
	gridExamInfo->SetColSize(1, FromDIP(151));
	gridExamInfo->SetColSize(2, FromDIP(105));
	gridExamInfo->SetColSize(3, FromDIP(40));
	gridExamInfo->SetColSize(4, FromDIP(76));
	gridExamInfo->SetColSize(5, FromDIP(46));
	gridExamInfo->SetColSize(6, FromDIP(79));
	gridExamInfo->SetColSize(7, FromDIP(54));
	gridExamInfo->SetColSize(8, FromDIP(55));
	gridExamInfo->SetColSize(9, FromDIP(46));
	gridExamInfo->EnableDragColMove(true);
	gridExamInfo->EnableDragColSize(true);
	gridExamInfo->SetColLabelValue(0, wxT("课程"));
	gridExamInfo->SetColLabelValue(1, wxT("时间"));
	gridExamInfo->SetColLabelValue(2, wxT("考试地点"));
	gridExamInfo->SetColLabelValue(3, wxT("座位号"));
	gridExamInfo->SetColLabelValue(4, wxT("学年"));
	gridExamInfo->SetColLabelValue(5, wxT("学期"));
	gridExamInfo->SetColLabelValue(6, wxT("课程代码"));
	gridExamInfo->SetColLabelValue(7, wxT("平时成绩"));
	gridExamInfo->SetColLabelValue(8, wxT("考试成绩"));
	gridExamInfo->SetColLabelValue(9, wxT("总评"));
	gridExamInfo->SetColLabelSize(wxGRID_AUTOSIZE);
	gridExamInfo->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows

	gridExamInfo->EnableDragRowSize(true);
	gridExamInfo->SetRowLabelSize(wxGRID_AUTOSIZE);
	gridExamInfo->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	gridExamInfo->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	verticalSizerGrid->Add(gridExamInfo, 5, wxALL | wxEXPAND, 5);

	gridExamResult = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	gridExamResult->CreateGrid(5, 10);
	gridExamResult->EnableEditing(false);
	gridExamResult->EnableGridLines(true);
	gridExamResult->SetGridLineColour(wxColour(202, 202, 202));
	gridExamResult->EnableDragGridSize(false);
	gridExamResult->SetMargins(0, 0);

	// Columns
	gridExamResult->SetColSize(0, FromDIP(240));
	gridExamResult->SetColSize(1, FromDIP(151));
	gridExamResult->SetColSize(2, FromDIP(105));
	gridExamResult->SetColSize(3, FromDIP(40));
	gridExamResult->SetColSize(4, FromDIP(76));
	gridExamResult->SetColSize(5, FromDIP(46));
	gridExamResult->SetColSize(6, FromDIP(79));
	gridExamResult->SetColSize(7, FromDIP(54));
	gridExamResult->SetColSize(8, FromDIP(55));
	gridExamResult->SetColSize(9, FromDIP(46));
	gridExamResult->EnableDragColMove(true);
	gridExamResult->EnableDragColSize(true);
	gridExamResult->SetColLabelValue(0, wxT("课程"));
	gridExamResult->SetColLabelValue(1, wxT("时间"));
	gridExamResult->SetColLabelValue(2, wxT("考试地点"));
	gridExamResult->SetColLabelValue(3, wxT("座位号"));
	gridExamResult->SetColLabelValue(4, wxT("学年"));
	gridExamResult->SetColLabelValue(5, wxT("学期"));
	gridExamResult->SetColLabelValue(6, wxT("课程代码"));
	gridExamResult->SetColLabelValue(7, wxT("平时成绩"));
	gridExamResult->SetColLabelValue(8, wxT("考试成绩"));
	gridExamResult->SetColLabelValue(9, wxT("总评"));
	gridExamResult->SetColLabelSize(wxGRID_AUTOSIZE);
	gridExamResult->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	gridExamResult->SetRowSize(0, 32);
	gridExamResult->SetRowSize(1, 21);
	gridExamResult->SetRowSize(2, 21);
	gridExamResult->SetRowSize(3, 22);
	gridExamResult->SetRowSize(4, 23);
	gridExamResult->EnableDragRowSize(true);
	gridExamResult->SetRowLabelSize(wxGRID_AUTOSIZE);
	gridExamResult->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	gridExamResult->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	gridExamInfo->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	verticalSizerGrid->Add(gridExamResult, 5, wxALL | wxEXPAND, 5);


	verticalSizerMain->Add(verticalSizerGrid, 5, wxEXPAND, 5);
	webView = wxWebView::New(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxWebViewBackendEdge);
	webView->SetMaxSize(FromDIP(wxSize(-1, 400)));
	verticalSizerMain->Add(webView, 2, wxEXPAND, 5);

	this->SetSizer(verticalSizerMain);
	this->Layout();
	autoEvaTimer.SetOwner(this, wxID_ANY);
	statusBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

	this->Centre(wxBOTH);

	//btnAutoQuery->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ExamFrame::onAutoQureyClick,this);
	this->Bind(wxEVT_CLOSE_WINDOW, &ExamFrame::onClose, this);
	btnQuery->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ExamFrame::onQureyClick,this);
	btnAutoEvaluate->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ExamFrame::onAutoEvaluatClick,this);
	webView->Bind(wxEVT_WEBVIEW_LOADED, &ExamFrame::onPageLoaded, this);

	json j;
	try {
		
		wxString jsonPath = wxStandardPaths::Get().GetExecutablePath();
		jsonPath=jsonPath.BeforeLast('\\')+"\\examData.json";

		std::ifstream inFile(jsonPath.ToStdString());
		std::stringstream strStream;
		strStream << inFile.rdbuf(); // 读取文件内容到字符串流
		inFile.close();
		std::string content = strStream.str(); // 转换为std::string
		std::wstring cc = s2wstring(content);
		j=json::parse(cc);
		// 将std::string转换为wxString并显示在textCtrl中
		
		ExamDataMap = j.get<std::map<wxString, ExamData>>();
		FillGridExamInfo();
	}
	catch (nlohmann::json::parse_error& e) {
		wxLogMessage(e.what());
	}
	WidgetsInit();
}

ExamFrame::~ExamFrame()
{

}


void ExamFrame::WidgetsInit()
{
	choiceSemester->Append("1");
	choiceSemester->Append("2");
	choiceSemester->Append("3");
	choiceSemester->SetSelection(0);



	// 获取当前年份和月份
	wxDateTime now = wxDateTime::Now();
	int currentYear = now.GetYear();
	int currentMonth = now.GetMonth() + 1; // wxDateTime 的月份是从 0 开始的

	 // 设置年份范围
	int startYear = 2005;
	int endYear = currentYear + 3;

	// 填充选项，从最新年份开始
	for (int year = endYear; year >= startYear; --year) {
		wxString yearStr = wxString::Format("%d-%d", year, year + 1);
		choiceYear->Append(yearStr);  // 插入到列表的顶部
	}

	// 设置默认选择项
	if (currentMonth >= 10) {
		choiceYear->SetSelection(3);
		choiceSemester->SetSelection(0);
	}
	else if (currentMonth <= 9) { 
		choiceYear->SetSelection(4);
		if(currentMonth>=3) choiceSemester->SetSelection(1);
		else choiceSemester->SetSelection(0);
	}
	timer = new wxTimer(this, wxID_ANY);
	timer ->Start(30*60*1000);
	Bind(wxEVT_TIMER, &ExamFrame::onTimer, this,timer->GetId());
	AutoQuery();
	
}

void ExamFrame::AutoQuery()
{
	//讲道理应该直接ping教务系统的，但是老师应该不会断网时间出成绩。
	if (isConnected() && examAccountInput->GetValue().Length()!=0 && examPwdInput->GetValue().Length() != 0) {
		webView->LoadURL("https://jwxt2018.gxu.edu.cn/jwglxt/kwgl/kscx_cxXsksxxIndex.html?gnmkdm=N358105&layout=default");

	}
	else {
		statusBar->SetStatusText(L"网络连接失败");
	}
}

void ExamFrame::GetSelectDate(wxString& xnm, wxString& xqm)
{
	//学期和xnm的对应关系1-3,2-12,3-16
	wxString semesterMap[] = { "3", "12", "16" };
	xqm = semesterMap[choiceSemester->GetSelection()];
	wxString yearStr = choiceYear->GetString(choiceYear->GetSelection());
	xnm = yearStr.BeforeFirst('-');
}

void ExamFrame::GetMonitorDate(wxString& xnm, wxString& xqm)
{
	//获得当前年月
	wxDateTime now = wxDateTime::Now();
	int currentYear = now.GetYear();
	int currentMonth = now.GetMonth() + 1; // wxDateTime 的月份是从 0 开始的
	//如果当前月份大于等于10或小于等于4，那么就是第一学期，否则是第二学期
	if (currentMonth >= 10 || currentMonth <= 4) {
		xqm = "1";
	}
	else {
		xqm = "2";
	}

	//设置学年
	if(currentMonth<10) xnm = wxString::Format("%d",currentYear - 1);
	else xnm = wxString::Format("%d", currentYear);
}

void ExamFrame::ParseExamDate(wxString jsonDate, long long& examTime)
{
	jsonDate.Replace("-", ""); // Remove '-'
	jsonDate.Replace("(", ""); // Remove '('
	jsonDate.Replace(")", ""); // Remove ')'
	jsonDate.Replace(":", ""); // Remove ':'

	jsonDate.ToLongLong(&examTime);
}

//void ExamFrame::onAutoQureyClick(wxCommandEvent& event)
//{
//	wxString label = btnAutoQuery->GetLabel();
//		
//	if (label == L"开始自动查询") {
//		btnAutoQuery->SetLabelText(L"结束自动查询");
//		examAccountInput->Disable();
//		examPwdInput->Disable();
//		
//		if (isConnected()) {
//			webView->LoadURL("https://jwxt2018.gxu.edu.cn/jwglxt/kwgl/kscx_cxXsksxxIndex.html?gnmkdm=N358105&layout=default");
//			
//		}
//		else {
//			statusBar->SetStatusText(L"网络连接失败");
//		}
//	}
//	else {
//		btnAutoQuery->SetLabelText(L"开始自动查询");
//		examAccountInput->Enable();
//		examPwdInput->Enable();
//	}
//}

void ExamFrame::targetQueryBtn()
{
	wxCommandEvent e(wxEVT_BUTTON, btnQuery->GetId());
	btnQuery->GetEventHandler()->ProcessEvent(e);
}

void ExamFrame::onClose(wxCloseEvent& event)
{
	this->Hide();
	wxFileConfig config("GXU_Tools", "DleXoX", "config.ini", "",
		wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	config.Write("EduSystem/Account", examAccountInput->GetValue());
	config.Write("EduSystem/Password",examPwdInput->GetValue());
	//config.DeleteAll();
	// 确保写入数据被保存到文件
	config.Flush();
}



void ExamFrame::onTimer(wxTimerEvent& event)
{
	
	AutoQuery();
}

void ExamFrame::onQureyClick(wxCommandEvent& event)
{
	if (isConnected()) {
		
		webView->LoadURL("https://jwxt2018.gxu.edu.cn/jwglxt/xtgl/login_slogin.html");
		webView->RunScript("location.reload();");
		statusBar->SetStatusText(L"查询中(很久没动静就再查一次)");
	}
	else {
		statusBar->SetStatusText(L"网络连接失败");
	}
}

void ExamFrame::onAutoEvaluatClick(wxCommandEvent& event)
{
	if (isConnected()) {
		webView->LoadURL("https://jwxt2018.gxu.edu.cn/jwglxt/xspjgl/xspj_cxXspjIndex.html?doType=details&gnmkdm=N401605&layout=default");
		statusBar->SetStatusText(L"评教中");
	}
	else {
		statusBar->SetStatusText(L"网络连接失败");
	}
}

void ExamFrame::onPageLoaded(wxWebViewEvent& event)
{
	
	wxString url = event.GetURL();
	int pos = url.rfind("?");
	if (pos != wxString::npos) {
		url.erase(pos);
	}
	if (url == "https://jwxt2018.gxu.edu.cn/jwglxt/xtgl/login_slogin.html") {
		//看看提示栏中有没有内容，一般是要输验证码或者密码错误了才会有提示，
		wxString tipsSize;
		hv_msleep(1000);
		webView->RunScript(R"($("#tips").children().length;)",&tipsSize);
		if(tipsSize=="1"){
			statusBar->SetStatusText(L"登录失败,可能是密码错误或是需要输入验证码");
			//targetAutoQueryBtn();
			return;
		}
		webView->RunScript("document.getElementById('yhm').value = '" + examAccountInput->GetValue() + "';");
		webView->RunScript("document.getElementById('mm').value = '" + examPwdInput->GetValue() + "';");
		hv_msleep(350);
		webView->RunScript("document.getElementById('dl').click();");
	}
	//手动查询
	else if (url == "https://jwxt2018.gxu.edu.cn/jwglxt/xtgl/index_initMenu.html") {
		wxString examInfo,examResult;
		hv_msleep(250);
		webView->RunScript(ExamInfoQueryInit(QUERY));
		webView->RunScript(ExamResultsQueryInit(QUERY));
		hv_msleep(550);
		webView->RunScript("$('#examInfo').text();",&examInfo);
		webView->RunScript("$('#examResult').text();",&examResult);
		try
		{
			
			json examInfoJson = json::parse(examInfo.ToStdWstring());
			json examResultJson = json::parse(examResult.ToStdWstring());
			ParseExamInfoData(examInfoJson);
			ParseExamResultData(examResultJson);
			FillGridExamInfo();
			FillGridExamResult();
			statusBar->SetStatusText(L"查询完成");
		}
		catch (const json::parse_error& e)
		{
			wxLogMessage(e.what());
		}
		catch (const json::type_error& e)
		{
			wxLogMessage(e.what());
		}
		
			
		

	}
	else if (url == "https://jwxt2018.gxu.edu.cn/jwglxt/xspjgl/xspj_cxXspjIndex.html") {
		//评教

		wxString js =wxString::FromUTF8( R"((async () => {
const sleep = (delay) => new Promise((resolve) => setTimeout(resolve, delay));
await sleep(900);
$(".ui-pg-selbox").val(5000);
await sleep(900);
$(".ui-pg-selbox").change();
await sleep(900);
var firstCellList = $("tbody:first tr").not(':first').find("td:visible:first");
var teCellList = $("tbody:first tr:visible").find('td:visible:eq(1)');
for (var i = 0; i < firstCellList.length; i++) {
    var cell = $("tbody:first tr").not(':first').find("td:visible:first").eq(i);
    $("tbody:first tr").not(':first').find("td:visible:first").eq(i).click();
    await sleep(500);

	  if (cell.text() !== "提交") {
        $(".radio-inline.input-xspj.input-xspj-1 input").prop("checked", true);
        $(".radio-inline.input-xspj.input-xspj-2 input:first").click();
        var bfztxfs = $("#bfztxfs").val();
        var flagTf = true;
        var bfzpf;
        var panel_pjdx = $.find("div.panel-pjdx");
        if (bfztxfs == "2") {
            bfzpf = calculatePjmbPjzf2(panel_pjdx);
        } else {
            bfzpf = calculatePjmbPjzf(panel_pjdx);
        }
        var xspj_body = $("div.xspj-body");
        var jxb_id = $(xspj_body).data("jxb_id");
        var jgh_id = $(xspj_body).data("jgh_id");
        jQuery.ajaxSetup({ async: false });
        jQuery.post(_path + '/xspjgl/xspj_cxSftf.html', { bfzpf: bfzpf, jxb_id: jxb_id, jgh_id: jgh_id }, function (data) {
            if (data != 0) {
                flagTf = false;
                $.alert("同学，存在分数与当前评价分相同，请做调整");
                return flagTf;
            }
        }, 'json');

        var dataMap = buildRequestMap.call(this) || {};
        dataMap["tjzt"] = "0";
        jQuery.ajax({
            url: _path + "/xspjgl/xspj_tjXspj.html",
            type: "post",
            dataType: "json",
            data: dataMap,
            async: false,

        });
        await sleep(200);
    }
}
})();
)");

		webView->RunScript(js);

		statusBar->SetStatusText(L"评教完成");
	}
	//自动查询
	else if (url == "https://jwxt2018.gxu.edu.cn/jwglxt/kwgl/kscx_cxXsksxxIndex.html") {
		wxString examInfo, examResult;
		webView->RunScript(ExamInfoQueryInit(AUTO_QUERY));
		webView->RunScript(ExamResultsQueryInit(AUTO_QUERY));
		hv_msleep(550);
		webView->RunScript("$('#examInfo').text();", &examInfo);
		webView->RunScript("$('#examResult').text();", &examResult);
		try
		{

			json examInfoJson = json::parse(examInfo.ToStdWstring());
			json examResultJson = json::parse(examResult.ToStdWstring());
			ParseExamInfoData(examInfoJson);
			ParseExamResultData(examResultJson);
			FillGridExamInfo();
			FillGridExamResult();
			statusBar->SetStatusText(L"自动查询完成");
		}
		catch (const json::parse_error& e)
		{
			wxLogMessage(e.what());
		}
		catch (const json::type_error& e)
		{
			wxLogMessage(e.what());
		}
	}
	else
	{

	}
}

void ExamFrame::OnNotificationClick(wxCommandEvent& event)
{
	if(!this->IsShown()) this->Show();
	if(this->IsIconized()) this->Restore();
}

//void ExamFrame::targetAutoQueryBtn()
//{
//	wxCommandEvent e(wxEVT_BUTTON, btnAutoQuery->GetId());
//	btnAutoQuery->GetEventHandler()->ProcessEvent(e);
//
//}

wxString ExamFrame::ExamResultsQueryInit(QueryType qreryType)
{
	wxString xnm = "2005", xqm = "3";

	if (qreryType == QueryType::AUTO_QUERY) {
		GetMonitorDate(xnm, xqm);
		wxString semesterMap[] = { "3" ,"3", "12", "16" };
		int value;
		xqm.ToInt(&value);
		xqm = semesterMap[value];
	}
	else {
		GetSelectDate(xnm, xqm);
	}
	wxLogMessage(wxString::Format("xqm  %d,xnm  %d",xqm,xnm));
	
	
	wxString query = wxString::Format(R"($.ajax({
    url: "https://jwxt2018.gxu.edu.cn/jwglxt/cjcx/cjcx_cxXsKccjList.html?gnmkdm=N305007",
    type: "POST",
    headers: {
        "Accept": "application/json, text/javascript, */*; q=0.01",
        "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8",
        "Content-Type": "application/x-www-form-urlencoded;charset=UTF-8",
        "X-Requested-With": "XMLHttpRequest"
    },
    data: "xnm=%s&xqm=%s&ksmcdmb_id=&kch=&kc=&ksrq=&kkbm_id=&_search=false&nd=1703148446701&queryModel.showCount=5000&queryModel.currentPage=1&queryModel.sortName=&queryModel.sortOrder=asc&time=5",
    xhrFields: {
        withCredentials: true
    },
    crossDomain: true,
    success: function(response) {
         var jsonResponseString = JSON.stringify(response.items);
        $('body').append('<div id="examResult" style="display: none;">' + jsonResponseString + '</div>');
    }
});)", xnm, xqm);
	return query;

}


wxString ExamFrame::ExamInfoQueryInit(QueryType qreryType)
{
	wxString xnm = "2005", xqm = "3";
	if (qreryType == QueryType::AUTO_QUERY) {
		GetMonitorDate(xnm, xqm);
		wxString semesterMap[] = {"3" ,"3", "12", "16"};
		int value;
		xqm.ToInt(&value);
		xqm = semesterMap[value];
	}
	else {
		GetSelectDate(xnm, xqm);
	}

	wxString query = wxString::Format(R"($.ajax({
    url: "https://jwxt2018.gxu.edu.cn/jwglxt/kwgl/kscx_cxXsksxxIndex.html?doType=query&gnmkdm=N358105",
    type: "POST",
    headers: {
        "Accept": "application/json, text/javascript, */*; q=0.01",
        "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8",
        "Content-Type": "application/x-www-form-urlencoded;charset=UTF-8",
        "X-Requested-With": "XMLHttpRequest"
    },
    data: "xnm=%s&xqm=%s&ksmcdmb_id=&kch=&kc=&ksrq=&kkbm_id=&_search=false&nd=1703148446701&queryModel.showCount=5000&queryModel.currentPage=1&queryModel.sortName=&queryModel.sortOrder=asc&time=5",
    xhrFields: {
        withCredentials: true
    },
    crossDomain: true,
    success: function(response) {
         var jsonResponseString = JSON.stringify(response.items);
        $('body').append('<div id="examInfo" style="display: none;">' + jsonResponseString + '</div>');
    }
});)", xnm, xqm);
	return query;
}

void ExamFrame::ParseExamResultData(const json& examResultJson)
{
	std::unordered_map<std::wstring,std::string> semesterMap;
	semesterMap[L"3"] = "1";
	semesterMap[L"12"] = "2";
	semesterMap[L"16"] = "3";
	bool needNotify = false;
	for (int i = 0; i < examResultJson.size();i++) {
		ExamData result = tmpExamDataMap[s2wstring(examResultJson[i]["kch"])];
		wxString moduleName=s2wstring(examResultJson[i]["xmblmc"]);
		if (moduleName.starts_with(L"总评")) {
			result.kcmc = s2wstring(examResultJson[i]["kcmc"]);//课程名称
			result.xf = s2wstring(examResultJson[i]["xf"]); // 学分
			result.xnm = s2wstring(examResultJson[i]["xnm"]); // 学年
			result.xqm = semesterMap[s2wstring(examResultJson[i]["xqm"])]; // 学期		
			result.kch = s2wstring(examResultJson[i]["kch"]); // 课程代码
			result.zpcj = s2wstring(examResultJson[i]["xmcj"]); // 总评成绩
			wxString Mxqm, Mxnm;
			GetMonitorDate(Mxnm, Mxqm);
			if (!needNotify && result.xnm == Mxnm && result.xqm == Mxqm && ExamDataMap[result.kch].zpcj=="-") {
				needNotify = true;
			}
			
		}
		else if (moduleName.starts_with(L"平时")) {
			result.pscj = s2wstring(examResultJson[i]["xmcj"]); // 平时成绩
			result.pszb = s2wstring(examResultJson[i]["xmblmc"]); // 从平时成绩(40%) 中取出“40%”
			result.pszb.Replace(")", "");
			result.pszb =  result.pszb.AfterLast('(');
		}
		else if (moduleName.starts_with(L"期末")) {
			result.kscj = s2wstring(examResultJson[i]["xmcj"]); // 考试成绩
			result.kszb = s2wstring(examResultJson[i]["xmblmc"]); // 从 考试成绩(60%) 中取出“60%”
			result.kszb.Replace(")", "");
			result.kszb = result.kszb.AfterLast('(');
		}
		//else {
		//	wxLogMessage(wxString::Format("json中有未知的模块名称:%s", moduleName));
		//	return;
		//}
		
		if (result.kssj.IsEmpty()) {
			result.examTime = 2999999999999999;//考试时间为空，设置为最大值2999-99-99 99:99:99
		}
		tmpExamDataMap[s2wstring(examResultJson[i]["kch"])] = result;


	}
	if (needNotify) {
		ExamDataMap = tmpExamDataMap;
		//wxGenericNotificationMessage notice(L"出新成绩了", L"有新成绩了，快点击查看吧~",this);
		//wxImage img=wxImage(app_icon).Rescale(50, 50);
		//wxIcon icon; icon.CopyFromBitmap(wxBitmap(img));
		//notice.SetIcon(icon);

		//notice.Show(wxNotificationMessage::Timeout_Never);
		examResultNotice = new wxGenericNotificationMessage();
		wxImage img = wxImage(app_icon).Rescale(50, 50);
		wxIcon icon; icon.CopyFromBitmap(wxBitmap(img));
		examResultNotice->SetIcon(icon);
		examResultNotice->SetTitle(L"出新成绩了");
		examResultNotice->SetMessage(L"有新成绩了，快点击查看吧~");
		examResultNotice->Show(wxNotificationMessage::Timeout_Never);
		examResultNotice->Bind(wxEVT_NOTIFICATION_MESSAGE_CLICK, &ExamFrame::OnNotificationClick, this);
		std::ofstream o("examData.json");
		json j(ExamDataMap);
		o << j.dump(4) << std::endl;
		o.close();
	}
	
}

void ExamFrame::ParseExamInfoData(const json& examInfoJson)
{
	wxDateTime now = wxDateTime::Now();
	wxString formattedTime = now.Format("%Y-%m-%d %H:%M");
	updateTime->SetLabelText(formattedTime);
	wxDateTime nextUpdateTime = now + wxTimeSpan::Minutes(30);
	formattedTime = nextUpdateTime.Format("%Y-%m-%d %H:%M");
	updateTimeNxt->SetLabelText(formattedTime);
	timer->Stop();
	timer->Start(30*60*1000);

	tmpExamDataMap.clear();
	bool needNotify = false;
	if (examInfoJson.size() == 0) {
		return;
	}

	std::unordered_map<std::wstring, std::string> semesterMap;
	semesterMap[L"3"] = "1";
	semesterMap[L"12"] = "2";
	semesterMap[L"16"] = "3";
	for (int i = 0; i < examInfoJson.size(); i++) {
		ExamData result = tmpExamDataMap[s2wstring(examInfoJson[i]["kch"])];

		result.kcmc = s2wstring(examInfoJson[i]["kcmc"]);//课程名称
		result.xf = s2wstring(examInfoJson[i]["xf"]); // 学分
		result.xnm = s2wstring(examInfoJson[i]["xnm"]); // 学年
		result.xqm = semesterMap[s2wstring(examInfoJson[i]["xqm"])]; // 学期
		result.kch = s2wstring(examInfoJson[i]["kch"]); // 课程代码
		result.zwh= s2wstring(examInfoJson[i]["zwh"]); // 座位号
		result.ksdd= s2wstring(examInfoJson[i]["cdbh"]); // 考试地点
		result.kssj= s2wstring(examInfoJson[i]["kssj"]); // 考试时间

		if (!result.kssj.IsEmpty()) {
			ParseExamDate(result.kssj,result.examTime);
		}
		else {
			result.examTime = 2099999999999999;//考试时间为空，设置为最大值
		}


		tmpExamDataMap[result.kch] = result;
		wxString Mxqm,Mxnm;
		GetMonitorDate(Mxnm, Mxqm);
		if (!needNotify &&result.xnm == Mxnm && result.xqm == Mxqm && ExamDataMap.count(result.kch)==0) {
			//清掉上个学期的数据
			if (!ExamDataMap.empty() && ExamDataMap.begin()->second.xqm!= Mxqm) {
				ExamDataMap.clear();
			}
			needNotify= true;
		}

	}
	if (needNotify) {
		ExamDataMap = tmpExamDataMap;
		examInfoNotice = new wxGenericNotificationMessage();
		wxImage img = wxImage(app_icon).Rescale(50, 50);
		wxIcon icon; icon.CopyFromBitmap(wxBitmap(img));
		examInfoNotice->SetIcon(icon);
		examInfoNotice->SetTitle(L"新的考试通知");
		examInfoNotice->SetMessage(L"有新考试了，快点击查看吧~");
		examInfoNotice->Show(wxNotificationMessage::Timeout_Never);
		examInfoNotice->Bind(wxEVT_NOTIFICATION_MESSAGE_CLICK, &ExamFrame::OnNotificationClick, this);
		std::ofstream o("examData.json");
		json j(ExamDataMap);
		o  << j.dump(4) << std::endl;
		o.close();
	}
	
}



inline std::wstring ExamFrame::s2wstring(const std::string& input)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(input);
}

inline std::string ExamFrame::wstring2s(const std::wstring& input)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(input);
}

//使用examResultDataMap中的数据填充gridCourseInfo
void ExamFrame::FillGridExamResult()
{
	int row = 0;
	int colCount = gridExamResult->GetNumberRows();
	if(colCount>0) gridExamResult->DeleteRows(0,colCount);


	for (auto& it : tmpExamDataMap) {
		if (it.second.zpcj == "-") continue;

		gridExamResult->AppendRows();
		gridExamResult->SetCellValue(row, 0, it.second.kcmc+"("+it.second.pszb +"-"+ it.second.kszb + ")"); 
		gridExamResult->SetCellValue(row, 1, it.second.kssj);
		gridExamResult->SetCellValue(row, 2, it.second.ksdd);
		gridExamResult->SetCellValue(row, 3, it.second.zwh);
		gridExamResult->SetCellValue(row, 4, it.second.xnm);
		gridExamResult->SetCellValue(row, 5, it.second.xqm);
		gridExamResult->SetCellValue(row, 6, it.second.kch);
		gridExamResult->SetCellValue(row, 7, it.second.pscj);
		gridExamResult->SetCellValue(row, 8, it.second.kscj);
		gridExamResult->SetCellValue(row, 9, it.second.zpcj);
		row++;
	}
	if (gridExamResult->GetNumberRows() == 0) {
		gridExamResult->AppendRows();
		gridExamResult->SetCellValue(0, 0, L"还没有成绩哦~");
	}
}

void ExamFrame::FillGridExamInfo()
{

	int row = 0;
	int colCount = gridExamInfo->GetNumberRows();
	if (colCount > 0) gridExamInfo->DeleteRows(0, colCount);
	std::vector<ExamData> examDataVec;
	if (tmpExamDataMap.empty()) {
		for (auto& it : ExamDataMap) {
			examDataVec.push_back(it.second);
		}
	}
	else {
		for (auto& it : tmpExamDataMap) {
			examDataVec.push_back(it.second);
		}
	}

	std::sort(examDataVec.begin(), examDataVec.end(),
		[](const ExamData& a, const ExamData& b) {return a.examTime < b.examTime; });

	for (auto& it : examDataVec) {
		//if (it.second.zpcj != "-") continue;

		gridExamInfo->AppendRows();
		gridExamInfo->SetCellValue(row, 0, it.kcmc);
		gridExamInfo->SetCellValue(row, 1, it.kssj);
		gridExamInfo->SetCellValue(row, 2, it.ksdd);
		gridExamInfo->SetCellValue(row, 3, it.zwh);
		gridExamInfo->SetCellValue(row, 4, it.xnm);
		gridExamInfo->SetCellValue(row, 5, it.xqm);
		gridExamInfo->SetCellValue(row, 6, it.kch);
		gridExamInfo->SetCellValue(row, 7, it.kscj);
		gridExamInfo->SetCellValue(row, 8, it.kscj);
		gridExamInfo->SetCellValue(row, 9, it.zpcj);
		row++;
	}

	if (gridExamInfo->GetNumberRows() == 0) {
		gridExamInfo->AppendRows();
		gridExamInfo->SetCellValue(0, 0, L"考完了或者还没出通知");
	}
}



