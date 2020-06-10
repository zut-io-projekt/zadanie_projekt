#include "PlayfieldWindow.h"


PlayfieldWindow::PlayfieldWindow(wxWindow* parent) :wxPanel(parent), game(), piece_images(piece_image_names.size())
{
	wxInitAllImageHandlers();
	Bind(wxEVT_SIZE, &PlayfieldWindow::Draw, this);
	Bind(wxEVT_MOTION, &PlayfieldWindow::in, this);
	Bind(wxEVT_IDLE, &PlayfieldWindow::onIdle, this);
	Bind(wxEVT_LEFT_DOWN, &PlayfieldWindow::onMouseDown, this);
	Bind(wxEVT_LEFT_UP, &PlayfieldWindow::onMouseUp, this);
	m_playfield = &(game.getPlayfield());
	for (int i = 0 ; i< PIECE_EMPTY; i++)
	{
		piece_images[i].LoadFile(piece_image_names[i], wxBITMAP_TYPE_PNG);
	}
}

void PlayfieldWindow::onIdle(wxIdleEvent& evt)
{
	update();
	//game.doMove(IPC::getStockfishMove().substr(8,4));
	evt.Skip();
}

void PlayfieldWindow::onMouseDown(wxMouseEvent& event)
{
	wxPoint point = event.GetPosition();
	wxSize windowSize = this->GetSize();
	int step_width = windowSize.GetWidth() / Utils::field_width;
	int step_height = windowSize.GetHeight() / Utils::field_height;
	wxPoint currentSquare;
	int row;
	int column;
	for (row = 0; row < Utils::field_height; row++)
	{
		for (column = 0; column < Utils::field_width; column++)
		{
			currentSquare = { column * step_width,  row * step_height };
			if ((point.x < currentSquare.x + step_width) && (point.y < currentSquare.y + step_height))
			{
				goto broken;
			}
		}
	}
broken:
	mousePos = point;
	row = (7 - row);
	selected_piece = (*m_playfield)[to_1d(row, column)];
	(*m_playfield)[to_1d(row, column)] = PIECE_EMPTY;
	event.Skip();
}

void PlayfieldWindow::onMouseUp(wxMouseEvent& event)
{
	wxPoint point = event.GetPosition();
	wxSize windowSize = this->GetSize();
	int step_width = windowSize.GetWidth() / Utils::field_width;
	int step_height = windowSize.GetHeight() / Utils::field_height;
	wxPoint currentSquare;
	int row;
	int column;
	for (row = 0; row < Utils::field_height; row++)
	{
		for (column = 0; column < Utils::field_width; column++)
		{
			currentSquare = { column * step_width,  row * step_height };
			if ((point.x < currentSquare.x + step_width) && (point.y < currentSquare.y + step_height))
			{
				goto broken;
			}
		}
	}
broken:
	row = (7 - row);
	(*m_playfield)[to_1d(row, column)] = selected_piece;
	selected_piece = PIECE_EMPTY;

}

void PlayfieldWindow::Draw(wxSizeEvent& event)
{
	wxInitAllImageHandlers();
	wxSize windowSize = this->GetSize();
	int step_width = windowSize.GetWidth() / Utils::field_width;
	int step_height = windowSize.GetHeight() / Utils::field_height;
	for (int i = 0; i < PIECE_EMPTY; i++)
	{
		piece_images[i].LoadFile(piece_image_names[i], wxBITMAP_TYPE_PNG);
		piece_images[i].Rescale(step_width, step_height);
	}
	event.Skip();
}

void PlayfieldWindow::update()
{
	wxInitAllImageHandlers();
	wxSize windowSize = this->GetSize();
	int step_width = windowSize.GetWidth() / Utils::field_width;
	int step_height = windowSize.GetHeight() / Utils::field_height;
	const std::vector<Piece>& playfield_ref = *m_playfield;
	wxPoint currentSquare;
	wxClientDC dc(this);
	wxBufferedDC a(&dc);
	a.Clear();
	SetBackgroundColour({ 155,0,155 });
	for (int row = 0; row < Utils::field_height; row++)
	{
		for (int column = 0; column < Utils::field_width; column++)
		{
			currentSquare = { column * step_width,  (7-row) * step_height };
			if (playfield_ref[to_1d(row, column)] >= PIECE_EMPTY) continue;
			a.DrawBitmap(piece_images[playfield_ref[to_1d(row, column)]], currentSquare);
		}
	}
	for (int row = 1; row < Utils::field_height; row++)
	{
		a.DrawLine({ 0, row * step_height }, { windowSize.GetWidth() , row * step_height });
	}
	for (int column = 1; column < Utils::field_width; column++)
	{
		a.DrawLine({ column * step_width,0 }, { column * step_width,windowSize.GetHeight() });
	}
	if (selected_piece < PIECE_EMPTY)
	{
		a.DrawBitmap(piece_images[selected_piece], mousePos);
	}
	wxInitAllImageHandlers();
	wxImage border("border.png", wxBITMAP_TYPE_PNG);
	border.Rescale(step_width, step_height);
	a.DrawBitmap(border, previousSquare);
}


void PlayfieldWindow::in(wxMouseEvent& event)
{
	wxPoint point = event.GetPosition();
	wxSize windowSize = this->GetSize();
	int step_width = windowSize.GetWidth() / Utils::field_width;
	int step_height = windowSize.GetHeight() / Utils::field_height;
	bool broke = 0;
	wxPoint currentSquare;
	for (int row = 0; row < Utils::field_height; row++)
	{
		for (int column = 0; column < Utils::field_width; column++)
		{
			currentSquare = { column * step_width,  row * step_height };
			if ((point.x < currentSquare.x + step_width) && (point.y < currentSquare.y + step_height))
			{
				goto broke_loop;
			}
		}
	}
broke_loop:
	previousSquare = currentSquare;
	if (selected_piece < PIECE_EMPTY)
	{
		mousePos = point;
		update();
	}
	event.Skip();
}