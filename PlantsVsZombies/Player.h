#pragma once

#include<iostream>
#include<fstream>
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
	void Serialize(std::ostream& stream) const {
		stream << level << endl;
		stream << currency << endl;
		stream << lives << endl;
		stream << score << endl;
	}

	void Deserialize(std::istream& stream) {
stream >> level;
		stream >> currency;
		stream >> lives;
stream >> score;
	}
};
