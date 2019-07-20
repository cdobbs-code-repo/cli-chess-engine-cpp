//implementation file
//chess engine
//position.cpp
#include "position.h"
#include <iostream>
#include <string>
#include <cctype> //using this library for now. Documentation appears
				  //to stress including 'locale' info, but tested with
				  //only the characters we will use, it works so no locale
				  //information included.
				  //Included functions:
				  //isupper(char x) and islower(char y)
				  //note: '#' returns false for both

enum {a,b,c,d,e,f,g,h};
enum {one,two,three,four,five,six,seven,eight};

const int BOARDSIZE = 8;

position::position()
{
	//Note: in order to just use characters the
	//uppercase indicates white and the lower case
	//indicates black. 
	//white starting position:
	board[a][one] = 'R';
	board[b][one] = 'N';
	board[c][one] = 'B';
	board[d][one] = 'Q';
	board[e][one] = 'K';
	board[f][one] = 'B';
	board[g][one] = 'N';
	board[h][one] = 'R';
	board[a][two] = 'P';
	board[b][two] = 'P';
	board[c][two] = 'P';
	board[d][two] = 'P';
	board[e][two] = 'P';
	board[f][two] = 'P';
	board[g][two] = 'P';
	board[h][two] = 'P';
	//black starting position:
	board[a][eight] = 'r';
	board[b][eight] = 'n';
	board[c][eight] = 'b';
	board[d][eight] = 'q';
	board[e][eight] = 'k';
	board[f][eight] = 'b';
	board[g][eight] = 'n';
	board[h][eight] = 'r';
	board[a][seven] = 'p';
	board[b][seven] = 'p';
	board[c][seven] = 'p';
	board[d][seven] = 'p';
	board[e][seven] = 'p';
	board[f][seven] = 'p';
	board[g][seven] = 'p';
	board[h][seven] = 'p';
	//other spaces empty. Set to '#'
	for(int i=a;i<=h;i++)
		for(int j=three; j<= six; j++)
			board[i][j]='#';
}

void position::print_board()
{
	for(int i=BOARDSIZE-1; i>=0; i--){
		for(int j=0; j<BOARDSIZE; j++){
			std::cout << board[j][i];
		}
		std::cout << "\n";
	}
}

void position::move(int col1,int row1, int col2, int row2, bool clear){
	//!!ONLY CLEAR IF NOT IN MINI OR MAXI FUNCTION SINCE IN THOSE CASES
	//  MOVES ARE CONTINUOUSLY 'UNDONE' !!
	if(clear == 1){
		if(white_move_list.size() > 0)//emptying possible move list after position changes
			white_move_list.clear();
		if(black_move_list.size() > 0)
			black_move_list.clear();
	}
	
	//The final three lines are sufficient for everything except pawn promotion,
	//en passent, and castling
	
	//castling
	
	//en passent
	
	//pawn promotion (always promoting to Queen for now)
	if(board[col1][row1] == 'P' && row1 == 6)//no exceptions here, pawn can only move forward!
	{
		board[col1][row1] = '#';
		board[col2][row2] = 'Q';
	}
	else if(board[col1][row1] == 'p' && row1 == 1)//no exceptions here, pawn can only move forward!
	{
		board[col1][row1] = '#';
		board[col2][row2] = 'q';
	}
	else{
		char temp = board[col1][row1];
		board[col1][row1] = '#';
		board[col2][row2] = temp;
	}
}

