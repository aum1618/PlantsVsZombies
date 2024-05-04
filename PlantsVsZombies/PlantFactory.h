#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Plant.h"
using namespace sf;
using namespace std;


class PlantFactory {
public:
	Plant** plants;
	int plants_created;
	PlantFactory(int numPlants = 0) {
		plants_created = numPlants;
		plants = new Plant * [plants_created];
	}
	void createPlant(float x, float y) {
		Plant* newPlant = new Plant(x, y);
		Plant** temp = new Plant * [plants_created + 1];
		for (int i = 0; i < plants_created; i++) {
			temp[i] = plants[i];

		}
		temp[plants_created] = newPlant;
		plants_created++;
		delete[] plants;
		plants = temp;

	}
	~PlantFactory() {
		for (int i = 0; i < plants_created; i++) {
			delete plants[i];
		}
		delete[] plants;
	}
};