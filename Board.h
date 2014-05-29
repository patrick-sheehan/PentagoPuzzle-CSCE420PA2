/*
	Patrick Sheehan
	CSCE 420 - A2 (Pentago)
	5 February 2014
*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Board{

public:
	char myBoard[6][6]; // each location enumerated [0,35]
	
	int numMoves;
	static const int UID_ADJACENT_3 = 3;
	static const int UID_ADJACENT_4 = 4;
	static const int UID_ADJACENT_5 = 5;
	
	// constructors
	Board();
	Board(__int64 state);

	// mutators
	void rotate(char c);
	void move(int row, int col, char rotation, char player);
	void move(int spotID, char rotation, char player);
	void show();
	void setBoard(unsigned __int64 state);
	void clear();

	// accessors
	bool isEmpty(int row, int col);
	bool isWinner(char player);
	int getSpotID(int row, int col);
	int getRowFromID(int id);
	int getColFromID(int id);
	unsigned __int64 getStateID();
	
	bool horizontalConsecutive(int numSpots,int r, int c, int count, char player);
	bool verticalConsecutive(int numSpots, int r, int c, int count, char player);
	bool diagonalUpConsecutive(int numSpots, int r, int c, int count, char player);
	bool diagonalDownConsecutive(int numSpots, int r, int c, int count, char player);
	
	Board getBoard(unsigned __int64 state);

	vector<int> getOpenSlots();
	vector<__int64>* getWinningStates(char player);
	
	int utility(char player);
	int utility(int r, int c, int count, char player, int UID);
};

#endif