void position::find_legal_moves(bool white_or_black){
	if(white_or_black == 1){//(white is one..)
		for(int i = 0; i < BOARDSIZE; i++){
			for(int j = 0; j < BOARDSIZE; j++){
				switch(board[i][j]){
					case 'P':
						find_whitePawnMoves(i,j);
						break;
					case 'N':
						find_whiteKnightMoves(i,j);
						break;
					case '#':
						break;
					case 'R':
						find_whiteRookMoves(i,j);
						break;
					case 'B':
						find_whiteBishopMoves(i,j);
						break;
					case 'K':
						find_whiteKingMoves(i,j);
						break;
					case 'Q':
						find_whiteQueenMoves(i,j);	
						break;	
				}
			}
		}
	}else{
		for(int i = 0; i < BOARDSIZE; i++){
			for(int j = 0; j < BOARDSIZE; j++){
				switch(board[i][j]){
					case 'p': //LOWERCASE !!!
						find_blackPawnMoves(i,j);
						break;
					case 'n':
						find_blackKnightMoves(i,j);
						break;
					case '#':
						break;
					case 'r':
						find_blackRookMoves(i,j);
						break;
					case 'b':
						find_blackBishopMoves(i,j);
						break;
					case 'k':
						find_blackKingMoves(i,j);
						break;
					case 'q':
						find_blackQueenMoves(i,j);
						break;
				}
			}
		}
	}
}

void position::print_move_list(char b_or_w){
	if(b_or_w == 'w'){
		int size = white_move_list.size();
		std::cout << "printing moves...\n";//might be worth while to convert moves to more
										   //readable format..
		for(int i = 0; i < size; i++){
			std::cout << "piece: " << white_move_list[i].piece << "\n"
					  << "board[col][row]: " << board[white_move_list[i].col][white_move_list[i].row] << "\n" 
					  << "col,row:" << white_move_list[i].col << "," << white_move_list[i].row << "\n"
					  << "new_col,new_row:" << white_move_list[i].new_col << "," << white_move_list[i].new_row << "\n\n";
		}
		std::cout << "moves printed.\n";
	}else{
		int size = black_move_list.size();
		std::cout << "printing moves...\n";//might be worth while to convert moves to more
										   //readable format..
		for(int i = 0; i < size; i++){
			std::cout << "piece: " << black_move_list[i].piece << "\n"
					  << "col,row:" << black_move_list[i].col << "," << black_move_list[i].row << "\n"
					  << "new_col,new_row:" << black_move_list[i].new_col << "," << black_move_list[i].new_row << "\n\n";
		}
		std::cout << "moves printed.\n";
	}
}


void position::find_whitePawnMoves(const int i,const int j){
	move_params temp_move;
	if(board[i][j]=='P'){
		//1. check diagonals for piece capture (remember that black pieces
		//            are lowercase).
		if(islower(board[i+1][j+1]) && i+1 < BOARDSIZE && j+1 < BOARDSIZE){
			temp_move.piece='P';
			temp_move.col=i;
			temp_move.row=j;
			temp_move.new_col=i+1;
			temp_move.new_row=j+1;
			white_move_list.push_back(temp_move);
		}
		if(islower(board[i-1][j+1]) && i-1 >= 0 && j+1 < BOARDSIZE){
			temp_move.piece='P';
			temp_move.col=i;
			temp_move.row=j;
			temp_move.new_col=i-1;
			temp_move.new_row=j+1;
			white_move_list.push_back(temp_move);
		}
		//2. check one square ahead for one square move
		if(board[i][j+1]=='#' && j+1 < BOARDSIZE){
			temp_move.piece='P';
			temp_move.col=i;
			temp_move.row=j;
			temp_move.new_col=i;
			temp_move.new_row=j+1;
			white_move_list.push_back(temp_move);	
		}
		//3. if on second row (indexed as 1 so use enum), check one square move
		//   and check two square move
		if(j == two && board[i][three] == '#' && board[i][four] == '#'){
			temp_move.piece='P';
			temp_move.col=i;
			temp_move.row=j;
			temp_move.new_col=i;
			temp_move.new_row=j+2;
			white_move_list.push_back(temp_move);	
		}
		//4. [add this later] check last move for en passent possibility
	}
}

