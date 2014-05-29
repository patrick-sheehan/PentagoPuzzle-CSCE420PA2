/*
	Patrick Sheehan
	CSCE 420 - A2 (Pentago)
	5 February 2014
*/

#include "Board.h"

Board::Board()
{ // Note the array representation of the board is zero-indexed,
	// however, function input for row/col are in the range [1,6] inclusive
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			myBoard[i][j] = 'O'; // board is empty
}
Board::Board(__int64 state)
{ // construct a board that represents the provided state ID
	Board();
	setBoard(state);
}
void Board::rotate(char c)
{ // rotate a quadrant: lowercase => clockwise, uppercase => counterclockwise
	int dr = 0, dc = 0; // row and column offset
	switch(tolower(c)){
		case 'a': break;
		case 'b': dc = 3; break;
		case 'c': dr = 3; break;
		case 'd': dr = 3; dc = 3; break;
		default: cout << "Invalid rotation\n"; return;
	}

	char tempVal11 = myBoard[dr][dc];
	char tempVal12 = myBoard[dr][dc+1];
	char tempVal13 = myBoard[dr][dc+2];

	char tempVal21 = myBoard[dr+1][dc];
	char tempVal23 = myBoard[dr+1][dc+2];

	char tempVal31 = myBoard[dr+2][dc];
	char tempVal32 = myBoard[dr+2][dc+1];
	char tempVal33 = myBoard[dr+2][dc+2];
	
	
	if (islower(c)){ // clockwise
		myBoard[dr][dc] = tempVal31;
		myBoard[dr][dc+1] = tempVal21;
		myBoard[dr][dc+2] = tempVal11;
		myBoard[dr+1][dc] = tempVal32;
		myBoard[dr+1][dc+2] = tempVal12;
		myBoard[dr+2][dc] = tempVal33;
		myBoard[dr+2][dc+1] = tempVal23;
		myBoard[dr+2][dc+2] = tempVal13;	
	}
	else if (isupper(c)) { // counter-clockwise
		myBoard[dr][dc] = tempVal13;
		myBoard[dr][dc+1] = tempVal23;
		myBoard[dr][dc+2] = tempVal33;
		myBoard[dr+1][dc] = tempVal12;
		myBoard[dr+1][dc+2] = tempVal32;
		myBoard[dr+2][dc] = tempVal11;
		myBoard[dr+2][dc+1] = tempVal21;
		myBoard[dr+2][dc+2] = tempVal31;
	}
}
void Board::move(int row, int col, char rotation, char player)
{ // move a player's marble to a slot identified by a row<-[1,6], and col<-[1,6], then rotate
	
	if (isEmpty(row, col))
	{ // if the slot is empty
		myBoard[row-1][col-1] = toupper(player);
		rotate(rotation);
	}
	else
		cout << "Invalid placement, slot is already taken\n";
}
void Board::move(int spotID, char rotation, char player)
{ // move a player's marble to the spotID, then rotate
	move(getRowFromID(spotID) + 1, getColFromID(spotID) + 1, rotation, player);
}
void Board::show()
{ // display the board to standard output
	int i,j;
	cout << "---------------\n";
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++) cout << myBoard[i][j] << " ";
		cout << "| ";
		for ( ; j < 6; j++) cout << myBoard[i][j] << " ";
		cout << "| \n";
	}
	cout << "---------------\n";
	for ( ; i < 6; i++){
		for (j = 0; j < 3; j++) cout << myBoard[i][j] << " ";
		cout << "| ";
		for ( ; j < 6; j++) cout << myBoard[i][j] << " ";
		cout << "| \n";
	}
	cout << "---------------\n\n";
}
bool Board::isEmpty(int row, int col)
{ // return true if a given spot is empty 
	return myBoard[row - 1][col - 1] == 'O';
}
bool Board::isWinner(char player)
{ // function for user to invoke recursive isWinner method with default parameters
// TODO: just check the 28 winning combinations
	for (int r = 0; r < 6; r++)
		if (horizontalConsecutive(5,r,0,0,player)) return true;

	for (int c = 0; c < 6; c++)
		if (verticalConsecutive(5,0,c,0,player)) return true;

	if (diagonalUpConsecutive(5,4,0,0,player)) return true;
	if (diagonalUpConsecutive(5,5,0,0,player)) return true;
	if (diagonalUpConsecutive(5,5,1,0,player)) return true;

	if (diagonalDownConsecutive(5,0,0,0,player)) return true;
	if (diagonalDownConsecutive(5,0,1,0,player)) return true;
	if (diagonalDownConsecutive(5,1,0,0,player)) return true;

	return false;
}
bool Board::horizontalConsecutive(int numSpots, int r, int c, int count, char player)
{ // return true if there are numSpots of horizontally consecutive marbles
  // used to evaluate wins and the utility function
	if (count == numSpots) return true;
	if (r > 5 || c > 5) return false;
	
	int newCount = myBoard[r][c] == toupper(player) ? ++count : 0;
	return horizontalConsecutive(numSpots, r, c+1, newCount, player);
}
bool Board::verticalConsecutive(int numSpots, int r, int c, int count, char player)
{ // return true if there are numSpots of vertically consecutive marbles
  // used to evaluate wins and the utility function
	if (count == numSpots) return true;
	if (r > 5 || c > 5) return false;
	
	int newCount = myBoard[r][c] == toupper(player) ? ++count : 0;
	return verticalConsecutive(numSpots, r+1, c, newCount, player);
}
bool Board::diagonalUpConsecutive(int numSpots, int r, int c, int count, char player)
{ // return true if there are numSpots of diagonally (bottom left->top right) consecutive marbles
  // used to evaluate wins and the utility function
	if (count == numSpots) return true;
	if (r > 5 || c > 5 || r < 0) return false;
	
	int newCount = myBoard[r][c] == toupper(player) ? ++count : 0;
	return diagonalUpConsecutive(numSpots, r-1, c+1, newCount, player);
}
bool Board::diagonalDownConsecutive(int numSpots, int r, int c, int count, char player)
{ // return true if there are numSpots of diagonally (top left->bottom right) consecutive marbles
  // used to evaluate wins and the utility function
	if (count == numSpots) return true;
	if (r > 5 || c > 5 || r < 0) return false;
	
	int newCount = myBoard[r][c] == toupper(player) ? ++count : 0;
	return diagonalDownConsecutive(numSpots, r+1, c+1, newCount, player);
}

