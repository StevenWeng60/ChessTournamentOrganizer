#include "Groups.h"

Groups::Groups() {
	size = 0;
	maxPlayers = 10;
	listOfPlayers = new Player[10];
	groupsStarted = false;
	gameListSize = 0;
	numOfGames = 0;
	gameList = new ChessGame[10];
	bracketGFinished = false;
}

Groups::Groups(int max) {
	size = 0;
	maxPlayers = max;
	listOfPlayers = new Player[max];
	groupsStarted = false;
	gameListSize = 0;
	numOfGames = 0;
	// Need to initialize, gameList will have a greater capacity than max in the future
	gameList = new ChessGame[max];
	bracketGFinished = false;
}

// Function that allows the program to add players into the group
// *This function cannot be called if the startGroups() function has been called
// *This function cannot be called if the number of players in a group is full
void Groups::addPlayer(Player player) {
	if ((groupsStarted) != true && (size != maxPlayers)) {
		listOfPlayers[size] = player;
		size++;
	}
}

// Function which prints the information of every single player in the group
void Groups::printPlayers() {
	for (int i = 0; i < size; i++) {
		cout << listOfPlayers[i].getName() << " " << listOfPlayers[i].getSchool() << " " << listOfPlayers[i].getRating() << endl;
	}
}


// Function which is used to create an array list of ChessGames to store every game that will be created in the group
// It then calls the generateGames() function to create all of the games.
void Groups::startGroups() {
	if (groupsStarted == false) {
		groupsStarted = true;
		int numOfPlayers = size;
		while (numOfPlayers > 0) {
			numOfPlayers--;
			numOfGames += numOfPlayers;
		}
		numOfGames *= 2;
		delete [] gameList;
		gameList = new ChessGame[numOfGames];
		generateGames();
	}
	else {
		cout << "Game already started." << endl;
	}
}

// Function which is used to create and add every single game in the group to the list of ChessGame objects
// *This function can only be called by the startGroups function
void Groups::generateGames() {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			gameList[gameListSize] = ChessGame(listOfPlayers[i], listOfPlayers[j], listOfPlayers[i].getName());
			gameListSize++;
			gameList[gameListSize] = ChessGame(listOfPlayers[i], listOfPlayers[j], listOfPlayers[j].getName());
			gameListSize++;
		}
	}
}


// Function which is used to set the winner of a specific game based on user input
void Groups::inspectGame(string p1, string p2, string white) {
	ChessGame* game = &gameList[0];
	int i;

	for (i = 0; i < gameListSize; i++) {
		if ((gameList[i].getPlayer1().getName() == p1 || gameList[i].getPlayer1().getName() == p2) && (gameList[i].getPlayer2().getName() == p1 || gameList[i].getPlayer2().getName() == p2) && (gameList[i].getWhite() == white)) {
			game = &gameList[i];
			break;
		}
	}

	if (i == gameListSize) {
		cout << "Could not find game" << endl << endl;
		return;
	}
	else if (game->getWinner() == p1 || game->getWinner() == p2 || game->getWinner() == "Draw") {
		cout << "The result for this game has already been set" << endl << endl;
		return;
	}

	cout << "Current game between: " << game->getPlayer1().getName() << " and " << game->getPlayer2().getName() << endl;
	string input;
	cout << "1 - Set Winner" << endl;
	cout << "2 - Set Tie" << endl;
	cout << "Input:";

	cin >> input;
	cout << endl;

	if (input == "1") {
		cout << "Which player won? (1 for " << game->getPlayer1().getName() << ", 2 for " << game->getPlayer2().getName() << ")" << endl;
		cout << "Input:";
		cin >> input;
		if (input == "1") {
			game->setWinner(game->getPlayer1().getName());
			allocatePoints(game->getPlayer1().getName());
		}
		else if (input == "2") {
			game->setWinner(game->getPlayer2().getName());
			allocatePoints(game->getPlayer2().getName());
		}
	}
	else if (input == "2") {
		cout << "Draw set" << endl << endl;
		game->setWinner("Draw");
		addDrawPoints(game->getPlayer1().getName(), game->getPlayer2().getName());
	}

	cout << "Winner: " << game->getWinner() << endl << endl;
}

// Function which is used to add points to the winner of a game
// *This function can only be called by the inspectGame() function
void Groups::allocatePoints(string winner) {
	for (int i = 0; i < size; i++) {
		if (listOfPlayers[i].getName() == winner) {
			listOfPlayers[i].addPoints(1.0);
			break;
		}
	}
}