void position::find_blackPawnMoves(const int i, const int j){
	move_params temp_move;
	if(board[i][j]=='p'){
		//1. check diagonals for piece capture (remember that black pieces
		//            are lowercase).
		if(isupper(board[i+1][j-1]) && i+1 < BOARDSIZE && j-1 >= 0){
			temp_move.piece='p';
			temp_move.col=i;
			temp_move.row=j;
			temp_move.new_col=i+1;
			temp_move.new_row=j-1;
			black_move_list.push_back(temp_move);
		}
		if(isupper(board[i-1][j-1]) && i-1 >= 0 && j-1 >= 0){
			temp_move.piece='p';
			temp_move.col=i;
			temp_move.row=j;
			temp_move.new_col=i-1;
			temp_move.new_row=j-1;
			black_move_list.push_back(temp_move);
		}
		//2. check one square ahead for one square move
		if(board[i][j-1]=='#' && j-1 >= 0){
			temp_move.piece='p';
			temp_move.col=i;
			temp_move.row=j;
			temp_move.new_col=i;
			temp_move.new_row=j-1;
			black_move_list.push_back(temp_move);	
		}
		//3. if on seventh row (indexed as 6 so use enum), check one square move
		//   and check two square move
		if(j == seven && board[i][six] == '#' && board[i][five] == '#'){
			temp_move.piece='p';
			temp_move.col=i;
			temp_move.row=j;
			temp_move.new_col=i;
			temp_move.new_row=j-2;
			black_move_list.push_back(temp_move);	
		}
		//4. [add this later] check last move for en passent possibility
	}
}

void position::find_whiteKnightMoves(const int i, const int j){
	move_params temp_move;
	if(board[i][j]=='N'){
		//At most, the knight can move to eight different squares.
		//Therefore, we just need to check all eight squares then we're done.
		
		//square 1 - starting with upper right square and moving clockwise
		if(!isupper(board[i+2][j+1]) && i+2 < BOARDSIZE && j+1 < BOARDSIZE){//i.e. if not white, then...
			temp_move.piece   = 'N';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i+2;
			temp_move.new_row = j+1;
			white_move_list.push_back(temp_move);
		}
		//square 2
		if(!isupper(board[i+1][j+2]) && i+1 < BOARDSIZE && j+2 < BOARDSIZE){
			temp_move.piece   = 'N';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i+1;
			temp_move.new_row = j+2;
			white_move_list.push_back(temp_move);
		}
		//square 3
		if(!isupper(board[i-1][j+2]) && i-1 >= 0 && j+2 < BOARDSIZE){
			temp_move.piece   = 'N';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i-1;
			temp_move.new_row = j+2;
			white_move_list.push_back(temp_move);
		}
		//square 4
		if(!isupper(board[i-2][j+1]) && i-2 >= 0 && j+1 < BOARDSIZE){
			temp_move.piece   = 'N';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i-2;
			temp_move.new_row = j+1;
			white_move_list.push_back(temp_move);
		}
		//square 5
		if(!isupper(board[i-2][j-1]) && i-2 >= 0 && j-1 >= 0){
			temp_move.piece   = 'N';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i-2;
			temp_move.new_row = j-1;
			white_move_list.push_back(temp_move);
		}
		//square 6
		if(!isupper(board[i-1][j-2]) && i-1 >= 0 && j-2 >= 0){
			temp_move.piece   = 'N';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i-1;
			temp_move.new_row = j-2;
			white_move_list.push_back(temp_move);
		}
		//square 7
		if(!isupper(board[i+1][j-2]) && i+1 < BOARDSIZE && j-2 >= 0){
			temp_move.piece   = 'N';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i+1;
			temp_move.new_row = j-2;
			white_move_list.push_back(temp_move);
		}
		//square 8 
		if(!isupper(board[i+2][j-1]) && i+2 < BOARDSIZE && j-1 >= 0){
			temp_move.piece   = 'N';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i+2;
			temp_move.new_row = j-1;
			white_move_list.push_back(temp_move);
		}
	}
}


