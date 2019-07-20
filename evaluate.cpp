//evaluate.cpp
//implementation file

#include "evaluate.h"
#include <iostream>
#include <cctype>
//#include <cctype> // for isupper and islower ('#' is false for both)

const int BOARDSIZE = 8;

evaluate::evaluate(){
	//do nothing...
}

bool evaluate::whiteCheck(const position& pos)
{
	int king_column;
	int king_row;
	//first find the king
	//(note: consider passing king location via argument instead)
	for(int i = 0; i < BOARDSIZE; i++){
		for(int j = 0; j < BOARDSIZE; j++){
			if(pos.board[i][j] == 'K'){
				king_column = i;
				king_row = j;
			}	
		}	
	}	
	
	const int i = king_column;
	const int j = king_row;
	
	//check for black knights
	//--knight position 1
	if(pos.board[i-2][j+1] == 'n' && i-2 >= 0 && j+1 < BOARDSIZE){
		return true;	
	}
	//--knight position 2
	if(pos.board[i-1][j+2] == 'n' && i-1 >= 0 && j+2 < BOARDSIZE){
		return true;	
	}
	//--knight position 3
	if(pos.board[i+1][j+2] == 'n' && i+1 < BOARDSIZE && j+2 < BOARDSIZE){
		return true;	
	}
	//--knight position 4
	if(pos.board[i+2][j+1] == 'n' && i+2 < BOARDSIZE && j+1 < BOARDSIZE){
		return true;	
	}
	//--knight position 5
	if(pos.board[i+2][j-1] == 'n' && i+2 < BOARDSIZE && j-1 >= 0){
		return true;	
	}
	//--knight position 6
	if(pos.board[i+1][j-2] == 'n' && i+1 < BOARDSIZE && j-2 >= 0){
		return true;	
	}
	//--knight position 7
	if(pos.board[i-1][j-2] == 'n' && i-1 >= 0 && j-2 >= 0){
		return true;	
	}
	//--knight position 8
	if(pos.board[i-2][j-1] == 'n' && i-2 >= 0 && j-1 >= 0){
		return true;	
	}
	
	//check for diagonal (queens or bishops or pawns)
	//black pawns
	if(pos.board[i-1][j+1] == 'p' || pos.board[i+1][j+1] == 'p')
		return true;
	
	//--upper left diagonal
	//--upper left diagonal
	//--upper left diagonal
	int temp_i = i-1;
	int temp_j = j+1;
	while(temp_i >= 0 && temp_j < BOARDSIZE){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			//std::cout << "code 2\n";
			temp_i--;
			temp_j++;		
		}
		//if white piece or non queen/bishop black piece, break
		else if(isupper(pos.board[temp_i][temp_j]) || 
				(islower(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'q' && pos.board[temp_i][temp_j] != 'b')){
			//std::cout << "code 3\n";
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'q' || pos.board[temp_i][temp_j] == 'b'){
			//std::cout << "code 4\n";
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN WHITECHECK EVAL\n";
		}
	}
	
	//--upper right diagonal
	//--upper right diagonal
	//--upper right diagonal
	temp_i = i+1;
	temp_j = j+1;
	while(temp_i < BOARDSIZE && temp_j < BOARDSIZE){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			//std::cout << "code 2\n";
			temp_i++;
			temp_j++;		
		}
		//if white piece or non queen/bishop black piece, break
		else if(isupper(pos.board[temp_i][temp_j]) || 
				(islower(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'q' && pos.board[temp_i][temp_j] != 'b')){
			//std::cout << "code 3\n";
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'q' || pos.board[temp_i][temp_j] == 'b'){
			//std::cout << "code 4\n";
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN WHITECHECK EVAL\n";
		}
	}
	
	//--lower right diagonal
	//--lower right diagonal
	//--lower right diagonal
	temp_i = i+1;
	temp_j = j-1;
	while(temp_i < BOARDSIZE && temp_j >= 0){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			//std::cout << "code 2\n";
			temp_i++;
			temp_j--;		
		}
		//if white piece or non queen/bishop black piece, break
		else if(isupper(pos.board[temp_i][temp_j]) || 
				(islower(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'q' && pos.board[temp_i][temp_j] != 'b')){
			//std::cout << "code 3\n";
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'q' || pos.board[temp_i][temp_j] == 'b'){
			//std::cout << "code 4\n";
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN WHITECHECK EVAL\n";
		}
	}
	
	//--lower left diagonal
	//--lower left diagonal
	//--lower left diagonal
	temp_i = i-1;
	temp_j = j-1;
	while(temp_i >= 0 && temp_j >= 0){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			//std::cout << "code 2\n";
			temp_i--;
			temp_j--;		
		}
		//if white piece or non queen/bishop black piece, break
		else if(isupper(pos.board[temp_i][temp_j]) || 
				(islower(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'q' && pos.board[temp_i][temp_j] != 'b')){
			//std::cout << "code 3\n";
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'q' || pos.board[temp_i][temp_j] == 'b'){
			//std::cout << "code 4\n";
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN WHITECHECK EVAL\n";
		}
	}
	
	//check for horizontal and vertical checks
	//(queens or rooks)
	
	//--left horizontal
	//--left horizontal
	//--left horizontal
	temp_i = i-1;
	temp_j = j;
	while(temp_i >= 0){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			temp_i--;		
		}
		//if white piece or non queen/rook black piece, break
		else if(isupper(pos.board[temp_i][temp_j]) || 
				(islower(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'q' && pos.board[temp_i][temp_j] != 'r')){
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'q' || pos.board[temp_i][temp_j] == 'r'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN WHITECHECK EVAL\n";
		}
	}
	
	//--right horizontal
	//--right horizontal
	//--right horizontal
	temp_i = i+1;
	temp_j = j;
	while(temp_i < BOARDSIZE){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			temp_i++;		
		}
		//if white piece or non queen/rook black piece, break
		else if(isupper(pos.board[temp_i][temp_j]) || 
				(islower(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'q' && pos.board[temp_i][temp_j] != 'r')){
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'q' || pos.board[temp_i][temp_j] == 'r'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN WHITECHECK EVAL\n";
		}
	}
	
	//--vertical up
	//--vertical up
	//--vertical up
	temp_i = i;
	temp_j = j+1;
	while(temp_j < BOARDSIZE){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			temp_j++;		
		}
		//if white piece or non queen/rook black piece, break
		else if(isupper(pos.board[temp_i][temp_j]) || 
				(islower(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'q' && pos.board[temp_i][temp_j] != 'r')){
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'q' || pos.board[temp_i][temp_j] == 'r'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN WHITECHECK EVAL\n";
		}
	}
	
	//--vertical down
	//--vertical down
	//--vertical down
	temp_i = i;
	temp_j = j-1;
	while(temp_j >= 0){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			temp_j--;		
		}
		//if white piece or non queen/rook black piece, break
		else if(isupper(pos.board[temp_i][temp_j]) || 
				(islower(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'q' && pos.board[temp_i][temp_j] != 'r')){
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'q' || pos.board[temp_i][temp_j] == 'r'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN WHITECHECK EVAL\n";
		}
	}
	
	//TO ENSURE THAT THE KING DOESN'T MOVE ILLEGALLY, WE MUST INCLUDE
	//A CHECK FOR THE OTHER KING IN THE KING'S VICINITY (SURROUNDING SQUARES)
	
	//king square one
	if(pos.board[i+1][j] == 'k' && i+1 < BOARDSIZE){
		return true;
	}
	//king square two
	if(pos.board[i+1][j+1] == 'k' && i+1 < BOARDSIZE && j+1 < BOARDSIZE){
		return true;
	}
	//king square three
	if(pos.board[i][j+1] == 'k' && j+1 < BOARDSIZE){
		return true;
	}
	//king square four
	if(pos.board[i-1][j+1] == 'k' && i-1 >= 0 && j+1 < BOARDSIZE){
		return true;
	}
	//king square five
	if(pos.board[i-1][j] == 'k' && i-1 >= 0){
		return true;
	}
	//king square six
	if(pos.board[i-1][j-1] == 'k' && i-1 >= 0 && j-1 >= 0){
		return true;
	}
	//king square seven
	if(pos.board[i][j-1] == 'k' && j-1 >= 0){
		return true;
	}
	//king square eight
	if(pos.board[i+1][j-1] == 'k' && i+1 < BOARDSIZE && j-1 >= 0){
		//std::cout << "debug8\n";MUST CHECK BOUNDS!! (NOT A RUBIK'S CUBE)
		return true;
	}
	
	return false; //control reaches this statement if all if statements fail
}

