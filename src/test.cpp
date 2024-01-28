#include <wx/wx.h>
#include <wx/webview.h>
#include "wx/msw/webview_edge.h"




class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    wxString res;
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnPageLoaded(wxWebViewEvent& event);
    void OnNewWindow(wxWebViewEvent& event);
    void OnNewWindowScriptResult(wxWebViewEvent& event);
    wxWebView* m_webView;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("wxWidgets WebView Example", wxDefaultPosition, wxSize(700, 500));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    if(!wxWebView::IsBackendAvailable(wxWebViewBackendEdge)) exit(2);
    // ʹ�� Edge ����������ʼ�� WebView
    m_webView = wxWebView::New(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxWebViewBackendEdge);
    m_webView->LoadURL("https://jwxt2018.gxu.edu.cn/jwglxt/xtgl/login_slogin.html");
    m_webView->Bind(wxEVT_WEBVIEW_LOADED, &MyFrame::OnPageLoaded, this);
    m_webView->Bind(wxEVT_WEBVIEW_NEWWINDOW, &MyFrame::OnNewWindow, this);
    m_webView->Bind(wxEVT_WEBVIEW_SCRIPT_RESULT, &MyFrame::OnNewWindowScriptResult, this);

}
#if wxUSE_WEBVIEW_EDGE
#endif

void MyFrame::OnPageLoaded(wxWebViewEvent& event)
{
    // ��ҳ�������ɺ���IDΪ��yhm�����������������
    wxString url=event.GetURL();
    int pos = url.rfind("?");
    if (pos != wxString::npos) {
        url.erase(pos);
    }
    if (url == "https://jwxt2018.gxu.edu.cn/jwglxt/xtgl/login_slogin.html") {
        wxString javascript = "document.getElementById('yhm').value = '2007310429';var a=document.getElementById('mm');a.value = '926jwcWen';";
        wxSleep(1);
        wxString javascript1 = "document.getElementById('dl').click()";

        m_webView->RunScript(javascript);
        wxSleep(1);
        m_webView->RunScript(javascript1);
    }
    if (url == "https://jwxt2018.gxu.edu.cn/jwglxt/xtgl/index_initMenu.html") {   
        m_webView->RunScript(R"(var aaa='';
$.ajax({
    url: "https://jwxt2018.gxu.edu.cn/jwglxt/cjcx/cjcx_cxXsKccjList.html?gnmkdm=N305007",
    type: "POST",
    headers: {
        "Accept": "application/json, text/javascript, */*; q=0.01",
        "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8",
        "Content-Type": "application/x-www-form-urlencoded;charset=UTF-8",
        "X-Requested-With": "XMLHttpRequest"
    },
    data: "xnm=2022&xqm=3&ksmcdmb_id=&kch=&kc=&ksrq=&kkbm_id=&_search=false&nd=1703148446701&queryModel.showCount=5000&queryModel.currentPage=1&queryModel.sortName=&queryModel.sortOrder=asc&time=5",
    xhrFields: {
        withCredentials: true
    },
    crossDomain: true,
    success: function(response) {
         var jsonResponseString = JSON.stringify(response);
        $('body').append('<div id="ajaxResult" style="display: none;">' + jsonResponseString + '</div>');
    }
});)");

        m_webView->RunScript(R"($("#ajaxResult").text())", &url);
        int a = 0;
    }



    //wxWebView* webView = wxWebView::New(this, wxID_ANY, "https://www.example.com");

    //// ��������������ȡ�־û��洢�е� cookies �Ĵ���
    //wxString cookies = LoadCookiesFromStorage();

    //// ���� cookies��ʾ�������巽��ȡ���� wxWebView �İ汾�����棩
    //webView->SetCookies(cookies);
}

void MyFrame::OnNewWindow(wxWebViewEvent& event)
{
    // ��ȡURL
    wxString url = event.GetURL();

    // ���������µ�wxWebView�д�URL
   
    m_webView->LoadURL(url);

    // ���ߣ�ʹ��ϵͳĬ���������
    // wxLaunchDefaultBrowser(url);
}

void MyFrame::OnNewWindowScriptResult(wxWebViewEvent& event)
{
    wxString a= event.GetString();
    event.IsError();
    int b = 1;
}


