#pragma once

#include<iostream>
using namespace std;

class Player {

public:
	int level;
	int currency;
	int lives;
	int score;
	Player() {
	level = 1;
	currency = 0;
	lives=3;
	score = 0;
}
};
