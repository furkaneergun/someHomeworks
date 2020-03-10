#include <iostream>
#include "Board.h"
#pragma once
class Player {
	private:
		Board *board;	//board as a pointer as more than one Player objects can share a board
		char player_char;
	public:
		Player(Board *, char);
		bool play(int choice);
		bool wins();
};