/*
	Patrick Sheehan
	CSCE 420 - A2 (Pentago)
	5 February 2014
*/

#include "Pentago.h"

using namespace Pentago;

void singlePlayerGame(Board* b);
void computerMove(Board* b, int depth, char compPlayer);
void twoComputerGame(Board* b);

int main(int argc, char* argv[])
{
	srand(time_t(NULL));

	Board* b = new Board();
	clock_t begin = clock();
	
	singlePlayerGame(b);
	//twoComputerGame(b);	

	
	cout << "Total program running time: " << float(clock() - begin) / CLOCKS_PER_SEC << " seconds\n";
	return 0;
}
void singlePlayerGame(Board* b)
{ // start a single player (human against computer)
	cout << "Enter your move in the format - <row> <col> <cell-rot-dir>\n\nStarting board:\n";
	b->clear();
	b->show();

	int depth = 1;
	int numMoves = 0;
	int row, col;
	char cell;
	clock_t begin;

	while (true)
	{
		cout << "Human's turn (Player W): ";
		cin >> row;
		cin >> col;
		cin >> cell;

		if (row <= 6 && row > 0 && col <= 6 && col > 0 && b->isEmpty(row, col) && string("ABCDabcd").find(cell) != string::npos)
		{
			// make human's move if valid
			b->move(row, col, cell, 'W');	
			if (b->isWinner('W')) { cout << "Player 'W' / Human wins!\n\n\n"; break; }
			b->show();

			// make computer's move and time it
			cout << "\nMy move (Player B), depth = " << depth << ", time = ";
			begin = clock();
			computerMove(b, depth, 'B');
			cout << float(clock() - begin) / CLOCKS_PER_SEC << " seconds\n";
			if (b->isWinner('B')) { cout << "I, the computer, beat you!\n\n\n"; break; }
			b->show();

			if (++numMoves > 5) depth = 2;

		}
		else cout << "Invalid input. Try again\n";
	}

	b->show();
	cout << "Final board. Play again? (y/n): \n";
	cin >> cell;
	if (cell == 'y') singlePlayerGame(b);
}
void twoComputerGame(Board* b)
{ // start a game where two computers play against each other
	clock_t begin, end;
	int depth = 1;
	int numMoves = 0;
	while (true)
	{
		// make W computer's move and time it
		begin = clock();
		computerMove(b, depth, 'W');
		end = clock() - begin;
		if (b->isWinner('W')) { cout << "White computer won\n\n\n"; break; }
		b->show();
		cout << "White's move, depth = " << depth << ", time = " << float(clock() - begin) / CLOCKS_PER_SEC << " seconds\n\n";


		// make B computer's move and time it
		begin = clock();
		computerMove(b, depth, 'B');
		end = clock() - begin;
		if (b->isWinner('B')) { cout << "Black computer won\n\n\n"; break; }
		b->show();
		cout << "Black's move, depth = " << depth << ", time = " << float(clock() - begin) / CLOCKS_PER_SEC << " seconds\n\n";
		

		if (++numMoves > 5) depth = 2;
	}

	cout << "Final board:\n";
	b->show();
}
void computerMove(Board* b, int depth, char compPlayer)
{ // make a move on the board by the computer 
	__int64 currentState = b->getStateID();
	__int64 desiredState = minimax(depth, true, compPlayer, currentState);
	b->setBoard(desiredState);
}