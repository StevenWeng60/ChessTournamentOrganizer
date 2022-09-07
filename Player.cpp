#include "Player.h"

Player::Player() {
	name = "N/A";
	school = "N/A";
	rating = -1;
	currPoints = 0.0;
}

Player::Player(string pname, string pschool, int prating) {
	name = pname;
	school = pschool;
	rating = prating;
	currPoints = 0.0;
}

int Player::getRating() {
	return rating;
}

double Player::getCurrPoints() {
	return currPoints;
}

string Player::getName() {
	return name;
}

string Player::getSchool() {
	return school;
}

void Player::addPoints(double points) {
	currPoints += points;
}

void Player::restartCurrPoints() {
	currPoints = 0;
}

// Overloaded assignment operator which allows Player objects to be assigned with the same values as other Player objects
Player& Player::operator=(const Player &other) {
	if (this != &other) {
		name = other.name;
		school = other.school;
		rating = other.rating;
		currPoints = other.currPoints;
	}
	return (*this);
}

// Overloaded equality operator which returns whether or not a Player object has equal values to another Player object
bool Player::operator==(Player other) {
	if (name != other.getName() || school != other.getSchool() || rating != other.getRating()) {
		return false;
	}
	return true;
}