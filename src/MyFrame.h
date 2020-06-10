#pragma once
#include <wx/wx.h>
#include "BasicDrawPanel.h"

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
    {
        //Bind(wxEVT_LEFT_UP, &BasicDrawPane::kappa, this);
    }
};