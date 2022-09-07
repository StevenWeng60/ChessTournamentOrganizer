#pragma once
#ifndef BRACKET_H
#define BRACKET_H
#include "Groups.h"

class Bracket {
public:
	Bracket();
	Bracket(int);
	void startNextRound();
	void printBracket();
	void printPlayers();
	void addPlayer(Player player);
	void simulate();
	void printResults();
	void setCurrRound(int);
	void bracketViewer();
	string saveFile();
	bool getCompleted();
	int getCurrRound();

private:
	Player* listOfPlayers;
	Groups* listOfGroups;
	int size;
	int groupSize;
	int max;
	int currRound;
	int numOfGroups;
	bool bracketFinished;

};


#endif