void position::find_blackKnightMoves(const int i, const int j){
	move_params temp_move;
	if(board[i][j]=='n'){
		//At most, the knight can move to eight different squares.
		//Therefore, we just need to check all eight squares then we're done.
		
		//square 1 - starting with upper right square and moving clockwise
		if(!islower(board[i+2][j+1]) && i+2 < BOARDSIZE && j+1 < BOARDSIZE){//i.e. if not black, then...
			temp_move.piece   = 'n';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i+2;
			temp_move.new_row = j+1;
			black_move_list.push_back(temp_move);
		}
		//square 2
		if(!islower(board[i+1][j+2]) && i+1 < BOARDSIZE && j+2 < BOARDSIZE){
			temp_move.piece   = 'n';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i+1;
			temp_move.new_row = j+2;
			black_move_list.push_back(temp_move);
		}
		//square 3
		if(!islower(board[i-1][j+2]) && i-1 >= 0 && j+2 < BOARDSIZE){
			temp_move.piece   = 'n';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i-1;
			temp_move.new_row = j+2;
			black_move_list.push_back(temp_move);
		}
		//square 4
		if(!islower(board[i-2][j+1]) && i-2 >= 0 && j+1 < BOARDSIZE){
			temp_move.piece   = 'n';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i-2;
			temp_move.new_row = j+1;
			black_move_list.push_back(temp_move);
		}
		//square 5
		if(!islower(board[i-2][j-1]) && i-2 >= 0 && j-1 >= 0){
			temp_move.piece   = 'n';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i-2;
			temp_move.new_row = j-1;
			black_move_list.push_back(temp_move);
		}
		//square 6
		if(!islower(board[i-1][j-2]) && i-1 >= 0 && j-2 >= 0){
			temp_move.piece   = 'n';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i-1;
			temp_move.new_row = j-2;
			black_move_list.push_back(temp_move);
		}
		//square 7
		if(!islower(board[i+1][j-2]) && i+1 < BOARDSIZE && j-2 >= 0){
			temp_move.piece   = 'n';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i+1;
			temp_move.new_row = j-2;
			black_move_list.push_back(temp_move);
		}
		//square 8 
		if(!islower(board[i+2][j-1]) && i+2 < BOARDSIZE && j-1 >= 0){
			temp_move.piece   = 'n';
			temp_move.col     = i;
			temp_move.row     = j;
			temp_move.new_col = i+2;
			temp_move.new_row = j-1;
			black_move_list.push_back(temp_move);
		}
	}
}

void position::find_whiteRookMoves(const int i, const int j){
	move_params temp_move;
	if(board[i][j] == 'R'){
		//check up direction
		for(int row = j+1; row < BOARDSIZE; row++){
		//-if empty, add move to list and continue
			if(board[i][row] == '#'){
				temp_move.piece = 'R';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = i;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[i][row])){
					temp_move.piece = 'R';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = i;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check down
		for(int row = j-1; row >= 0; row--){
		//-if empty, add move to list and continue
			if(board[i][row] == '#'){
				temp_move.piece = 'R';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = i;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[i][row])){
					temp_move.piece = 'R';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = i;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check left
		for(int col = i-1; col >= 0; col--){
		//-if empty, add move to list and continue
			if(board[col][j] == '#'){
				temp_move.piece = 'R';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = j;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][j])){
					temp_move.piece = 'R';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = j;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check right
		for(int col = i+1; col < BOARDSIZE; col++){
		//-if empty, add move to list and continue
			if(board[col][j] == '#'){
				temp_move.piece = 'R';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = j;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][j])){
					temp_move.piece = 'R';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = j;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
	}	
}

void position::find_blackRookMoves(const int i, const int j){
	move_params temp_move;
	if(board[i][j] == 'r'){
		//check up direction
		for(int row = j+1; row < BOARDSIZE; row++){
		//-if empty, add move to list and continue
			if(board[i][row] == '#'){
				temp_move.piece = 'r';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = i;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[i][row])){
					temp_move.piece = 'r';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = i;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check down
		for(int row = j-1; row >= 0; row--){
		//-if empty, add move to list and continue
			if(board[i][row] == '#'){
				temp_move.piece = 'r';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = i;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[i][row])){
					temp_move.piece = 'r';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = i;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check left
		for(int col = i-1; col >= 0; col--){
		//-if empty, add move to list and continue
			if(board[col][j] == '#'){
				temp_move.piece = 'r';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = j;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][j])){
					temp_move.piece = 'r';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = j;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check right
		for(int col = i+1; col < BOARDSIZE; col++){
		//-if empty, add move to list and continue
			if(board[col][j] == '#'){
				temp_move.piece = 'r';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = j;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][j])){
					temp_move.piece = 'r';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = j;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
	}	
}

void position::find_whiteBishopMoves(const int i, const int j){
	move_params temp_move;
	if(board[i][j] == 'B'){
		//check NW
		int col = i;
		for(int row = j+1; row < BOARDSIZE; row++){
			col--;//row and column increment each iteration (diagonal!)
			if(col < 0)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'B';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][row])){
					temp_move.piece = 'B';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check NE
		col = i;
		for(int row = j+1; row < BOARDSIZE; row++){
			col++;//row and column increment each iteration (diagonal!)
			if(col >= BOARDSIZE)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'B';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][row])){
					temp_move.piece = 'B';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check SE
		col = i;
		for(int row = j-1; row >= 0; row--){
			col++;//row and column increment each iteration (diagonal!)
			if(col >= BOARDSIZE)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'B';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][row])){
					temp_move.piece = 'B';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check SW
		col = i;
		for(int row = j-1; row >= 0; row--){
			col--;//row and column increment each iteration (diagonal!)
			if(col < 0)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'B';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][row])){
					temp_move.piece = 'B';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
	}
}

