#include "UserInterface.h"

UserInterface::UserInterface() {
	listOfPlayers = new Player[100];
	listOfGroups = new Groups[10];
	currSize = 0;
	numOfGroups = 0;
	Bracket br;
	bracket = br;
	bracketStarted = false;
	fileName = "N/A";
	tournamentStarted = false;
}

//Menu, the first thing that pops up when you start the Chess Tournament Organizer
void UserInterface::menu() {
	cout << "Welcome to the Chess Tournament Organizer" << endl << endl;

	string input = "1";
	while (input != "0") {
		cout << "(0) Menu Commands -" << endl;
		cout << "1 - Add players (General)" << endl;
		cout << "2 - Print all players (General)" << endl;
		cout << "3 - Start tournament (Tournament)" << endl;
		cout << "4 - View current tournament (Tournament)" << endl;
		cout << "5 - View final results (Tournament)" << endl;
		cout << "6 - Save final results to file (Tournament)" << endl;
		cout << "q - quit" << endl;

		cout << "Input: ";
		cin >> input;
		cout << endl;

		if (input == "1") {
			if (tournamentStarted == false) {
				addPlayersMenu();
			}
			else {
				cout << "You cannot add players into an ongoing tournament" << endl << endl;
			}
		}
		else if (input == "2") {
			printPlayers();
		}
		else if (input == "3") {
			if (tournamentStarted == false) {
				sortPlayers();
				startTournamentUI();
			}
			else {
				cout << "Tournament has already started" << endl << endl;
			}
		}
		else if (input == "4") {
			if (tournamentStarted == true) {
				tournamentViewerUI();
			}
			else {
				cout << "There is no tournament to view" << endl << endl;
			}
		}
		else if (input == "5") {
			if (bracket.getCompleted()) {
				bracket.printResults();
				cout << "#" << numOfGroups + 1 << " -" << endl;
				for (int i = 0; i < numOfGroups; i++) {
					listOfGroups[i].printAllLosers();
				}
				cout << setw(27) << setfill('-') << "" << endl;
				cout << endl;
			}
			else {
				cout << "The tournament is not finished" << endl << endl;
			}
		}
		else if (input == "6") {
			if (bracket.getCompleted()) {
				string fileName;
				fileName = bracket.saveFile();
				if (fileName == "-1") {
					cout << "File loading error occurred..." << endl << endl;
				}
				else {
					ofstream outStream;
					outStream.open(fileName, ios::app);
					if (!outStream.is_open()) {
						cout << "File loading error occurred..." << endl << endl;
					}
					else {
						outStream << "#" << numOfGroups + 1 << " -" << endl;
						outStream.close();
						for (int i = 0; i < numOfGroups; i++) {
							listOfGroups[i].saveAllLosers(fileName);
						}
						outStream.open(fileName, ios::app);
						if (!outStream.is_open()) {
							cout << "Error occurred ..." << endl;
						}
						else{
							outStream << setw(27) << setfill('-') << "" << endl;
							outStream << endl;
							outStream.close();
						}
					}
				}
				cout << endl;
				cout << "File saved successfully" << endl << endl;
			}
			else {
				cout << "The tournament is not finished" << endl << endl;
			}
		}
		else if (input == "q") {
			break;
		}
	}
}

// Tournament user interface for groups and brackets
void UserInterface::tournamentViewerUI() {
	string input = "1";
	while (input != "0") {
		cout << "(1) Tournament viewer" << endl;
		cout << "1 - Inspect group (Groups)" << endl;
		cout << "2 - View all groups (Groups)" << endl;
		cout << "3 - Simulate all groups (Groups)" << endl;
		cout << "4 - Start final " << numOfGroups << " player bracket (Bracket)" << endl;
		cout << "5 - Inspect bracket (Bracket)" << endl;
		cout << "q - quit" << endl;

		cout << "Input: ";
		cin >> input;
		cout << endl;

		if (input == "1") {
			groupViewer();
		}
		else if (input == "2") {
			for (int i = 0; i < numOfGroups; i++) {
				cout << "Group " << i + 1 << endl;
				listOfGroups[i].printPlayers();
				cout << "Winner: " << listOfGroups[i].getGroupsWinner().getName() << endl;
				cout << endl;
			}
		}
		else if (input == "3") {
			cout << "Simulating all groups" << endl << endl;
			for (int i = 0; i < numOfGroups; i++) {
				if (listOfGroups[i].groupsHasStarted()) {
					cout << "Some groups have already been started, you cannot simulate anymore" << endl << endl;
					break;
				}
				else {
					listOfGroups[i].startGroups();
					listOfGroups[i].simulate();
				}
			}
		}
		else if (input == "4") {
			if (!bracketStarted) {
				bool finished = true;
				for (int i = 0; i < numOfGroups; i++) {
					if (!listOfGroups[i].groupsFinished()) {
						finished = false;
						break;
					}
				}

				if (finished == true) {
					cout << "Bracket started" << endl;
					bracketStarted = true;
					Bracket br(numOfGroups);
					bracket = br;
					for (int i = 0; i < numOfGroups; i++) {
						bracket.addPlayer(listOfGroups[i].getGroupsWinner());
					}
					bracket.printPlayers();
				}
				else {
					cout << "There are still ongoing groups" << endl << endl;
				}
			}
			else {
				cout << "The final bracket has already started" << endl << endl;
			}
		}
		else if (input == "5") {
			if (bracketStarted) {
				bracketViewerUI();
			}
			else {
				cout << "You must start the final bracket before you can view it" << endl << endl;
			}
		}
		else if (input == "q") {
			break;
		}
	}
}

