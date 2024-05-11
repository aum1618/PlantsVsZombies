#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Zombie.h"
using namespace sf;
using namespace std;

class ZombieFactory
{
public:
	Zombie **zombies;
	int zombies_created;
	ZombieFactory(int numZombies = 0)
	{
		zombies_created = numZombies;
		zombies = new Zombie *[zombies_created];
		for (int i = 0; i < numZombies; i++)
		{
			int newX = (rand() % 1001) + 1300; 
			int newY = (rand() % 499) + 200;   

			newX = newX / 100 * 100;
			newY = newY / 100 * 100;
			zombies[i] = new Zombie(newX, newY);
		}
	}
	void createZombie(float x=0,float y=0)
	{
		Zombie *newZombie = new Zombie(x,y);
		Zombie **temp = new Zombie *[zombies_created + 1];
		for (int i = 0; i < zombies_created; i++)
		{
			temp[i] = zombies[i];
		}
		temp[zombies_created] = newZombie;
		zombies_created++;
		delete[] zombies;
		zombies = temp;
	}
	bool isZombieThere(float x, float y)
	{
		for (int i = 0; i < zombies_created; i++)
		{
			// Get the bounds of the zombie sprite
			FloatRect zombieBounds = zombies[i]->sprite.getGlobalBounds();
			// Check if the coordinates (x, y) are within the bounds of the zombie sprite
			if (zombieBounds.contains(x, y))
			{
				return true;
			}
		}
		return false;
	}
	void freezeZombies(int x, int y)
	{
		int rightEdge = x + 200;
		int bottomEdge = y + 200;
		for (int i = 0; i < zombies_created; i++)
		{
			if (zombies[i]->cordintes.x >= x && zombies[i]->cordintes.x <= rightEdge &&
				zombies[i]->cordintes.y >= y && zombies[i]->cordintes.y <= bottomEdge)
			{
				zombies[i]->shouldMove = false;
				zombies[i]->clock2.restart();
			}
		}
	}
	void summonZombies() {

		for (int i = 0; i < zombies_created; i++)
		{
			if (zombies[i]->type == "dancing" && !zombies[i]->hasSummoned)
			{
				int random = rand() % 100;
				if (random < 10 && zombies[i]->cordintes.x <= 900)
				{
					float zombieX = zombies[i]->cordintes.x;
					float zombieY = zombies[i]->cordintes.y;

					int newY = zombieY;
					if (zombieY == 200 || random % 2)
					{
						newY += 100;
					}
					{
						newY -= 100;
					}
					cout << "Dancing zombie summoned" << endl;
					createZombie(zombieX + 100, zombieY);
					createZombie(zombieX - 100, zombieY);
					createZombie(zombieX, newY);
					createZombie(zombieX + 100, newY);
					createZombie(zombieX - 100, newY);
					zombies[i]->hasSummoned = true;
				}
			}

		}

	}

	void deleteZombiesInRect(float x, float y)
	{
		// Determine the coordinates of the bottom right corner of the box
		float x2 = x + 300;
		float y2 = y;

		// Iterate through zombies and delete those within the box
		for (int i = 0; i < zombies_created; i++)
		{
			// Get the bounds of the zombie sprite
			FloatRect zombieBounds = zombies[i]->sprite.getGlobalBounds();
			// Check if the zombie is within the box
			if (zombieBounds.left >= x && zombieBounds.left <= x2 &&
				zombieBounds.top >= y && zombieBounds.top <= y2)
			{
				// Delete the zombie
				delete zombies[i];
				// Move the last zombie to the current position to maintain continuity in the array
				zombies[i] = zombies[zombies_created - 1];
				// Decrease the count of zombies
				zombies_created--;
				// Decrement i to recheck the current position after swapping
				i--;
			}
		}
	}

	void move() {
		for (int i = 0; i < zombies_created; i++)
		{
			zombies[i]->move();
		}

	}
	void draw(RenderWindow &window)
	{
		for (int i = 0; i < zombies_created; i++)
		{
			zombies[i]->draw(window);
		}
	}

	~ZombieFactory()
	{
		for (int i = 0; i < zombies_created; i++)
		{
			delete zombies[i];
		}
		delete[] zombies;
	}
};