void position::find_blackBishopMoves(const int i, const int j){
	move_params temp_move;
	if(board[i][j] == 'b'){
		//check NW
		int col = i;
		for(int row = j+1; row < BOARDSIZE; row++){
			col--;//row and column increment each iteration (diagonal!)
			if(col < 0)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'b';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][row])){
					temp_move.piece = 'b';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check NE
		col = i;
		for(int row = j+1; row < BOARDSIZE; row++){
			col++;//row and column increment each iteration (diagonal!)
			if(col >= BOARDSIZE)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'b';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][row])){
					temp_move.piece = 'b';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check SE
		col = i;
		for(int row = j-1; row >= 0; row--){
			col++;//row and column increment each iteration (diagonal!)
			if(col >= BOARDSIZE)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'b';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][row])){
					temp_move.piece = 'b';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check SW
		col = i;
		for(int row = j-1; row >= 0; row--){
			col--;//row and column increment each iteration (diagonal!)
			if(col < 0)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'b';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][row])){
					temp_move.piece = 'b';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
	}
}

void position::find_whiteKingMoves(const int i, const int j){
	//king can only move to, at most, 8 adjacent square.
	//Just need to check each square.
	//Note about check: As of now, not incorporating check.
	//This has two reasons beyond obvious complexity considerations:
	//1. The evaluate function will place losing the king as nearly infinitely 'bad' (negative)
	//and thus the program should be able to avoid check since that would lead to
	//losing the king (the worst alternative). If it's unavoidable to move into check then either it's
	//stalemate or it's checkmate. 
	//2. And that leads to the second point - checking for stalemate or checkmate separately
	//each time seems reasonably sufficient for now.
	move_params temp_move;
	//square 1 (start at top and move clockwise)
	if(!isupper(board[i][j+1]) && j+1 < BOARDSIZE){
		temp_move.piece = 'K';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i;
		temp_move.new_row = j+1;
		white_move_list.push_back(temp_move);	
	}
	//suqare 2
	if(!isupper(board[i+1][j+1]) && j+1 < BOARDSIZE && i+1 < BOARDSIZE){
		temp_move.piece = 'K';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i+1;
		temp_move.new_row = j+1;
		white_move_list.push_back(temp_move);	
	}
	//suqare 3
	if(!isupper(board[i+1][j]) && i+1 < BOARDSIZE){
		temp_move.piece = 'K';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i+1;
		temp_move.new_row = j;
		white_move_list.push_back(temp_move);	
	}
	//suqare 4
	if(!isupper(board[i+1][j-1]) && i+1 < BOARDSIZE && j-1 >= 0){
		temp_move.piece = 'K';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i+1;
		temp_move.new_row = j-1;
		white_move_list.push_back(temp_move);	
	}
	//suqare 5
	if(!isupper(board[i][j-1]) && j-1 >= 0){
		temp_move.piece = 'K';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i;
		temp_move.new_row = j-1;
		white_move_list.push_back(temp_move);	
	}
	//suqare 6
	if(!isupper(board[i-1][j-1]) && j-1 >= 0 && i-1 >= 0){
		temp_move.piece = 'K';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i-1;
		temp_move.new_row = j-1;
		white_move_list.push_back(temp_move);	
	}
	//suqare 7
	if(!isupper(board[i-1][j]) && i-1 >= 0){
		temp_move.piece = 'K';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i-1;
		temp_move.new_row = j;
		white_move_list.push_back(temp_move);	
	}
	//suqare 8
	if(!isupper(board[i-1][j+1]) && i-1 >= 0 && j+1 < BOARDSIZE){
		temp_move.piece = 'K';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i-1;
		temp_move.new_row = j+1;
		white_move_list.push_back(temp_move);	
	}
}

