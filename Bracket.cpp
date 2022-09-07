#include "Bracket.h"

Bracket::Bracket() {
	listOfGroups = new Groups[10];
	listOfPlayers = new Player[10];
	size = 0;
	groupSize = 0;
	max = 0;
	currRound = 0;
	bracketFinished = false;
	numOfGroups = 0;
}

Bracket::Bracket(int bracketType) {
	numOfGroups = 0;
	int copyBT = bracketType;
	while (copyBT > 1) {
		copyBT /= 2;
		numOfGroups += copyBT;
	}
	size = 0;
	max = bracketType;
	groupSize = 0;
	listOfGroups = new Groups[numOfGroups];
	listOfPlayers = new Player[bracketType];
	currRound = 0;
	bracketFinished = false;
}

// Function that allows the User to inspect a specific group in the bracket
void Bracket::bracketViewer() {
	string input;
	cout << "Which group number? (1 - " << groupSize << ")" << endl;
	int intInput;
	cout << "Input: ";
	cin >> intInput;
	cout << endl;

	if (intInput > 0 && intInput < groupSize + 1) {
		while (input != "0") {
			cout << "(3) Bracket viewer (Group # " << intInput << ")" << endl;
			cout << "1 - Create games" << endl;
			cout << "2 - Inspect game" << endl;
			cout << "3 - View all players" << endl;
			cout << "4 - Print all games" << endl;
			cout << "5 - Simulate group (For Tests)" << endl;
			cout << "q - quit" << endl;

			cout << "Input: ";
			cin >> input;
			cout << endl;

			if (input == "1") {
				if (!listOfGroups[intInput - 1].groupsHasStarted()) {
					cout << "Games have been created" << endl << endl;
					listOfGroups[intInput - 1].startGroups();
				}
				else {
					cout << "Games have already been created in this group" << endl << endl;
				}
			}
			else if (input == "2") {
				if (listOfGroups[intInput - 1].groupsHasStarted()) {
					string p1name;
					string p2name;
					string white;
					cin.ignore();
					cout << "Enter first player name" << endl;
					getline(cin, p1name);
					cout << "Enter second player name" << endl;
					getline(cin, p2name);
					cout << "Enter player with white" << endl;
					getline(cin, white);
					cout << endl;

					listOfGroups[intInput - 1].inspectGame(p1name, p2name, white);
				}
				else {
					cout << "Games have not been created yet" << endl << endl;
				}
			}
			else if (input == "3") {
				listOfGroups[intInput - 1].printPlayers();
				cout << endl;
			}
			else if (input == "4") {
				if (listOfGroups[intInput - 1].groupsHasStarted()) {
					listOfGroups[intInput - 1].printAllGames();
				}
				else {
					cout << "Games have not been created yet" << endl << endl;
				}
			}
			else if (input == "5") {
				if (listOfGroups[intInput - 1].groupsHasStarted() && !listOfGroups[intInput - 1].groupsFinished()) {
					listOfGroups[intInput - 1].simulate();
					cout << "Games have been simulated" << endl << endl;
				}
				else {
					cout << "Games have not been created yet/games are finished" << endl << endl;
				}
			}
			else if (input == "q") {
				break;
			}
		}
	}
}

// Function that allows the program to add players into the bracket
// *This function can only be called by the program when the bracket is first created
// *This function cannot be called if the number of players in the bracket is full
void Bracket::addPlayer(Player player) {
	if (size < max) {
		player.restartCurrPoints();
		listOfPlayers[size] = player;
		size++;
	}
	else {
		cout << "Number of players in final bracket is full" << endl << endl;
	}
}

// Function which is used to start the next round of the bracket by creating the next set of groups based on the winners of the previous rounds (groups)
// *This function can be called repeatedly until there is only one group left (or when the round is "Top 2"). After that no more groups can be created.
void Bracket::startNextRound() {
	if (!bracketFinished && size == max) {
		if (currRound == 0) {
			currRound = max;
			int nGroups = currRound / 2;
			for (int i = 0; i < max; i++) {
				Groups group(2);
				listOfPlayers[i].restartCurrPoints();
				group.addPlayer(listOfPlayers[i]);
				i++;
				listOfPlayers[i].restartCurrPoints();
				group.addPlayer(listOfPlayers[i]);
				listOfGroups[groupSize] = group;
				groupSize++;
			}
		}
		else {
			bool previousRoundFinished = true;
			for (int i = 0; i < groupSize; i++) {
				if (listOfGroups[i].getGroupsWinner().getName() == "N/A") {
					cout << "Previous round is not finished" << endl << endl;
					previousRoundFinished = false;
					break;
				}
			}
			//Player player;
			int ogGroupSize = groupSize;
			if (previousRoundFinished) {
				int nGroups = currRound;
				currRound /= 2;
				for (int i = 0; i < ogGroupSize; i++) {
					if (listOfGroups[i].winnerExtracted()) {
						continue;
					}
					else {
						Groups group(2);
						for (int j = 0; j < size; j++) {
							if (listOfGroups[i].getGroupsWinner() == listOfPlayers[j]) {
								listOfPlayers[j].restartCurrPoints();
								group.addPlayer(listOfPlayers[j]);
							}
						}
						//group.addPlayer(listOfGroups[i].getGroupsWinner());
						listOfGroups[i].setWinnerExtracted();
						i++;
						for (int j = 0; j < size; j++) {
							if (listOfGroups[i].getGroupsWinner() == listOfPlayers[j]) {
								listOfPlayers[j].restartCurrPoints();
								group.addPlayer(listOfPlayers[j]);
							}
						}
						//group.addPlayer(listOfGroups[i].getGroupsWinner());
						listOfGroups[i].setWinnerExtracted();
						listOfGroups[groupSize] = group;
						groupSize++;
						if (groupSize == numOfGroups) {
							bracketFinished = true;
						}
					}
				}
			}
		}
	}
	else {
		cout << "Either the bracket has been finished or the player requirement has not been met" << endl << endl;
	}
}

