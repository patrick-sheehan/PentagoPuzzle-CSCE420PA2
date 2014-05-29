/*
	Patrick Sheehan
	CSCE 420 - A2 (Pentago)
	5 February 2014
*/

#ifndef PENTAGO_H
#define PENTAGO_H

#include "State.h"

#include <iostream>
#include <ctime>
#include <iostream>

using namespace std;
static const __int64 MAX_STATE_NUM = 150094635296999112;
static const float MAX_SECONDS = .1f;

namespace Pentago 
{
	vector<__int64> newBoardStates(__int64 state, char player);
	Board getRandomBoard();
	__int64 minimax(int depth, bool isMax, char player, __int64 state);
	int utility(__int64 state, char player);
};

#endif