void position::find_blackKingMoves(const int i, const int j){
	//king can only move to, at most, 8 adjacent square.
	//Just need to check each square.
	//Note about check: As of now, not incorporating check.
	//This has two reasons beyond obvious complexity considerations:
	//1. The evaluate function will place losing the king as nearly infinitely 'bad' (negative)
	//and thus the program should be able to avoid check since that would lead to
	//losing the king (the worst alternative). If it's unavoidable to move into check then either it's
	//stalemate or it's checkmate. 
	//2. And that leads to the second point - checking for stalemate or checkmate separately
	//each time seems reasonably sufficient for now.
	move_params temp_move;
	//square 1 (start at top and move clockwise)
	if(!islower(board[i][j+1]) && j+1 < BOARDSIZE){
		temp_move.piece = 'k';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i;
		temp_move.new_row = j+1;
		black_move_list.push_back(temp_move);	
	}
	//suqare 2
	if(!islower(board[i+1][j+1]) && j+1 < BOARDSIZE && i+1 < BOARDSIZE){
		temp_move.piece = 'k';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i+1;
		temp_move.new_row = j+1;
		black_move_list.push_back(temp_move);	
	}
	//suqare 3
	if(!islower(board[i+1][j]) && i+1 < BOARDSIZE){
		temp_move.piece = 'k';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i+1;
		temp_move.new_row = j;
		black_move_list.push_back(temp_move);	
	}
	//suqare 4
	if(!islower(board[i+1][j-1]) && i+1 < BOARDSIZE && j-1 >= 0){
		temp_move.piece = 'k';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i+1;
		temp_move.new_row = j-1;
		black_move_list.push_back(temp_move);	
	}
	//suqare 5
	if(!islower(board[i][j-1]) && j-1 >= 0){
		temp_move.piece = 'k';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i;
		temp_move.new_row = j-1;
		black_move_list.push_back(temp_move);	
	}
	//suqare 6
	if(!islower(board[i-1][j-1]) && j-1 >= 0 && i-1 >= 0){
		temp_move.piece = 'k';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i-1;
		temp_move.new_row = j-1;
		black_move_list.push_back(temp_move);	
	}
	//suqare 7
	if(!islower(board[i-1][j]) && i-1 >= 0){
		temp_move.piece = 'k';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i-1;
		temp_move.new_row = j;
		black_move_list.push_back(temp_move);	
	}
	//suqare 8
	if(!islower(board[i-1][j+1]) && i-1 >= 0 && j+1 < BOARDSIZE){
		temp_move.piece = 'k';
		temp_move.col = i;
		temp_move.row = j;
		temp_move.new_col = i-1;
		temp_move.new_row = j+1;
		black_move_list.push_back(temp_move);	
	}
}

