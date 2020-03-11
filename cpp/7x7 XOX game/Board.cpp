#include "Board.h"
using namespace std;

Board::Board() {
	//Default constructor which initializes an empty board
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			board[i][j] = '_';
		}
	}
}

void Board::displayBoard() {
	//Writing every element of the board
	cout << "Board:" << endl;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

bool Board::isBoardFull() {
	//If there is any empty cell this function returns false, otherwise it returns true
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (board[i][j] != 'X' && board[i][j] != 'O') { return false; }
		}
	}
	return true;
}

bool Board::isCellFull(int row, int column) {
	//Check if the cell is empty(_) or not
	if (board[row][column] != '_') return true;
	return false;
}

void Board::append(int row, int column, char choice) {
	//Changes the specific row and column of the board
	board[row][column] = choice;
}

bool Board::searchHelper(int i, int j) {
	//Checks if the coordinat valid in the board system (7x7)
	if (i < 0 || i>6) return false;
	if (j < 0 || j>6) return false;
	return true;
}

bool Board::Search(int row, int column, int attempt, char c, int type) {
	/*
	This function takes starting row column and the char which is searching for as a
	parameter and makes a vertical, horizontal, to the top left diagonal and to the bottom
	left diagonal search with recursion. If any of the searches finds the 4 char repeatedly
	it changes the static isFound and function call ends. Also in the first search it should
	be noted that through switch statement every type of search is called and then only the
	same type of search is called.
	*/
	static int isFound = false;
	if (searchHelper(row, column) && !isFound) {	//While there is no solution yet and given coordinates are valid
		if (board[row][column] == c) {
			attempt++;
			if (attempt == 4) {
				//If 4 in a row, then the recursion should be ended
				isFound = true;
				return isFound;
			}
			switch (type) {
			//Unless the first search only repeat the last search direction
			case 1:
				Search(row - 1, column, attempt, c, type);
				break;
			case 2:
				Search(row, column + 1, attempt, c, type);
				break;
			case 3:
				Search(row - 1, column + 1, attempt, c, type);
				break;
			case 4:
				Search(row + 1, column + 1, attempt, c, type);
				break;
			default:
				//For the first case, invoking every recursion
				Search(row - 1, column, attempt, c, 1);
				Search(row, column + 1, attempt, c, 2);
				Search(row - 1, column + 1, attempt, c, 3);
				Search(row + 1, column + 1, attempt, c, 4);
			}
		}
	}
	return isFound;
}

