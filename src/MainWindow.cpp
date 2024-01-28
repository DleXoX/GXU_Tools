#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Rpcrt4.lib")
#include <wx/app.h>
#include <wx/snglinst.h>
#include <wx/stdpaths.h>
#include <hv/hlog.h>
#include <wx/msgdlg.h>
#include"../header/MyFrame.h"
#include "../header/AboutDialog.h"
#include "../header/ExamFrame.h"
//#define wxUSE DEBUG CONTEXT 1
//#define wxUSE MEMORY TRACING 1
//#define wxUSE GLOBAL MEMORY OPERATORS 1
//#define wxUSE DEBUG NEW ALWAYS 1

class MyApp : public wxApp
{
public:
    bool OnInit() override;
    int OnExit()override;
    wxSingleInstanceChecker* singleChecker;
    bool boost_from_system = true;
};

bool MyApp::OnInit()
{
    wxLog::SetLogLevel(wxLOG_Error);
   
    wxString appPath = wxStandardPaths::Get().GetExecutablePath();
    appPath = appPath.SubString(0, appPath.find_last_of('\\')-1);
 
    if (appPath == wxGetCwd()) {
        boost_from_system = false;
    }
    wxSetWorkingDirectory(appPath);

    hlog_disable();

    singleChecker =new wxSingleInstanceChecker;
    if (singleChecker->IsAnotherRunning()) {
        wxMessageBox 
        (
            L"你好像已经运行过我了捏\n去系统托盘里看看吧",
            L"运行一个我就好了",
           wxYES_DEFAULT
        );

        delete singleChecker; // OnExit() won't be called if we return false
        singleChecker = nullptr;

        return false;
    }
    wxImage::AddHandler(new wxPNGHandler);
    

    MyFrame* frame = new MyFrame(nullptr);
    if(!boost_from_system) frame->Show(true);
    
    return true;
}

int MyApp::OnExit()
{
    delete singleChecker;
    return 0;
}

wxIMPLEMENT_APP(MyApp);