// Function which is used to print the information of every single group in the bracket
void Bracket::printBracket() {
	int calculateRounds = max / 2;
	int numRounds = max / 2;
	int roundTracker = max;
	for (int i = 0; i < groupSize; i++) {
		if (numRounds > i) {
			cout << "Round: Top " << roundTracker << endl;
			cout << "Group " << i + 1 << endl;
			listOfGroups[i].printPlayers();
			cout << "Winner: " << listOfGroups[i].getGroupsWinner().getName() << endl;
			cout << endl;
		}
		else {
			calculateRounds /= 2;
			roundTracker /= 2;
			numRounds += calculateRounds;
			cout << "Round: Top " << roundTracker << endl;
			cout << "Group " << i + 1 << endl;
			listOfGroups[i].printPlayers();
			cout << "Winner: " << listOfGroups[i].getGroupsWinner().getName() << endl;
			cout << endl;
		}
	}

	cout << endl;
}

// Function which is used to print the information of every player in the bracket
void Bracket::printPlayers() {
	for (int i = 0; i < size; i++) {
		cout << listOfPlayers[i].getName() << " " << listOfPlayers[i].getSchool() << " " << listOfPlayers[i].getRating() << endl;
	}
	cout << endl;
}

// Function which is used to print the results of the bracket
// *This function can only be called when every single group in the bracket is finished
void Bracket::printResults() {
	if (bracketFinished) {
		if (listOfGroups[groupSize - 1].groupsFinished()) {
			cout << "Tournament Results --------" << endl;
			int j = 1;
			int numOfSameRank = 2;
			int k = 0;
			int rank = 3;
			for (int i = groupSize - 1; i >= 0; i--) {
				if (i == groupSize - 1) {
					cout << "#" << j << " " << listOfGroups[i].getGroupsWinner().getName() << endl;
					j++;
					cout << "#" << j << " " << listOfGroups[i].getGroupsLoser().getName() << endl;
				}
				else if (numOfSameRank > k) {
					cout << "#" << rank << " " << listOfGroups[i].getGroupsLoser().getName() << endl;
					k++;
				}

				if (numOfSameRank == k) {
					rank += numOfSameRank;
					numOfSameRank *= 2;
					k = 0;
				}
			}
		}
	}
	else {
		cout << "The games are not finished yet" << endl;
	}
}

// Function which is used to return the current round of the bracket
int Bracket::getCurrRound() {
	return currRound;
}

// Function which is used to set the current round of the bracket
void Bracket::setCurrRound(int round) {
	currRound = round;
}

// Function which returns whether or not the last group of the bracket is finished
bool Bracket::getCompleted() {
	if (bracketFinished) {
		if (listOfGroups[groupSize - 1].groupsFinished()) {
			return true;
		}
	}

	return false;
}

// Function which is used to write the ranking of every single player in the bracket to a file
// *This function is a variation of the printResults() functions
string Bracket::saveFile() {
	ofstream outputStream;
	string input;

	cout << "Enter file name/directory to write to " << endl;
	cin >> input;
	outputStream.open(input);
	if (!outputStream.is_open()) {
		cout << "Invalid file" << endl << endl;
		return "-1";
	}
	else {
		string tournamentName;
		cout << endl;
		cout << "Enter tournament name: " << endl;
		cin.ignore();
		getline(cin, tournamentName);
		outputStream << tournamentName << endl << endl;

		if (bracketFinished) {
			if (listOfGroups[groupSize - 1].groupsFinished()) {
				outputStream << "Tournament Results --------" << endl;
				int j = 1;
				int numOfSameRank = 2;
				int k = 0;
				int rank = 3;
				for (int i = groupSize - 1; i >= 0; i--) {
					if (i == groupSize - 1) {
						outputStream << "#" << j << " " << listOfGroups[i].getGroupsWinner().getName() << endl;
						j++;
						outputStream << "#" << j << " " << listOfGroups[i].getGroupsLoser().getName() << endl;
					}
					else if (numOfSameRank > k) {
						outputStream << "#" << rank << " " << listOfGroups[i].getGroupsLoser().getName() << endl;
						k++;
					}

					if (numOfSameRank == k) {
						rank += numOfSameRank;
						numOfSameRank *= 2;
						k = 0;
					}
				}
			}
			outputStream.close();
			return input;
		}
		else {
			cout << "The games are not finished yet" << endl << endl;
		}
		outputStream.close();
	}

	return "-1";
}

// Function which is used to set the winner of every single group in a current round
// *This is used for testing 
void Bracket::simulate() {
	for (int i = 0; i < groupSize; i++) {
		if (listOfGroups[i].winnerExtracted() == false && !listOfGroups[i].groupsFinished()) {
			listOfGroups[i].startGroups();
			listOfGroups[i].simulate();
		}
	}
}