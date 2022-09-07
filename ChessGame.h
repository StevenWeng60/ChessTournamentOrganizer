#pragma once
#ifndef CHESSGAME_H
#define CHESSGAME_H
#include "Player.h"

class ChessGame {
public:
	ChessGame();
	ChessGame(Player, Player, string);
	Player getPlayer1();
	Player getPlayer2();
	string getWinner();
	string getWhite();
	void setWinner(string);
	ChessGame& operator=(const ChessGame&);
	bool operator==(ChessGame);
private:
	Player player1;
	Player player2;
	string winner;
	string whitePieces;
};

#endif