#pragma once
#include <array>
#include <vector>
#include <intrin.h>
#include <string>
#pragma warning( disable : 26495 26812 26451)

enum Piece
{
	PIECE_WP,
	PIECE_WN,
	PIECE_WB,
	PIECE_WR,
	PIECE_WQ,
	PIECE_WK,

	PIECE_BP,
	PIECE_BN,
	PIECE_BB,
	PIECE_BR,
	PIECE_BQ,
	PIECE_BK,

	PIECE_EMPTY,
	PIECE_NONE
};


enum File
{
	FILE_A,
	FILE_B,
	FILE_C,
	FILE_D,
	FILE_E,
	FILE_F,
	FILE_G,
	FILE_H,
	FILE_NONE
};

enum Rank
{
	RANK_1,
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_NONE
};

enum Square
{
	A1 = 21, A2, A3, A4, A5, A6, A7, A8,
	B1 = 31, B2, B3, B4, B5, B6, B7, B8,
	C1 = 41, C2, C3, C4, C5, C6, C7, C8,
	D1 = 51, D2, D3, D4, D5, D6, D7, D8,
	E1 = 61, E2, E3, E4, E5, E6, E7, E8,
	F1 = 71, F2, F3, F4, F5, F6, F7, F8,
	G1 = 81, G2, G3, G4, G5, G6, G7, G8,
	H1 = 91, H2, H3, H4, H5, H6, H7, H8, SQ_NONE
};

enum Castling
{
	WHITE_KING_CASTLING = 1,
	WHITE_QUEEN_CASTLING = 2,
	BLACK_KING_CASTLING = 4,
	BLACK_QUEEN_CASTLING = 8
};

enum Color
{
	WHITE,
	BLACK,
	COLOR_NONE
};


inline constexpr int coordinates_to_120array(int f, int r)
{
	return (21 + f) + (r * 10);
}


class bitboard
{
public:
	bool test_square(int sq);
	int popcnt()
	{
		return __popcnt(m_bitboard);
	}
	operator unsigned long long()
	{
		return m_bitboard;
	}
private:
	unsigned long long m_bitboard;
};


class move
{
public:
	move(int move):m_move(move)
	{}
	int to_sq();
	int from_sq();
	Piece promotion_piece();
	operator int()
	{
		return m_move;
	}
private:
	int m_move;
};


class board
{
public:
	typedef unsigned long long pos_key;

	board();
	board(const board& b) = delete;

	void do_move(const move& m);
	void do_move(const std::string& m);
	void undo_move();
	void undo_move(const move& m);
	bool is_legal(const move& m);
	bool is_legal(const move& m) const;
	const std::vector<move>& get_legal_moves() const;	
	void generate_moves();

private:
	//data members
	std::array<Piece, 120> m_pieces;				//120 piece array (includes unreachable squares for easier move generation
	std::array<bitboard, COLOR_NONE> m_pawns;		//pawn bitboards
	std::vector<pos_key> m_position_history;		//history for 3-fold repetition
	std::vector<move> m_pseudolegal_moves;			//moves which might include those that for example leave the king in check
	std::vector<move> m_legal_moves;				


	//helpers
	std::array<int, 120> Board120to64;				//120 index to 64 index for pawns
	std::array<int, 64> Board64to120;				//64 index to 120 index for the board array
	std::array<unsigned long long, 64> set_mask;
	std::array<unsigned long long, 64> clear_mask;
	unsigned long long piece_key[PIECE_EMPTY][120];
	unsigned long long side_key;
	unsigned long long castle_key[16];

	void set_bit(unsigned long long& bb, int sq)
	{
		bb |= set_mask[sq];
	}

	void clear_bit(unsigned long long& bb, int sq)
	{
		bb |= clear_mask[sq];
	}

	//position properties
	Color m_side_to_move;
	pos_key m_hash;									//64 bit zoribst hash key
	int m_fifty_move_counter;
	int m_castling_perms;
	int m_en_passant;
	int m_ply;
};

