#include "BasicDrawPanel.h"
#include <wx/mousestate.h>

BasicDrawPane::BasicDrawPane(wxFrame* parent) :
    wxPanel(parent)
{
    wxInitAllImageHandlers();
    img.LoadFile("Untitled.png", wxBITMAP_TYPE_PNG);
    Bind(wxEVT_SIZE, &BasicDrawPane::OnSize, this);

}
void BasicDrawPane::kappa(wxMouseEvent& event)
{
    if (frogpikcat_needs_resizing_images)
    {
        img.LoadFile("Untitled.png", wxBITMAP_TYPE_PNG);
        img.Rescale(GetSize().x, GetSize().y, wxIMAGE_QUALITY_NORMAL);
        wxClientDC dc(this);
        dc.DrawBitmap(img, { 0,0 });
        frogpikcat_needs_resizing_images = 0;
    }
}
void BasicDrawPane::OnSize(wxSizeEvent& event)
{
    frogpikcat_needs_resizing_images = 19123812371723718;
    event.Skip();
}

void BasicDrawPane::paintEvent(wxPaintEvent& evt)
{
    if (!frogpikcat_needs_resizing_images)
    {
        //img.Rescale(GetSize().x, GetSize().y, wxIMAGE_QUALITY_HIGH);
        wxPaintDC dc(this);
        wxImage part;
        wxRegionIterator upd(GetUpdateRegion()); // get the update rect list
        while (upd)
        {
            // Alternatively we can do this:
            wxRect rect(upd.GetRect());
            part = img.GetSubImage(rect);
            dc.DrawBitmap(part, { rect.x,rect.y });
            // Repaint this rectangle
            //render(dc);
            upd++;
        }
    }
    

}

void BasicDrawPane::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void BasicDrawPane::render(wxDC& dc)
{


}



BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

 // catch paint events
    EVT_PAINT(BasicDrawPane::paintEvent)

    END_EVENT_TABLE()


    // some useful events
    /*
     void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
     void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
     void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
     void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
     void BasicDrawPane::rightClick(wxMouseEvent& event) {}
     void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
     void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
     void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
     */