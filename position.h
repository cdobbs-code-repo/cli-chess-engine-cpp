//position.h

//specification file
//chess engine 
//position.h
#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include <string>

struct move_params {
	char piece;
	int col;
	int row;
	int new_col;
	int new_row;
};

class position{
	public:
		position();
		void move(int col1,int row1, int col2, int row2, bool clear);
		void find_legal_moves(bool white_or_black);
		//this calls private search functions for a given side
		void print_board();
		void print_move_list(char b_or_w);
		
		friend class evaluate;
		std::vector<move_params> black_move_list;
		std::vector<move_params> white_move_list;
		char board[8][8];
		//friend int maxi(position board1, int depth, move_params& best_white_move);
		//friend int mini(position board1, int depth, move_params& best_black_move);
	private:
		void find_whitePawnMoves(const int i,const int j);
		void find_blackPawnMoves(const int i,const int j);
		void find_whiteKnightMoves(const int i,const int j);
		void find_blackKnightMoves(const int i,const int j);
		void find_whiteRookMoves(const int i,const int j);
		void find_blackRookMoves(const int i,const int j);
		void find_whiteBishopMoves(const int i,const int j);
		void find_blackBishopMoves(const int i,const int j);
		void find_whiteKingMoves(const int i,const int j);
		void find_blackKingMoves(const int i,const int j);
		void find_whiteQueenMoves(const int i,const int j);
		void find_blackQueenMoves(const int i,const int j);
};

#endif