// Function which is used to give points in the case where a game ends in a draw
// *This function can only be called by the inspectGame() function
void Groups::addDrawPoints(string p1, string p2) {
	for (int i = 0; i < size; i++) {
		if (listOfPlayers[i].getName() == p1) {
			listOfPlayers[i].addPoints(0.5);
		}
		else if (listOfPlayers[i].getName() == p2) {
			listOfPlayers[i].addPoints(0.5);
		}
	}
}

// Function which is used to print every single game in the group, the results, and the points of every single player
void Groups::printAllGames() {
	for (int i = 0; i < gameListSize; i++) {
		cout << "Game " << i + 1 << ": " << gameList[i].getPlayer1().getName() << " and " << gameList[i].getPlayer2().getName() << " (White: " << gameList[i].getWhite() << ") - Winner: " << gameList[i].getWinner() << "" << endl;
	}

	cout << endl;
	cout << fixed << setprecision(1);
	for (int i = 0; i < size; i++) {
		cout << listOfPlayers[i].getName() << " has " << listOfPlayers[i].getCurrPoints() << " points " << endl;
	}
	cout << endl;
}

// Function which is used to return whether or not a group is finished
// A group is finished if every single game in the group has a result of either a win or a draw
bool Groups::groupsFinished() {
	if (gameListSize == 0) {
		return false;
	}
	for (int i = 0; i < gameListSize; i++) {
		if (gameList[i].getWinner() == "N/A") {
			return false;
		}
	}
	return true;
}

// Function which is used to get the winner of the group
// *This function can only be called if groupsFinished() == true
Player Groups::getGroupsWinner() {
	Player player;
	if (groupsFinished()) {
		for (int i = 0; i < size; i++) {
			if (listOfPlayers[i].getCurrPoints() > player.getCurrPoints()) {
				player = listOfPlayers[i];
			}
			else if (listOfPlayers[i].getCurrPoints() == player.getCurrPoints()) {
				if (listOfPlayers[i].getRating() > player.getRating()) {
					player = listOfPlayers[i];
				}
			}
		}
	}
	else {
		cout << "There are still ongoing games" << endl;
	}
	return player;
}

// Function which is used to get the loser of the group
// *This function is only used to help print the final rankings of a bracket
Player Groups::getGroupsLoser() {
	Player player;
	player = listOfPlayers[0];
	if (groupsFinished()) {
		for (int i = 0; i < size; i++) {
			if (listOfPlayers[i].getCurrPoints() < player.getCurrPoints()) {
				player = listOfPlayers[i];
			}
			else if (listOfPlayers[i].getCurrPoints() == player.getCurrPoints()) {
				if (listOfPlayers[i].getRating() < player.getRating()) {
					player = listOfPlayers[i];
				}
			}
		}
	}
	else {
		cout << "There are still ongoing games" << endl << endl;
	}

	return player;
}

// Function which is used to return whether or not the startGroups() function has been called
bool Groups::groupsHasStarted() {
	return groupsStarted;
}

// Function which is used to set bracketGFinished to true;
void Groups::setWinnerExtracted() {
	bracketGFinished = true;
}

// Function which is used to indicate whether the winner of the group has already been extracted.
bool Groups::winnerExtracted() {
	return bracketGFinished;
}

// Function which is used to print every single player in the group except for the winner
// *This function is only used to print the final results of a tournament 
void Groups::printAllLosers() {
	for (int i = 0; i < size; i++) {
		if (listOfPlayers[i] == getGroupsWinner()) {

		}
		else {
			cout << "   " << listOfPlayers[i].getName() << endl;
		}
	}
}

// Function which is used to write every single player in the group (except for the winner) to a file
// *This function is a variation of the printAllLosers() functions
void Groups::saveAllLosers(string input) {
	ofstream outputStream;
	outputStream.open(input, ios::app);
	if (!outputStream.is_open()) {
		cout << "File saving error occurred..." << endl << endl;
		return;
	}
	else {
		for (int i = 0; i < size; i++) {
			if (listOfPlayers[i] == getGroupsWinner()) {

			}
			else {
				outputStream << "   " << listOfPlayers[i].getName() << endl;
			}
		}
		outputStream.close();
	}
}

// Function which is used to set the winner of every single game in the group randomly
// *This function is used for testing
void Groups::simulate() {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < gameListSize; i++) {
		if (rand() % 2 == 0) {
			gameList[i].setWinner(gameList[i].getPlayer1().getName());
			allocatePoints(gameList[i].getPlayer1().getName());
		}
		else {
			gameList[i].setWinner(gameList[i].getPlayer2().getName());
			allocatePoints(gameList[i].getPlayer2().getName());
		}
	}
}
