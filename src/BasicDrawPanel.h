#pragma once
#include <wx/panel.h>
#include <wx/wx.h>

class BasicDrawPane : public wxPanel
{

public:
    BasicDrawPane(wxFrame* parent);
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void kappa(wxMouseEvent& event);

    void render(wxDC& dc);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()
    wxImage img;
private:
    bool frogpikcat_needs_resizing_images;
};

