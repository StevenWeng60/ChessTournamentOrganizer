#pragma once
#ifndef USER_INTERFACE
#define USER_INTERFACE

#include "Bracket.h"

class UserInterface {
public:
	UserInterface();
	void menu();

private:
	Groups* listOfGroups;
	Player* listOfPlayers;
	Bracket bracket;
	string fileName;
	int currSize;
	int numOfGroups;
	bool tournamentStarted;
	bool bracketStarted;
	void addPlayersMenu();
	void addPlayersManually();
	void fileLoadPlayers();
	void printPlayers();
	void sortPlayers();
	void startTournamentUI();
	void tournamentViewerUI();
	void groupViewer();
	void bracketViewerUI();
};

#endif