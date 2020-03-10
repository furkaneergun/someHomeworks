#include <iostream>
#pragma once
class Board {
	private:
		char board[7][7];	//The game table
		bool searchHelper(int, int);  //This function is only for self search purposes. Not related with other classes

	public:
		//These functions can be used by another classes
		void displayBoard();
		bool isBoardFull();
		bool isCellFull(int, int);
		void append(int, int, char);
		Board(void);	//Default constructor
		bool Board::Search(int, int, int, char, int);

};
