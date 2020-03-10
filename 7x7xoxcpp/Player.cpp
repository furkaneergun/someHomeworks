#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(Board *ptr, char player_char) {
	//constructor
	this->board = ptr;
	this->player_char = player_char;
}

bool Player::play(int choice){
	if ((choice < 0) || (choice >= 7)) {
		//If the choice is not valid for 7x7 matrix
		cout << "This cell is not valid, invalid move, try again!" << endl;
		return false;
	}
	for (int i = 6; i >= 0; i--) {
		if (!(*board).isCellFull(i, choice)) {
			//The first empty cell from bottom to top is the cell which will be used
			(*board).append(i, choice, player_char);
			return true;
		}
	}
	//If choice is valid and all cells are full
	cout << "This cell is not empty, invalid move, try again!" << endl;
	return false;
	(*board).displayBoard();
}

bool Player::wins() {
	bool isWin = false;//Starts with initial condition false
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			isWin=(*board).Search(i, j, 0, player_char, 0);
			if (isWin) return isWin;	//If a cell has a solution either horizontal, vertical or diagonal isWin is empty and loop should be ended
		}
	}
	return isWin;
}