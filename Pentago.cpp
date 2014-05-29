/*
	Patrick Sheehan
	CSCE 420 - A2 (Pentago)
	5 February 2014
*/

#include "Pentago.h"



vector<__int64> Pentago::newBoardStates(__int64 state, char player)
{ // return a vector of state identifiers for all possible child states
	Board* brd = new Board();
	brd->setBoard(state);
	vector<int> empties = brd->getOpenSlots();
	vector<__int64> boardStates;

	for (unsigned int i = 0; i < empties.size(); i++)
	{
		int spotID = empties.at(i);
		if (spotID <= 35 && spotID >= 0) 
		{
			for (char j = 'a'; j <= 'd'; j++)
			{
				brd->setBoard(state);
				brd->move(spotID, tolower(j), player);
				__int64 lowerStateID = brd->getStateID();
				if (brd->isWinner(player)) 
				{
					boardStates.clear();
					boardStates.push_back(lowerStateID);
					return boardStates;
				}

				brd->setBoard(state);
				brd->move(spotID, toupper(j), player);
				__int64 upperStateID = brd->getStateID();
				if (brd->isWinner(player)) 
				{
					boardStates.clear();
					boardStates.push_back(upperStateID);
					return boardStates;
				}
				
				boardStates.push_back(lowerStateID);
				boardStates.push_back(upperStateID);
			}
		}
	}
	return boardStates;
}
Board Pentago::getRandomBoard()
{ // function used early in development for testing board functionality
	// 64-bit random number??
	unsigned __int64 randomState = rand() * rand() * rand();
	//unsigned __int64 randomState2 = rand() * (unsigned __int64) 4.58;
	
	
	if (randomState > MAX_STATE_NUM) return getRandomBoard(); // error state
	
	Board b = Board();
	b.setBoard(randomState);
	/*cout << "state = " << randomState << endl;
	b.show();*/
	return b;
}
__int64 Pentago::minimax(int depth, bool maximize, char player, __int64 state)
{ // return the state that should be moved to
	// selects self if depth maximum is reached
	
//TODO: alpha-beta pruning

	vector<__int64> children = newBoardStates(state, player);


	// **base case: leaf or reached depth limitation
	if (depth == 0 || children.size() == 0) return state;	

	
	// **recursive case below
	int bestUtil = maximize ? INT_MIN : INT_MAX; // default best is (+/- infty)
	int childUtil;	// utility of a child node

	__int64 childState, grandchildState;
	__int64 bestState = children.at(0);
		
	for (unsigned int i = 1; i < children.size(); i++)
	{ // for every child state

		// state and utility value of this iteration's board
		childState = children.at(i); 
			
		// recursively compute child utility value
		grandchildState = minimax(depth - 1, !maximize, player, childState);
		childUtil = utility(grandchildState, player);


		if ((maximize && (childUtil > bestUtil)) || (!maximize && (childUtil < bestUtil)))
		{ // adjust best utility and best state values if necessary
			bestUtil = childUtil;
			bestState = childState;
		}
	}
	return bestState;
}

int Pentago::utility(__int64 state, char player)
{ // get a player's utility at a given state, using Board's functionality
	Board b = Board();
	b.setBoard(state);

	return b.utility(player);
}