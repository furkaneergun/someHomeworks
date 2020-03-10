#include<iostream>
#include<string>
#include "Board.h"
#include "Player.h"
#pragma once
using namespace std;
/*****************
Furkan Ergün 24083
******************/
int main()
{
	Board myBoard = Board();


	   //Create your player objects based on your choice of approach to share an object.
	   //The parameters "..." are left for you to set.
	   Player player1 = Player(&myBoard, 'X'); 
	   Player player2 = Player(&myBoard, 'O');

	
	int col, turn = 0;
	bool continueGame = true;
	bool validMove = false;
	
	while(continueGame)
	{
		myBoard.displayBoard();
		if(turn == 0)
		{
			cout << "Player 1 turn: " << endl;
			cin >> col;
			validMove = player1.play(col);
			
			if(player1.wins())
			{
				continueGame = false;
				cout << "Player1 won the game!" << endl;
			}
		}
		else if(turn == 1)
		{
			cout << "Player 2 turn: " << endl;
			cin >> col;
			validMove = player2.play(col);
			
			if(player2.wins())
			{
				continueGame = false;
				cout << "Player2 won the game!" << endl;
			}
		}
		
		if(continueGame) {
			//If a valid move has been done, change the turn
			if(validMove) {
				turn = (turn + 1) % 2;		
			}
					
			if(myBoard.isBoardFull())
			{
				continueGame = false;
				cout << "No one won the game!" << endl;
			}
		}
	}	

	cout << "Game is over!" << endl;
	cout << "Final state of the board: " << endl;
	myBoard.displayBoard();
	system("pause"); //:)
	
	return 0;
}
