#pragma once
#ifndef GROUPS_H
#define GROUPS_H

#include "ChessGame.h"

class Groups {
public:
	Groups();
	Groups(int);
	void addPlayer(Player);
	void startGroups();
	void printPlayers();
	void inspectGame(string, string, string);
	void printAllGames();
	void printAllLosers();
	void saveAllLosers(string);
	void simulate();
	void setWinnerExtracted();
	bool groupsFinished();
	bool groupsHasStarted();
	bool winnerExtracted();
	Player getGroupsWinner();
	Player getGroupsLoser();
private:
	Player* listOfPlayers;
	ChessGame* gameList;
	int size;
	int gameListSize;
	int maxPlayers;
	int numOfGames;
	bool groupsStarted;
	bool bracketGFinished;
	void generateGames();
	void allocatePoints(string);
	void addDrawPoints(string, string);
};

#endif