int Board::getSpotID(int row, int col)
{ // ids in range [0,35]
	return 6 * row + col;
}
int Board::getRowFromID(int id)
{ // returns the row (zero-based)
	return id / 6;
}
int Board::getColFromID(int id)
{ // returns the col (zero-based)
	return id % 6;
}
unsigned __int64 Board::getStateID()
{ // return unique ID for the board's state. 
	// The number of possible (not probable) layouts is 3^36 < [2^64; size of 64-bit int]
	unsigned __int64 state = 0;
	
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++){
			int multiplier;
			switch(myBoard[i][j]){
				case 'B': multiplier = 2; break;
				case 'W': multiplier = 1; break;
				default : multiplier = 0; break;
			}
			state += multiplier * (__int64)pow(3, getSpotID(i,j));
		}
		
	return state;
}
vector<int> Board::getOpenSlots()
{ // return vector of ints identifying IDs of open slots
	vector<int> empties;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			if (myBoard[i][j] == 'O')
				empties.push_back(getSpotID(i, j));

	return empties;
}
void Board::setBoard(unsigned __int64 state)
{ // set the board according to the state id using a '3-bit number' scheme
	unsigned __int64 _state = state;

	for (int i = 5; i >= 0; i--)
		for (int j = 5; j >= 0; j--){
			unsigned __int64 exp = (unsigned __int64)pow(3, getSpotID(i, j)); // 3^(spotID)
			if (2 * exp <= _state) {
				myBoard[i][j] = 'B';
				_state -= 2 * exp;
			}else if (exp <= _state){
				myBoard[i][j] = 'W';
				_state -= exp;
			}else myBoard[i][j] = 'O';
		}
}
void Board::clear()
{ // clear contents of the board
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			myBoard[i][j] = 'O'; // board is empty
}
Board Board::getBoard(unsigned __int64 state)
{ // set the board according to the state id using a '3-bit number' scheme
	unsigned __int64 _state = state;
	Board b = Board();

	for (int i = 5; i >= 0; i--)
		for (int j = 5; j >= 0; j--){
			unsigned __int64 exp = (unsigned __int64)pow(3, getSpotID(i, j)); // 3^(spotID)
			if (2 * exp <= _state) {
				b.myBoard[i][j] = 'B';
				_state -= 2 * exp;
			}else if (exp <= _state){
				b.myBoard[i][j] = 'W';
				_state -= exp;
			}else b.myBoard[i][j] = 'O';
		}
	return b;
}
int Board::utility(char player)
{ // return estimated utility value for player at the current state, INT_MAX if a winning board
	if (isWinner(player)) return INT_MAX;

	int consecUtil = 0;

	for (int r = 0; r < 6; r++)
		if (horizontalConsecutive(4,r,0,0,player)) consecUtil += 1;
	for (int c = 0; c < 6; c++)
		if (verticalConsecutive(4,0,c,0,player)) consecUtil += 1;

	if (diagonalUpConsecutive(4,4,0,0,player)) consecUtil += 1;
	if (diagonalUpConsecutive(4,5,0,0,player)) consecUtil += 1;
	if (diagonalUpConsecutive(4,5,1,0,player)) consecUtil += 1;

	if (diagonalDownConsecutive(4,0,0,0,player)) consecUtil += 1;
	if (diagonalDownConsecutive(4,0,1,0,player)) consecUtil += 1;
	if (diagonalDownConsecutive(4,1,0,0,player)) consecUtil += 1;

	return consecUtil;

}
int Board::utility(int r, int c, int count, char player, int UID)
{ // Old attempt at utility function (this one not used)
	
	// recursive method to check if a number of player chars form a favorable pattern
	
	if (r > 5 || c > 5) return 0;

	if (UID == count) 
		return count;

	int newCount = myBoard[r][c] == toupper(player) ? ++count : 0;
	
	return utility(r, c+1, newCount, player, UID)
		+ utility(r+1, c+1, newCount, player, UID)
		+ utility(r+1, c, newCount, player, UID);
}
