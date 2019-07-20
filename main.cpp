//chess engine 2.0

#include <iostream>
#include "position.h"
#include "evaluate.h"

using namespace std;

double maxi(position board1, int depth);
double b_maxi(position board1, int depth);

move_params best_white_move;
move_params best_black_move;

const bool CLEAR        = 1;
const bool DO_NOT_CLEAR = 0;
const bool WHITE        = 1;
const bool BLACK        = 0;

const int DEPTH         = 4;

int input = 42;

int main()
{
	position test_game;
	evaluate evaluator;
	int col1, row1, col2, row2;
	while(input != 17){
		cout << "Enter a command: \n"
			 << "0 (print board)\n"
			 << "1 (find legal white moves)\n"
			 << "2 (find legal black moves)\n"
			 << "3 (print white move list)\n"
			 << "4 (print black move list)\n"
			 << "5 (piece move)\n"
			 << "6 (evaluate position for white)\n"
			 << "7 (evaluate position for black)\n"
			 << "8 (find best white move)\n"
			 << "9 (determine if white is in check)\n"
			 << "10 (determine if black is in check)\n"
			 << "17 (exit program)\n";
		cin >> input;
		switch(input){
			case 0:
				test_game.print_board();
				break;
			case 1:
				test_game.find_legal_moves(WHITE);
				break;
			case 2:
				test_game.find_legal_moves(BLACK);
				break;
			case 3:
				test_game.print_move_list('w');
				break;
			case 4:
				test_game.print_move_list('b');
				break;	
			case 5:
				cout << "Piece move. Enter col, row, new_col new_row:\n";
				cin >> col1 >> row1 >> col2 >> row2;
				test_game.move(col1,row1,col2,row2, CLEAR);
				break;
			case 6: 
				cout << "Evaluating the position for white...\n";
				cout << "score = " << evaluator.evaluate_position(test_game,WHITE) << endl;
				break;
			case 7: 
				cout << "Evaluating the position for black...\n";
				cout << "score = " << evaluator.evaluate_position(test_game,BLACK) << endl;
				break;
			case 8:
				cout << "Finding best move for white...\n";
				cout << "estimated move value: " << maxi(test_game, DEPTH) << endl;
				cout << "piece: " << best_white_move.piece << endl;
				cout << "new col: " << best_white_move.new_col << endl;
				cout << "new row: " << best_white_move.new_row << endl;
				cout << "old col: " << best_white_move.col << endl;
				cout << "old row: " << best_white_move.row << endl;
				break;
			case 9:
				cout << "Determining if white is in check...\n";
				if(evaluator.whiteCheck(test_game))
					cout << "White is in check.\n";
				else
					cout << "White is not in check.\n";
				break;
			case 10:
				cout << "Determining if black is in check...\n";
				if(evaluator.blackCheck(test_game))
					cout << "Black is in check.\n";
				else
					cout << "Black is not in check.\n";
				break;
		}
	}
	return 0;
}

double maxi(position board1, int depth){
	//FIRST ERASE MOVE LIST IF NOT EMPTY!
	if(board1.white_move_list.size() > 0)
		board1.white_move_list.clear();
	if(board1.black_move_list.size() > 0)
		board1.black_move_list.clear();
	
	double score = 0;
	evaluate evaluator;
	if(depth == 0) return evaluator.evaluate_position(board1, WHITE);
	double max = -109009000;
	
	//if(evaluator.inCheck)..
	// ..then board1.find_legal_moves(WHITE, in_Check);
	//else
	// ..then board1.find_legal_moves(WHITE, not_in_Check);
	board1.find_legal_moves(WHITE);
	
	for(int i = 0; i < board1.white_move_list.size();i++){
		int new_row = board1.white_move_list[i].new_row;
		int new_col = board1.white_move_list[i].new_col;
		int old_row = board1.white_move_list[i].row;
		int old_col = board1.white_move_list[i].col;
		char temp_piece = board1.board[new_col][new_row];

		//now move,				
		board1.move(old_col,old_row,new_col,new_row, DO_NOT_CLEAR);
				
		//call b_maxi,
		score = -b_maxi(board1, depth - 1);
		
		//update score and GLOBAL best white move if in main depth,
		if(score > max){
			max = score;
			if(depth == DEPTH){
				best_white_move.piece = board1.board[new_col][new_row];
				best_white_move.col   = old_col;
				best_white_move.row   = old_row;
				best_white_move.new_col = new_col;
				best_white_move.new_row = new_row;
			}
		}
		
		//and unmove
		board1.board[old_col][old_row] = board1.board[new_col][new_row];
		board1.board[new_col][new_row] = temp_piece;
	}
	return max;
}

double b_maxi(position board1, int depth){
	//FIRST ERASE MOVE LIST IF NOT EMPTY!
	if(board1.white_move_list.size() > 0)
		board1.white_move_list.clear();
	if(board1.black_move_list.size() > 0)
		board1.black_move_list.clear();
		
	double score = 0;
	evaluate evaluator;
	if(depth == 0){ 
		double ret_val = evaluator.evaluate_position(board1, BLACK);
		return ret_val;
	}
	double max = -109000900;
	board1.find_legal_moves(BLACK);

	for(int i = 0; i < board1.black_move_list.size();i++){
		int new_row = board1.black_move_list[i].new_row;
		int new_col = board1.black_move_list[i].new_col;
		int old_row = board1.black_move_list[i].row;
		int old_col = board1.black_move_list[i].col;
		char temp_piece = board1.board[new_col][new_row];
		//now move,
		
		board1.move(old_col,old_row,new_col,new_row, DO_NOT_CLEAR);
		
		//call maxi,				
		score = -maxi(board1, depth - 1);
		
		//update score and GLOBAL best black move,
		if(score > max){
			max = score;
			if(depth == DEPTH){
				best_black_move.piece = board1.board[new_col][new_row];
				best_black_move.col   = old_col;
				best_black_move.row   = old_row;
				best_black_move.new_col = new_col;
				best_black_move.new_row = new_row;
			}
		}

		//and unmove
		board1.board[old_col][old_row] = board1.board[new_col][new_row];
		board1.board[new_col][new_row] = temp_piece;
	}
	return max;
}














