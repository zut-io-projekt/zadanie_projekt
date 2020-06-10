#pragma once
#include <wx/panel.h>
#include <wx/wx.h>
#include "Utils.h"
#include <string>
#include <wx/dcbuffer.h>
#include "GameLogic.h"
#include "board.h"
#include <wx/timer.h>
#include "IPC.h"
#include <thread>


const std::vector<std::string> piece_image_names = { "WP.png","WN.png", "WB.png","WR.png","WQ.png","WK.png","BP.png","BN.png","BB.png","BR.png","BQ.png","BK.png" };

class PlayfieldWindow: public wxPanel
{
public:
	PlayfieldWindow(wxWindow* parent);
	void Draw(wxSizeEvent& event);
	void update();
	void in(wxMouseEvent& event);
	void make_move();
	void onIdle(wxIdleEvent& evt);
	void onMouseDown(wxMouseEvent& event);
	void onMouseUp(wxMouseEvent& event);



private:
	std::vector<wxImage> piece_images;
	
	std::vector<Piece>* m_playfield;
	wxPoint previousSquare;
	GameLogic game;
	int count = 120;
	Piece selected_piece = PIECE_EMPTY;
	wxPoint mousePos;
	std::string position_command = "position startpos moves";
};

