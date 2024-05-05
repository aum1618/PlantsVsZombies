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
		cout << "Creating plant at (" << x << ", " << y << ")" << endl;
		int newX = x / 100;
		int newY = y / 100;
		newX = newX * 100;
		newY = newY * 100;

		cout << "Plant at (" << newX << ", " << newY << ")" << endl;
		Plant* newPlant = new Plant(newX, newY);
		Plant** temp = new Plant * [plants_created + 1];
		for (int i = 0; i < plants_created; i++) {
			temp[i] = plants[i];

		}
		temp[plants_created] = newPlant;
		plants_created++;
		delete[] plants;
		plants = temp;

	}
	bool isPlantThere(float x, float y) {
		for (int i = 0; i < plants_created; i++) {
			// Get the bounds of the plant sprite
			FloatRect plantBounds = plants[i]->sprite.getGlobalBounds();
			// Check if the coordinates (x, y) are within the bounds of the plant sprite
			if (plantBounds.contains(x, y)) {
				return true;
			}
		}
		return false;
	}

	void removePlant(float x, float y) {
		for (int i = 0; i < plants_created; i++) {
			// Get the bounds of the plant sprite
			FloatRect plantBounds = plants[i]->sprite.getGlobalBounds();
			// Check if the coordinates (x, y) are within the bounds of the plant sprite
			if (plantBounds.contains(x, y)) {
				delete plants[i];
				for (int j = i; j < plants_created - 1; j++) {
					plants[j] = plants[j + 1];
				}
				plants_created--;
				Plant** temp = new Plant * [plants_created];
				for (int j = 0; j < plants_created; j++) {
					temp[j] = plants[j];
				}
				delete[] plants;
				plants = temp;
				return;
			}
		}
	}


	~PlantFactory() {
		for (int i = 0; i < plants_created; i++) {
			delete plants[i];
		}
		delete[] plants;
	}
};