#pragma once

#include<iostream>
#include<fstream>
using namespace std;

class Player {

public:
	int level;
	int currency;
	int lives;
	Player() {
	level = 1;
	currency = 0;
	lives=3;
}
	void Serialize(std::ostream& stream) const {
		stream << level << endl;
		stream << currency << endl;
		stream << lives << endl;
	}

	void Deserialize(std::istream& stream) {
stream >> level;
		stream >> currency;
		stream >> lives;
	}
};
