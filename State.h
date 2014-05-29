#ifndef STATE_H
#define STATE_H

#include "Board.h"

class State{
public:
	Board board;
	int utility;

	State(Board b) { board = b; utility = 0; }
	State(Board b, int util) {board = b; utility = util; }
};

#endif