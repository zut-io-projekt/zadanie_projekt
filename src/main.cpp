#include <wx/wx.h>
#include "wx/sizer.h"
#include <wx/imagpng.h>
#include <wx/splitter.h>
#include "BasicDrawPanel.h"
#include "Utils.h"
#include "MyFrame.h"
#include "PlayfieldWindow.h"
#include <thread>
enum wxIDs
{
    ID_FILE_NEW = 10000,
    ID_FILE_QUIT,
    ID_TOURNAMENT_NEW,
    ID_ENGINES_ADD,
    ID_ABOUT
};

class MyApp : public wxApp
{
    bool OnInit();
    //bool onNewGame(wxIDs id, wxCommandEvent& event);

    wxFrame* frame;
    BasicDrawPane* drawPane;
public:
    PlayfieldWindow* playfield;
};

IMPLEMENT_APP(MyApp)





bool MyApp::OnInit()
{
    //Bind(wxEVT_MENU, &MyApp::onNewGame, this);
    frame = new wxFrame(NULL,wxID_ANY, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(800, 600));
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxMenuBar* menuBar = new wxMenuBar();

    wxMenu* menuFile = new wxMenu;
    wxMenuItem* item = 
    menuFile->Append(ID_FILE_NEW, "New Game");
    menuFile->Append(ID_FILE_QUIT, "Quit");


    wxMenu* menuTournament = new wxMenu;
    menuTournament->Append(ID_TOURNAMENT_NEW, "New Tournament");

    menuBar->Append(menuFile,"File");
    menuBar->Append(menuTournament, "Tournament");

    frame->SetMenuBar(menuBar);

    wxSplitterWindow* mainWindow = new wxSplitterWindow(frame, wxID_ANY, { 100,100 }, { 800,600 });
    PlayfieldWindow* gameWindow = new PlayfieldWindow(mainWindow);
    playfield = gameWindow;
    
   
    wxSplitterWindow* NNinfoWindow = new wxSplitterWindow(mainWindow, wxID_ANY, { 0,0 }, { 150,600 });

    wxStaticText* textInfo = new wxStaticText(NNinfoWindow, wxID_ANY, "test");
    wxStaticText* textInfoe = new wxStaticText(NNinfoWindow, wxID_ANY, "test");
    drawPane = new BasicDrawPane((wxFrame*)NNinfoWindow);
    NNinfoWindow->SplitHorizontally(textInfo, drawPane);
    NNinfoWindow->SetSashGravity(0.5);
    NNinfoWindow->SetSashInvisible(false);
    wxBoxSizer* a = new wxBoxSizer(wxHORIZONTAL);

    mainWindow->SplitVertically(gameWindow, NNinfoWindow, 650);
    mainWindow->SetSashGravity(0.95);
    mainWindow->SetSashInvisible(false);
    std::cout << "abcd";
    sizer->Add(mainWindow,1);
    wxToolBar* toolbar = new wxToolBar();
    
    //sizer->Add(drawPane, 1, wxALIGN_CENTRE);
    //frame->SetSizer(sizer);
   // frame->SetAutoLayout(true);
    frame->Show();
    return true;
}


 