//evaluate.h

//pass position by reference and calculate piece values
//for each side. 

//This is the most basic evaluation.

//For human like evaluation, add logic that values dynamic
//advantage. To do this:
//1. compare relative rate of development
// if less than 20 moves have been played based on how many minor pieces
//are still on the back rank.
//2. place value on having control of the center by determining first
// whether any pawns are in the middle four squares.
//3. proximity to king
//4. forced moves: (valuing this would promote you're forced moves and prevent his)
//		a. look at possible moves for a knight (as an example)
//		b. is that square defended? if so do you outmatch your opponent there?

//***Remember, just negate the white evaluation score for black's evaluation
//position.h

//specification file
//chess engine 
//position.h
#ifndef EVALUATE_H
#define EVALUATE_H

#include "position.h"

class evaluate{
	public:
		evaluate();//default constructor
		double evaluate_position(position&,bool);
		bool   whiteCheck(const position&);
		bool   blackCheck(const position&);
	private:
		//int piece_points;
		//int center_points;			->There doesn't seem to be much reason at this time
		//int pawn_structure_points;	->to retain evaluation point memory since each variable
		//int king_safety_points;		->will have to be set to zero again each evaluation.
};

#endif

