#pragma once
#include <vector>
#include <deque>
#include <queue>
#include "Utils.h"
#include "board.h"

class GameLogic
{
public:
	GameLogic();
	std::vector<Piece>& getPlayfield();
	void doMove(std::string move);

private:
	std::vector<Piece> m_playfield;
	board b;
};