void position::find_whiteQueenMoves(const int i, const int j){
	move_params temp_move;
	//Horizontal and Vertical movements
	//up
	for(int row = j+1; row < BOARDSIZE; row++){
	//-if empty, add move to list and continue
		if(board[i][row] == '#'){
			temp_move.piece = 'Q';
			temp_move.col = i;
			temp_move.row = j;
			temp_move.new_col = i;
			temp_move.new_row = row;
			white_move_list.push_back(temp_move);
			continue;
		}else{
	//-else if occupied with a piece either:
	//--a. add capture to move list and break loop 
			if(islower(board[i][row])){
				temp_move.piece = 'Q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = i;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				break;
			}else{//(in the case it is a friendly piece)
	//--b. just break loop
				break;
			}
		}
	}
	//down
	for(int row = j-1; row >= 0; row--){
	//-if empty, add move to list and continue
		if(board[i][row] == '#'){
			temp_move.piece = 'Q';
			temp_move.col = i;
			temp_move.row = j;
			temp_move.new_col = i;
			temp_move.new_row = row;
			white_move_list.push_back(temp_move);
			continue;
		}else{
	//-else if occupied with a piece either:
	//--a. add capture to move list and break loop 
			if(islower(board[i][row])){
				temp_move.piece = 'Q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = i;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				break;
			}else{//(in the case it is a friendly piece)
	//--b. just break loop
				break;
			}
		}
	}
	//left
	for(int col = i-1; col >= 0; col--){
	//-if empty, add move to list and continue
		if(board[col][j] == '#'){
			temp_move.piece = 'Q';
			temp_move.col = i;
			temp_move.row = j;
			temp_move.new_col = col;
			temp_move.new_row = j;
			white_move_list.push_back(temp_move);
			continue;
		}else{
	//-else if occupied with a piece either:
	//--a. add capture to move list and break loop 
			if(islower(board[col][j])){
				temp_move.piece = 'Q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = j;
				white_move_list.push_back(temp_move);
				break;
			}else{//(in the case it is a friendly piece)
	//--b. just break loop
				break;
			}
		}
	}
	//right
	for(int col = i+1; col < BOARDSIZE; col++){
	//-if empty, add move to list and continue
		if(board[col][j] == '#'){
			temp_move.piece = 'Q';
			temp_move.col = i;
			temp_move.row = j;
			temp_move.new_col = col;
			temp_move.new_row = j;
			white_move_list.push_back(temp_move);
			continue;
		}else{
	//-else if occupied with a piece either:
	//--a. add capture to move list and break loop 
			if(islower(board[col][j])){
				temp_move.piece = 'Q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = j;
				white_move_list.push_back(temp_move);
				break;
			}else{//(in the case it is a friendly piece)
	//--b. just break loop
				break;
			}
		}
	}
	
	//Diagonal movements
	//check NW
		int col = i;
		for(int row = j+1; row < BOARDSIZE; row++){
			col--;//row and column increment each iteration (diagonal!)
			if(col < 0)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'Q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][row])){
					temp_move.piece = 'Q';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check NE
		col = i;
		for(int row = j+1; row < BOARDSIZE; row++){
			col++;//row and column increment each iteration (diagonal!)
			if(col >= BOARDSIZE)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'Q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][row])){
					temp_move.piece = 'Q';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check SE
		col = i;
		for(int row = j-1; row >= 0; row--){
			col++;//row and column increment each iteration (diagonal!)
			if(col >= BOARDSIZE)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'Q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][row])){
					temp_move.piece = 'Q';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check SW
		col = i;
		for(int row = j-1; row >= 0; row--){
			col--;//row and column increment each iteration (diagonal!)
			if(col < 0)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'Q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				white_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(islower(board[col][row])){
					temp_move.piece = 'Q';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					white_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
}

void position::find_blackQueenMoves(const int i, const int j){
	move_params temp_move;
	//Horizontal and Vertical movements
	//up
	for(int row = j+1; row < BOARDSIZE; row++){
	//-if empty, add move to list and continue
		if(board[i][row] == '#'){
			temp_move.piece = 'q';
			temp_move.col = i;
			temp_move.row = j;
			temp_move.new_col = i;
			temp_move.new_row = row;
			black_move_list.push_back(temp_move);
			continue;
		}else{
	//-else if occupied with a piece either:
	//--a. add capture to move list and break loop 
			if(isupper(board[i][row])){
				temp_move.piece = 'q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = i;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				break;
			}else{//(in the case it is a friendly piece)
	//--b. just break loop
				break;
			}
		}
	}
	//down
	for(int row = j-1; row >= 0; row--){
	//-if empty, add move to list and continue
		if(board[i][row] == '#'){
			temp_move.piece = 'q';
			temp_move.col = i;
			temp_move.row = j;
			temp_move.new_col = i;
			temp_move.new_row = row;
			black_move_list.push_back(temp_move);
			continue;
		}else{
	//-else if occupied with a piece either:
	//--a. add capture to move list and break loop 
			if(isupper(board[i][row])){
				temp_move.piece = 'q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = i;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				break;
			}else{//(in the case it is a friendly piece)
	//--b. just break loop
				break;
			}
		}
	}
	//left
	for(int col = i-1; col >= 0; col--){
	//-if empty, add move to list and continue
		if(board[col][j] == '#'){
			temp_move.piece = 'q';
			temp_move.col = i;
			temp_move.row = j;
			temp_move.new_col = col;
			temp_move.new_row = j;
			black_move_list.push_back(temp_move);
			continue;
		}else{
	//-else if occupied with a piece either:
	//--a. add capture to move list and break loop 
			if(isupper(board[col][j])){
				temp_move.piece = 'q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = j;
				black_move_list.push_back(temp_move);
				break;
			}else{//(in the case it is a friendly piece)
	//--b. just break loop
				break;
			}
		}
	}
	//right
	for(int col = i+1; col < BOARDSIZE; col++){
	//-if empty, add move to list and continue
		if(board[col][j] == '#'){
			temp_move.piece = 'q';
			temp_move.col = i;
			temp_move.row = j;
			temp_move.new_col = col;
			temp_move.new_row = j;
			black_move_list.push_back(temp_move);
			continue;
		}else{
	//-else if occupied with a piece either:
	//--a. add capture to move list and break loop 
			if(isupper(board[col][j])){
				temp_move.piece = 'q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = j;
				black_move_list.push_back(temp_move);
				break;
			}else{//(in the case it is a friendly piece)
	//--b. just break loop
				break;
			}
		}
	}
	
	//Diagonal movements
	//check NW
		int col = i;
		for(int row = j+1; row < BOARDSIZE; row++){
			col--;//row and column increment each iteration (diagonal!)
			if(col < 0)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][row])){
					temp_move.piece = 'q';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check NE
		col = i;
		for(int row = j+1; row < BOARDSIZE; row++){
			col++;//row and column increment each iteration (diagonal!)
			if(col >= BOARDSIZE)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][row])){
					temp_move.piece = 'q';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check SE
		col = i;
		for(int row = j-1; row >= 0; row--){
			col++;//row and column increment each iteration (diagonal!)
			if(col >= BOARDSIZE)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][row])){
					temp_move.piece = 'q';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
		//check SW
		col = i;
		for(int row = j-1; row >= 0; row--){
			col--;//row and column increment each iteration (diagonal!)
			if(col < 0)
				break;
		//-if empty, add move to list and continue
			if(board[col][row] == '#'){
				temp_move.piece = 'q';
				temp_move.col = i;
				temp_move.row = j;
				temp_move.new_col = col;
				temp_move.new_row = row;
				black_move_list.push_back(temp_move);
				continue;
			}else{
		//-else if occupied with a piece either:
		//--a. add capture to move list and break loop 
				if(isupper(board[col][row])){
					temp_move.piece = 'q';
					temp_move.col = i;
					temp_move.row = j;
					temp_move.new_col = col;
					temp_move.new_row = row;
					black_move_list.push_back(temp_move);
					break;
				}else{//(in the case it is a friendly piece)
		//--b. just break loop
					break;
				}
			}
		}
}






