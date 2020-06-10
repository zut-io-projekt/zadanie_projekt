#pragma once
#include <wx/notebook.h>
#include <wx/wx.h>

class statisticsWindow: public wxNotebook
{
public:
	statisticsWindow(wxFrame* parent);
private:
	wxImageList* imgList;

};