bool evaluate::blackCheck(const position& pos)
{
	int king_column;
	int king_row;
	//first find the king
	//(note: consider passing king location via argument instead)
	for(int i = 0; i < BOARDSIZE; i++){
		for(int j = 0; j < BOARDSIZE; j++){
			if(pos.board[i][j] == 'k'){
				king_column = i;
				king_row = j;
			}	
		}	
	}	
	
	const int i = king_column;
	const int j = king_row;
	
	//check for black knights
	//--knight position 1
	if(pos.board[i-2][j+1] == 'N' && i-2 >= 0 && j+1 < BOARDSIZE){
		return true;	
	}
	//--knight position 2
	if(pos.board[i-1][j+2] == 'N' && i-1 >= 0 && j+2 < BOARDSIZE){
		return true;	
	}
	//--knight position 3
	if(pos.board[i+1][j+2] == 'N' && i+1 < BOARDSIZE && j+2 < BOARDSIZE){
		return true;	
	}
	//--knight position 4
	if(pos.board[i+2][j+1] == 'N' && i+2 < BOARDSIZE && j+1 < BOARDSIZE){
		return true;	
	}
	//--knight position 5
	if(pos.board[i+2][j-1] == 'N' && i+2 < BOARDSIZE && j-1 >= 0){
		return true;	
	}
	//--knight position 6
	if(pos.board[i+1][j-2] == 'N' && i+1 < BOARDSIZE && j-2 >= 0){
		return true;	
	}
	//--knight position 7
	if(pos.board[i-1][j-2] == 'N' && i-1 >= 0 && j-2 >= 0){
		return true;	
	}
	//--knight position 8
	if(pos.board[i-2][j-1] == 'N' && i-2 >= 0 && j-1 >= 0){
		return true;	
	}
	
	//check for diagonal (queens or bishops or pawns)
	//black pawns
	if(pos.board[i-1][j-1] == 'P' || pos.board[i+1][j-1] == 'P')
		return true;
	
	//--upper left diagonal
	//--upper left diagonal
	//--upper left diagonal
	int temp_i = i-1;
	int temp_j = j+1;
	while(temp_i >= 0 && temp_j < BOARDSIZE){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			//std::cout << "code 2\n";
			temp_i--;
			temp_j++;		
		}
		//if black piece or non queen/bishop white piece, break
		else if(islower(pos.board[temp_i][temp_j]) || 
				(isupper(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'Q' && pos.board[temp_i][temp_j] != 'B')){
			//std::cout << "code 3\n";
			break;
		}
		//if white q or b, return true
		else if(pos.board[temp_i][temp_j] == 'Q' || pos.board[temp_i][temp_j] == 'B'){
			//std::cout << "code 4\n";
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN BLACKCHECK EVAL\n";
		}
	}
	
	//--upper right diagonal
	//--upper right diagonal
	//--upper right diagonal
	temp_i = i+1;
	temp_j = j+1;
	while(temp_i < BOARDSIZE && temp_j < BOARDSIZE){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			//std::cout << "code 2\n";
			temp_i++;
			temp_j++;		
		}
		//if white piece or non queen/bishop black piece, break
		else if(islower(pos.board[temp_i][temp_j]) || 
				(isupper(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'Q' && pos.board[temp_i][temp_j] != 'B')){
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'Q' || pos.board[temp_i][temp_j] == 'B'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN BLACKCHECK EVAL\n";
		}
	}
	
	//--lower right diagonal
	//--lower right diagonal
	//--lower right diagonal
	temp_i = i+1;
	temp_j = j-1;
	while(temp_i < BOARDSIZE && temp_j >= 0){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			//std::cout << "code 2\n";
			temp_i++;
			temp_j--;		
		}
		//if black piece or non queen/bishop white piece, break
		else if(islower(pos.board[temp_i][temp_j]) || 
				(isupper(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'Q' && pos.board[temp_i][temp_j] != 'B')){
			break;
		}
		//if white Q or B, return true
		else if(pos.board[temp_i][temp_j] == 'Q' || pos.board[temp_i][temp_j] == 'B'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN BlackCHECK EVAL\n";
		}
	}
	
	//--lower left diagonal
	//--lower left diagonal
	//--lower left diagonal
	temp_i = i-1;
	temp_j = j-1;
	while(temp_i >= 0 && temp_j >= 0){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			//std::cout << "code 2\n";
			temp_i--;
			temp_j--;		
		}
		//if black piece or non queen/bishop white piece, break
		else if(islower(pos.board[temp_i][temp_j]) || 
				(isupper(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'Q' && pos.board[temp_i][temp_j] != 'B')){
			//std::cout << "code 3\n";
			break;
		}
		//if white Q or B, return true
		else if(pos.board[temp_i][temp_j] == 'Q' || pos.board[temp_i][temp_j] == 'B'){
			//std::cout << "code 4\n";
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN blackCHECK EVAL\n";
		}
	}
	
	//check for horizontal and vertical checks
	//(queens or rooks)
	
	//--left horizontal
	//--left horizontal
	//--left horizontal
	temp_i = i-1;
	temp_j = j;
	while(temp_i >= 0){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			temp_i--;		
		}
		//if black piece or non queen/rook white piece, break
		else if(islower(pos.board[temp_i][temp_j]) || 
				(isupper(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'Q' && pos.board[temp_i][temp_j] != 'R')){
			break;
		}
		//if white q or b, return true
		else if(pos.board[temp_i][temp_j] == 'Q' || pos.board[temp_i][temp_j] == 'R'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN blackCHECK EVAL\n";
		}
	}
	
	//--right horizontal
	//--right horizontal
	//--right horizontal
	temp_i = i+1;
	temp_j = j;
	while(temp_i < BOARDSIZE){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			temp_i++;		
		}
		//if black piece or non queen/rook white piece, break
		else if(islower(pos.board[temp_i][temp_j]) || 
				(isupper(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'Q' && pos.board[temp_i][temp_j] != 'R')){
			break;
		}
		//if white q or b, return true
		else if(pos.board[temp_i][temp_j] == 'Q' || pos.board[temp_i][temp_j] == 'R'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN blackCHECK EVAL\n";
		}
	}
	
	//--vertical up
	//--vertical up
	//--vertical up
	temp_i = i;
	temp_j = j+1;
	while(temp_j < BOARDSIZE){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			temp_j++;		
		}
		//if black piece or non queen/rook black piece, break
		else if(islower(pos.board[temp_i][temp_j]) || 
				(isupper(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'Q' && pos.board[temp_i][temp_j] != 'R')){
			break;
		}
		//if black q or b, return true
		else if(pos.board[temp_i][temp_j] == 'Q' || pos.board[temp_i][temp_j] == 'R'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN blackCHECK EVAL\n";
		}
	}
	
	//--vertical down
	//--vertical down
	//--vertical down
	temp_i = i;
	temp_j = j-1;
	while(temp_j >= 0){
		//if space, increment/decrement and continue
		if(pos.board[temp_i][temp_j] == '#'){
			temp_j--;		
		}
		//if black piece or non queen/rook white piece, break
		else if(islower(pos.board[temp_i][temp_j]) || 
				(isupper(pos.board[temp_i][temp_j]) && pos.board[temp_i][temp_j] != 'Q' && pos.board[temp_i][temp_j] != 'R')){
			break;
		}
		//if white q or b, return true
		else if(pos.board[temp_i][temp_j] == 'Q' || pos.board[temp_i][temp_j] == 'R'){
			return true;
		}
		else{
			std::cout << "ERROR: UNKNOWN PIECE IN blackCHECK EVAL\n";
		}
	}
	
	//TO ENSURE THAT THE KING DOESN'T MOVE ILLEGALLY, WE MUST INCLUDE
	//A CHECK FOR THE OTHER KING IN THE KING'S VICINITY (SURROUNDING SQUARES)
	
	//king square one
	if(pos.board[i+1][j] == 'K' && i+1 < BOARDSIZE){
		return true;
	}
	//king square two
	if(pos.board[i+1][j+1] == 'K' && i+1 < BOARDSIZE && j+1 < BOARDSIZE){
		return true;
	}
	//king square three
	if(pos.board[i][j+1] == 'K' && j+1 < BOARDSIZE){
		return true;
	}
	//king square four
	if(pos.board[i-1][j+1] == 'K' && i-1 >= 0 && j+1 < BOARDSIZE){
		return true;
	}
	//king square five
	if(pos.board[i-1][j] == 'K' && i-1 >= 0){
		return true;
	}
	//king square six
	if(pos.board[i-1][j-1] == 'K' && i-1 >= 0 && j-1 >= 0){
		return true;
	}
	//king square seven
	if(pos.board[i][j-1] == 'K' && j-1 >= 0){
		return true;
	}
	//king square eight
	if(pos.board[i+1][j-1] == 'K' && i+1 < BOARDSIZE && j-1 >= 0){
		//std::cout << "debug8\n";MUST CHECK BOUNDS!! (NOT A RUBIK'S CUBE)
		return true;
	}
	
	return false; //control reaches this statement if all if statements fail
}

