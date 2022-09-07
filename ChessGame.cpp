#include "ChessGame.h"

ChessGame::ChessGame() {
	Player player;
	player1 = player;
	player2 = player;
	winner = "N/A";
	whitePieces = "N/A";
}

ChessGame::ChessGame(Player p1, Player p2, string white) {
	player1 = p1;
	player2 = p2;
	whitePieces = white;
	winner = "N/A";
}

Player ChessGame::getPlayer1() {
	return player1;
}

Player ChessGame::getPlayer2() {
	return player2;
}

string ChessGame::getWinner() {
	return winner;
}

string ChessGame::getWhite() {
	return whitePieces;
}

void ChessGame::setWinner(string name) {
	if (name == player1.getName() || name == player2.getName() || name == "Draw") {
		winner = name;
		return;
	}
	cout << "This player is not in the game" << endl;
	return;
}

// Overloaded assignment operator which allows ChessGame objects to be assigned with the same values as other ChessGame objects
ChessGame& ChessGame::operator=(const ChessGame& other) {
	if (this != &other) {
		player1 = other.player1;
		player2 = other.player2;
		winner = other.winner;
		whitePieces = other.whitePieces;
	}
	return (*this);
}

// Overloaded equality operator which returns whether or not a ChessGame object has equal values to another ChessGame object
bool ChessGame::operator==(ChessGame other) {
	if (player1 == other.getPlayer1() && player2 == other.getPlayer2() && winner == other.winner && whitePieces == other.whitePieces) {
		return true;
	}
	return false;
}
