#include <iostream>
#include <SFML/Graphics.hpp>
#include "Zombie.h"
using namespace sf;
using namespace std;



class ZombieFactory {
public:
	Zombie** zombies;
	int zombies_created;
	ZombieFactory(int numZombies = 0) {
		zombies_created = numZombies;
		zombies = new Zombie * [zombies_created];
		for (int i = 0; i < numZombies; i++) {
			int newX = (rand() % 1001) + 1300;  // Generates random number between 1300 and 2300
			int newY = (rand() % 499)+200;          // Generates random number between 0 and 900

			// Make newX and newY multiples of 100
			
			newY = newY / 100 * 100;
			zombies[i] = new Zombie(newX, newY);
		}
	}
	void createZombie() {
		Zombie* newZombie = new Zombie();
		Zombie** temp = new Zombie * [zombies_created + 1];
		for (int i = 0; i < zombies_created; i++) {
			temp[i] = zombies[i];
		}
		temp[zombies_created] = newZombie;
		zombies_created++;
		delete[] zombies;
		zombies = temp;
	}
	bool isZombieThere(float x, float y) {
		for (int i = 0; i < zombies_created; i++) {
			// Get the bounds of the zombie sprite
			FloatRect zombieBounds = zombies[i]->sprite.getGlobalBounds();
			// Check if the coordinates (x, y) are within the bounds of the zombie sprite
			if (zombieBounds.contains(x, y)) {
				return true;
			}
		}
		return false;
	}
	//create a function to freeze zombies present inside a rectangle  fro 5 seconds
	void freezeZombies(int x,int y) {
		cout << x << " " << y;
		int leftEdge = x;
		int rightEdge = x + 300;
		int topEdge = y;
		int bottomEdge = y + 300;

		for (int i = 0; i < zombies_created; i++) {
			if (zombies[i]->cordintes.x >= leftEdge && zombies[i]->cordintes.x <= rightEdge && zombies[i]->cordintes.y >= topEdge && zombies[i]->cordintes.y <= bottomEdge) {
				cout << "Zombie found in the box" << endl;
				zombies[i]->shouldMove = false;
				zombies[i]->clock.restart();
		}

		}
	}
	


	~ZombieFactory() {
		for (int i = 0; i < zombies_created; i++) {
			delete zombies[i];
		}
		delete[] zombies;
	}
};