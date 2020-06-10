#include "board.h"
#include <random>
#include <iostream>

#pragma warning( disable : 26495 26812 26451)

board::board()
{
	m_position_history.reserve(2048);
	for (auto& value : Board64to120)
	{
		value = SQ_NONE;
	}
	for (auto& value : Board120to64)
	{
		value = SQ_NONE;
	}
	int sq64 = 0;
	for (int rank = RANK_1; rank <= RANK_8; rank++)
	{
		for (int file = FILE_A; file <= FILE_H; file++)
		{
			Board64to120[sq64] = coordinates_to_120array(file, rank);
			Board120to64[Board64to120[sq64]] = sq64;
			sq64++;
		}
	}
	std::mt19937_64 rng(0);
	for (auto& piece_types : piece_key)
	{
		for (auto& square : piece_types)
		{
			square = rng();
			//std::cout << square<<"\n";
		}
	}
	side_key = rng();
	for (auto& key : castle_key)
	{
		key = rng();
	}
}


void board::generate_moves()
{
	int pawn_direction = m_side_to_move == WHITE ? 10 : -10;

	const std::vector<int> bishop_directions = { 9, 11, -9, -11 };
	const std::vector<int> rook_directions = { 1,-1, 10, -10 };
	const std::vector<int> knight_directions = { -21,-19, 21, 19 };
	const std::vector<int> king_directions = { -1,-10, -11, -9, 1,10, 11, 9 };

	std::vector<move>& available_moves = m_pseudolegal_moves;
	for (int square = 21 ; square < 99; square++)
	{
		//white pieces - values 0 to 5
		//black pieces - values 6 to 11
		if (m_pieces[square] == SQ_NONE) continue;

		if ((m_pieces[square] == PIECE_BN && m_side_to_move == BLACK) ||( m_pieces[square] == PIECE_WN && m_side_to_move == WHITE))
		{
			for (const auto direction : knight_directions)
			{
				Piece p = m_pieces[square + direction];
				if (p == PIECE_EMPTY || m_side_to_move == WHITE ? (p > PIECE_WK && p < PIECE_EMPTY) : (p <= PIECE_WK))
				{
					//lowest 6 bits - to_sq
					//higher 6 bits - from_sq
					move m = Board120to64[(square + direction)] | Board120to64[square] << 6;
					available_moves.push_back(m);
				}
			}
		}
		if ((m_pieces[square] == PIECE_BB && m_side_to_move == BLACK) || (m_pieces[square] == PIECE_WB && m_side_to_move == WHITE))
		{
			int target_sq = square;
			for (const auto direction : bishop_directions)
			{
				while (true)
				{
					target_sq += direction;
					Piece p = m_pieces[target_sq];
					if (!(p == PIECE_EMPTY || m_side_to_move == WHITE ? (p > PIECE_WK && p < PIECE_EMPTY) : (p <= PIECE_WK)))
					{
						break;
					}
					//lowest 6 bits - to_sq
					//higher 6 bits - from_sq
					move m = Board120to64[target_sq] | Board120to64[square] << 6;
					available_moves.push_back(m);
				}
				target_sq = square;
			}
		}
		if ((m_pieces[square] == PIECE_BR && m_side_to_move == BLACK) || (m_pieces[square] == PIECE_WR && m_side_to_move == WHITE))
		{
			int target_sq = square;
			for (const auto direction : rook_directions)
			{
				while (true)
				{
					target_sq += direction;
					Piece p = m_pieces[target_sq];
					if (!(p == PIECE_EMPTY || m_side_to_move == WHITE ? (p > PIECE_WK && p < PIECE_EMPTY) : (p <= PIECE_WK)))
					{
						break;
					}
					//lowest 6 bits - to_sq
					//higher 6 bits - from_sq
					move m = Board120to64[target_sq] | Board120to64[square] << 6;
					available_moves.push_back(m);
				}
				target_sq = square;
			}
		}
		if ((m_pieces[square] == PIECE_BK && m_side_to_move == BLACK) || (m_pieces[square] == PIECE_WK && m_side_to_move == WHITE))
		{
			for (const auto direction : king_directions)
			{
				Piece p = m_pieces[square + direction];
				if (p == PIECE_EMPTY || m_side_to_move == WHITE ? (p > PIECE_WK && p < PIECE_EMPTY) : (p <= PIECE_WK))
				{
					//lowest 6 bits - to_sq
					//higher 6 bits - from_sq
					move m = Board120to64[(square + direction)] | Board120to64[square] << 6;
					available_moves.push_back(m);
				}
			}
		}
		if ((m_pieces[square] == PIECE_BP && m_side_to_move == BLACK) || (m_pieces[square] == PIECE_WP && m_side_to_move == WHITE))
		{
			Piece p = m_pieces[square + pawn_direction];
			if (p == PIECE_EMPTY)
			{
				move m = Board120to64[square + pawn_direction] | Board120to64[square] << 6;
				available_moves.push_back(m);
				if (square > 20 && square < 29)
				{
					p = m_pieces[square + pawn_direction + pawn_direction];
					if (p == PIECE_EMPTY)
					{
						m = Board120to64[square + pawn_direction] | Board120to64[square] << 6;
						available_moves.push_back(m);
					}
				}
			}
			
		}
	}


}

