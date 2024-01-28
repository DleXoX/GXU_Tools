//////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once


#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/generic/statbmpg.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/hyperlink.h>
#include <wx/checkbox.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialog
///////////////////////////////////////////////////////////////////////////////
class AboutDialog : public wxDialog
{
private:

protected:
	wxGenericStaticBitmap* software_logo;
	wxStaticText* about_topic;
	wxStaticText* author_text;
	wxStaticText* friend_link_label;
	wxHyperlinkCtrl* github_link;
	wxStaticBitmap* kx_logo;
	wxStaticText* kx_text;
	wxHyperlinkCtrl* kx_link;
	wxStaticText* tips;
	wxCheckBox* pop_when_start_checker;

public:

	AboutDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("关于软件"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(321, 455), long style = wxDEFAULT_DIALOG_STYLE |wxSTAY_ON_TOP);

	~AboutDialog();

	void OnCheckBoxClicked(wxCommandEvent& event);

};