// Function that allows the User to inspect certain groups in the tournament
void UserInterface::groupViewer() {
	string input;
	cout << "Which group number? (1 - " << numOfGroups << ")" << endl;
	int intInput;
	cout << "Input: ";
	cin >> intInput;
	cout << endl;

	if (intInput > 0 && intInput < numOfGroups + 1) {
		while (input != "0") {
			cout << "(2) Group viewer (Group # " << intInput << ")" << endl;
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
	else {
		cout << "Invalid group number" << endl << endl;
	}
}

// User interface for the final bracket in the tournament
void UserInterface::bracketViewerUI() {
	string input;

	while (input != "0") {
		if (bracket.getCurrRound() == 0) {
			cout << "(2) Bracket viewer (Press 1 to start the bracket rounds)" << endl;
		}
		else if (bracket.getCurrRound() == 1) {
			cout << "(2) Bracket viewer (Tournament is on the last round or is finished)" << endl;
		}
		else {
			cout << "(2) Bracket viewer (Current round: Top " << bracket.getCurrRound() << ")" << endl;
		}
		cout << "1 - Start next round" << endl;
		cout << "2 - Inspect 1v1 series" << endl;
		cout << "3 - View all groups" << endl;
		cout << "4 - Simulate bracket (For Tests)" << endl;
		cout << "5 - Print results" << endl;
		cout << "q - quit" << endl;

		cout << "Input: ";
		cin >> input;
		cout << endl;

		if (input == "1") {
			if (bracket.getCurrRound() == 2) {
				bracket.setCurrRound(1);
			}
			bracket.startNextRound();
		}
		else if (input == "2") {
			if (bracket.getCurrRound() != 0) {
				bracket.bracketViewer();
			}
			else {
				cout << "There are no groups to view" << endl << endl;
			}
		}
		else if (input == "3") {
			bracket.printBracket();
		}
		else if (input == "4") {
			cout << "Bracket has been simulated" << endl << endl;
			bracket.simulate();
		}
		else if (input == "5") {
			bracket.printResults();
			cout << endl;
		}
		else if (input == "q") {
			break;
		}
	}
}

// Function that is called to start the tournament and creates the amount of groups necessary for the tournament based on user input
void UserInterface::startTournamentUI() {
	string input = "1";
	while (input != "0") {
		cout << "(1) How many players in the final bracket?" << endl;
		cout << "8 - Eight players in the final bracket (32 players minimum)" << endl;
		cout << "16 - Sixteen players in the final bracket (64 players minimum)" << endl;
		cout << "q - quit" << endl;

		cout << "Input: ";
		cin >> input;
		cout << endl;

		if (input == "8" && currSize >= 32) {
			cout << "Tournament has been started" << endl << endl;
			tournamentStarted = true;
			numOfGroups = 8;
			double numInGroups = ceil((double)currSize / 8);
			int numPeople = int(numInGroups);
			listOfGroups = new Groups[8];

			for (int i = 0; i < 8; i++) {
				Groups group(numPeople);
				listOfGroups[i] = group;
			}

			int k = 0;
			for (int j = 0; j < currSize; j++) {
				listOfGroups[k].addPlayer(listOfPlayers[j]);
				k++;
				if (k == 8) {
					k = 0;
				}
			}
			break;
		}
		else if (input == "16" && currSize >= 64) {
			cout << "Tournament has been started" << endl << endl;
			tournamentStarted = true;
			numOfGroups = 16;
			double numInGroups = ceil((double)currSize / 16);
			int numPeople = int(numInGroups);
			listOfGroups = new Groups[16];

			for (int i = 0; i < 16; i++) {
				Groups group(numPeople);
				listOfGroups[i] = group;
			}

			int k = 0;
			for (int j = 0; j < currSize; j++) {
				listOfGroups[k].addPlayer(listOfPlayers[j]);
				k++;
				if (k == 16) {
					k = 0;
				}
			}
			break;
		}
		else if (input == "q") {
			break;
		}
		else {
			cout << "Invalid input or number of minimum players are not satisfied" << endl << endl;
		}
	}
}

// Function that allows the user to choose how they want to add players to the tournament
void UserInterface::addPlayersMenu() {
	int i = 0;
	string input = "1";
	while (input != "0") {
		cout << "(1) How would you like to add players?" << endl;
		cout << "1 - Manual input" << endl;
		cout << "2 - File loading" << endl;
		cout << "q - quit" << endl;

		cout << "Input: ";
		cin >> input;
		cout << endl;

		if (input == "1") {
			addPlayersManually();
		}
		else if (input == "2") {
			fileLoadPlayers();
		}
		else if (input == "q") {
			break;
		}
	}
}

// Function that loads player data from a file 
void UserInterface::fileLoadPlayers() {
	ifstream inputStream;
	string input = "1";
	string name;
	string school;
	int rating;

	cout << "Enter file name/directory " << endl;
	cin >> input;
	inputStream.open(input);
	if (!inputStream.is_open()) {
		cout << "Invalid file" << endl << endl;
		return;
	}
	else {
		cout << endl;
		while (!inputStream.eof()) {
			getline(inputStream, name);
			getline(inputStream, school);
			inputStream >> rating;
			inputStream.ignore();

			if (name == "") {
				break;
			}

			Player aplayer(name, school, rating);
			listOfPlayers[currSize] = aplayer;
			currSize++;
			}
		if (!inputStream.eof()) {
			cout << "Error in file reading occurred" << endl;				}
		else {
			cout << "File loaded successfully" << endl;
		}

		inputStream.close();
	}

	cout << endl;

}

// Function that adds players based on user input
void UserInterface::addPlayersManually() {
	string input = "1";
	string name;
	string school;
	int rating;

	cin.ignore();
	cout << "Enter player name: ";
	getline(cin, name);

	cout << endl << "Enter player school: ";
	getline(cin, school);

	cout << endl << "Enter player rating: ";
	cin >> rating;
	cout << endl;

	if (name != "" || school != "" || (rating / 4) > 0) {
		Player aplayer(name, school, rating);
		listOfPlayers[currSize] = aplayer;
		currSize++;
	}

}

// Function that prints the information of every single player in the tournament
void UserInterface::printPlayers() {
	cout << left << setw(25) << "Name" << setw(20) << "|School" << " |Rating" << endl;
	cout << setfill('-') << setw(65) << "" << endl;
	cout << setfill(' ');
	for (int i = 0; i < currSize; i++) {
		cout << left << setw(25) << listOfPlayers[i].getName() << "|" << setw(20) << listOfPlayers[i].getSchool();
		cout << "|" << listOfPlayers[i].getRating() << endl;
	}
	cout << endl;
	cout << "Number of Players: " << currSize << endl;
	cout << endl;
}

// Function which sorts players in order by rating using shellsort
void UserInterface::sortPlayers() {
	int n = currSize;
	int h = 1;

	while (h < n / 3) {
		h = 3 * h + 1;
	}

	Player temp;
	while (h >= 1) {
		for (int i = h; i < n; i++) {
			for (int j = i; j >= h; j -= h) {
				if (listOfPlayers[j].getRating() < listOfPlayers[j - h].getRating()) {
					temp = listOfPlayers[j];
					listOfPlayers[j] = listOfPlayers[j - h];
					listOfPlayers[j - h] = temp;
				}
				else {
					break;
				}
			}
		}
		h /= 3;
	}

	for (int i = 0; i < currSize; i++) {
		for (int j = i; j > 0; j--) {
			if (listOfPlayers[j - 1].getRating() > listOfPlayers[j].getRating()) {
				temp = listOfPlayers[j];
				listOfPlayers[j] = listOfPlayers[j - 1];
				listOfPlayers[j - 1] = temp;
			}
			else {
				break;
			}
		}
	}

}