double evaluate::evaluate_position(position& board_pos, bool white)
{
	double piece_points = 0;
	double center_points = 0;		
	double pawn_structure_points = 0;	
	double king_safety_points = 0;
	double development_points = 0;	
	
	bool king_flag_white = false;//set this to TRUE when king is found.
	bool king_flag_black = false;//and if not found detract 'infinite' points
	double score = 0;
	
	//iterate through board position and determine basic material score:
	for(int i = 0; i < BOARDSIZE; i++){
		for(int j = 0; j < BOARDSIZE; j++){
			switch(board_pos.board[i][j]){
				case '#':
					break;
				case 'P':
					piece_points++;
					break;
				case 'R':
					piece_points += 5;
					break;
				case 'N':
					piece_points += 3;
					break;
				case 'B':
					piece_points += 3;
					break;
				case 'Q':
					piece_points += 9;
					break;
				case 'K':
					king_flag_white = true;
					break;
				case 'p':
					piece_points--;
					break;
				case 'r':
					piece_points -= 5;
					break;
				case 'n':
					piece_points -= 3;
					break;
				case 'b':
					piece_points -= 3;
					break;
				case 'q':
					piece_points -= 9;
					break;
				case 'k':
					king_flag_black = true;
					break;
			}
		}
	}
	
	//Value center occupation
	//For a given side, are they occupying the center two squares closest to them?
	if(board_pos.board[3][3] == 'P')
		center_points += 0.2;
	if(board_pos.board[4][3] == 'p')
		center_points -= 0.2;
	if(board_pos.board[3][3] == 'P')
		center_points += 0.2;
	if(board_pos.board[3][3] == 'p')
		center_points -= 0.2;
	
	//Value development:
	//For a given side, have they developed all of their MINOR pieces?
	for(int i = 0; i < BOARDSIZE; i++){
		if(board_pos.board[i][0] == 'B' || board_pos.board[i][0] == 'N')  //if white minor pieces are still on
			development_points -= 0.2;    							      //the first rank, then decrement the score
		if(board_pos.board[i][7] == 'b' || board_pos.board[i][7] == 'n')  //(and vice versa for black).
			development_points += 0.2;
	}	
	
	//**add** Rooks on open or semi-open files
	
	//**add** pawn structure
	
	//**add** dynamic advantage
	
	//**add** king safety
	
	//add or subtract 1 million for king loss (in lieu of check and checkmate overrides for now)
	if(!king_flag_white){
		score -= 1000000;//detracting one million seems sufficient for now.
						 //As sunfish.py does- the 'checkmate' score must be more than
						 //the max material which would be 9 queens + all minor pieces
						 // which is 9*9 + 2*5 + 4*3 = 81+10+12=102. (Yes, black would have to have
						 // one piece that would detract from the piece points but nonetheless, this
						 // shows that 1 million is ~infinity for any evaluation). 	
		//std::cout << "score -= 1000000;//king flag white called\n\n";//DEBUG 
	}
	
	if(!king_flag_black){
		score += 1000000;
		//std::cout << "score += 1000000;//king flag black called\n\n";//DEBUG 
	}
	
	//aggregate scores:
	score += piece_points + center_points + development_points + pawn_structure_points + king_safety_points;
		//'+=' not '=' (glitch2!!)
	
	//return score if white eval, and negative score if black eval:
	if(white){
		return score;
	}
	else{
		double ret_val = (score * -1);
		//std::cout << "returning for black score of: " << ret_val << std::endl;
		return ret_val;
	}
}


