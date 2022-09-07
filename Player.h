#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class Player {
public:
	Player();
	Player(string, string, int);
	void restartCurrPoints();
	void addPoints(double points);
	int getRating();
	double getCurrPoints();
	string getName();
	string getSchool();
	Player& operator=(const Player &);
	bool operator==(Player);
private:
	string name;
	string school;
	int rating;
	double currPoints;
};

#endif