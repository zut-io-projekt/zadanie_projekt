#include "GameLogic.h"
const std::vector<std::pair<int, int>> directions{ {0,-1},{-1,0},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1} };

GameLogic::GameLogic():m_playfield(Utils::field_height * Utils::field_width)
{
	for (auto& tile : m_playfield)
	{
		tile = PIECE_EMPTY;
	}

	m_playfield[to_1d(1, 0)] = PIECE_WP;
	m_playfield[to_1d(1, 1)] = PIECE_WP;
	m_playfield[to_1d(1, 2)] = PIECE_WP;
	m_playfield[to_1d(1, 3)] = PIECE_WP;
	m_playfield[to_1d(1, 4)] = PIECE_WP;
	m_playfield[to_1d(1, 5)] = PIECE_WP;
	m_playfield[to_1d(1, 6)] = PIECE_WP;
	m_playfield[to_1d(1, 7)] = PIECE_WP;
	m_playfield[to_1d(0, 0)] = PIECE_WR;
	m_playfield[to_1d(0, 7)] = PIECE_WR;
	m_playfield[to_1d(0, 1)] = PIECE_WN;
	m_playfield[to_1d(0, 6)] = PIECE_WN;
	m_playfield[to_1d(0, 2)] = PIECE_WB;
	m_playfield[to_1d(0, 5)] = PIECE_WB;
	m_playfield[to_1d(0, 3)] = PIECE_WQ;
	m_playfield[to_1d(0, 4)] = PIECE_WK;

	m_playfield[to_1d(6, 0)] = PIECE_BP;
	m_playfield[to_1d(6, 1)] = PIECE_BP;
	m_playfield[to_1d(6, 2)] = PIECE_BP;
	m_playfield[to_1d(6, 3)] = PIECE_BP;
	m_playfield[to_1d(6, 4)] = PIECE_BP;
	m_playfield[to_1d(6, 5)] = PIECE_BP;
	m_playfield[to_1d(6, 6)] = PIECE_BP;
	m_playfield[to_1d(6, 7)] = PIECE_BP;
	m_playfield[to_1d(7, 0)] = PIECE_BR;
	m_playfield[to_1d(7, 7)] = PIECE_BR;
	m_playfield[to_1d(7, 1)] = PIECE_BN;
	m_playfield[to_1d(7, 6)] = PIECE_BN;
	m_playfield[to_1d(7, 2)] = PIECE_BB;
	m_playfield[to_1d(7, 5)] = PIECE_BB;
	m_playfield[to_1d(7, 3)] = PIECE_BQ;
	m_playfield[to_1d(7, 4)] = PIECE_BK;
}

std::vector<Piece>& GameLogic::getPlayfield()
{
	return m_playfield;
}

void GameLogic::doMove(std::string move)
{
}


