#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Zombie.h"
#include "Player.h"
#include <fstream>
using namespace sf;
using namespace std;

class ZombieFactory
{
public:
	Zombie **zombies;
	int zombies_created;
	ZombieFactory(int numZombies = 0, int level = 1)
	{
		zombies_created = numZombies;
		zombies = new Zombie *[zombies_created];

		int numBasicZombies = 0;
		int numFootballZombies = 0;
		int numFlyingZombies = 0;
		int numDancingZombies = 0;

		if (level == 1)
		{
			numBasicZombies = numZombies;
		}
		else if (level == 2)
		{
			numBasicZombies = static_cast<int>(0.7 * numZombies);
			numFootballZombies = numZombies - numBasicZombies;
		}
		else if (level == 3)
		{
			numBasicZombies = static_cast<int>(0.35 * numZombies);
			numFootballZombies = static_cast<int>(0.35 * numZombies);
			numFlyingZombies = numZombies - numBasicZombies - numFootballZombies;
		}
		else if (level > 3)
		{
			// Mix of all types of zombies
			// You can adjust the percentages as needed
			// For example, for level 4 and beyond, you could evenly distribute among all types
			int temp = numZombies;
			numBasicZombies = temp / 3;
			numFootballZombies = temp / 3;
			numFlyingZombies = temp - numBasicZombies - numFootballZombies;

		}

		for (int i = 0; i < numBasicZombies; i++)
		{
			int newX = (rand() % 1001) + 1300;
			int newY = (rand() % 499) + 200;

			newX = newX / 100 * 100;
			newY = newY / 100 * 100;
			zombies[i] = new Zombie(newX, newY);
		}

		for (int i = numBasicZombies; i < numBasicZombies + numFootballZombies; i++)
		{
			int newX = (rand() % 1001) + 1300;
			int newY = (rand() % 499) + 200;

			newX = newX / 100 * 100;
			newY = newY / 100 * 100;
			zombies[i] = new FootballZombie(newX, newY);
		}

		for (int i = numBasicZombies + numFootballZombies; i < numZombies; i++)
		{
			int newX = (rand() % 1001) + 1300;
			int newY = (rand() % 499) + 200;

			newX = newX / 100 * 100;
			newY = newY / 100 * 100;
			zombies[i] = new FlyingZombie(newX, newY);
		}
	}

	ZombieFactory(const ZombieFactory &other)
	{
		zombies_created = other.zombies_created;
		zombies = new Zombie *[zombies_created];
		for (int i = 0; i < zombies_created; i++)
		{
			zombies[i] = new Zombie(*other.zombies[i]);
		}
	}
	void createZombie(float x = 0, float y = 0)
	{
		Zombie *newZombie = new Zombie(x, y);
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
	void summonZombies()
	{

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

	void deleteZombiesInRect(float x, float y, Player &player)
	{
		// Determine the coordinates of the bottom right corner of the box
		float x2 = x + 300;
		float y2 = y + 300;

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
				player.score += zombies[i]->scoring;
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

	bool areZombiesDead()
	{
		for (int i = 0; i < zombies_created; i++)
		{
			if (zombies[i]->isAlive)
			{
				return false;
			}
		}
		return true;
	}

	void move()
	{
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

	// save and load the data for zombieFactory usng the following zombie class functions:
	// void Serialize(std::ostream& stream) const {
	//	stream << health << endl;
	//	stream << speed << endl;
	//	stream << isAlive << endl;
	//	stream << cordintes.x << endl;
	//	stream << cordintes.y << endl;
	//	stream << numframes << endl;
	//	stream << frame << endl;
	//	stream << shouldMove << endl;
	//	stream << type << endl;
	//	stream << hasSummoned << endl;
	//	stream << targetY << endl;
	// }

	// void Deserialize(std::istream& stream) {
	//	stream >> health;
	//	stream >> speed;
	//	stream >> isAlive;
	//	stream >> cordintes.x;
	//	stream >> cordintes.y;
	//	stream >> numframes;
	//	stream >> frame;
	//	stream >> shouldMove;
	//	stream >> type;
	//	stream >> hasSummoned;
	//	stream >> targetY;

	//}

	void Serialize(std::ostream &stream) const
	{
		stream << zombies_created << endl;
		for (int i = 0; i < zombies_created; i++)
		{
			zombies[i]->Serialize(stream);
		}
	}

	void Deserialize(std::istream &stream)
	{
		int temp_zombies_created;
		stream >> temp_zombies_created;
		cout << "Zombies created: " << temp_zombies_created << endl;
		Zombie **temp = new Zombie *[temp_zombies_created];
		for (int i = 0; i < temp_zombies_created; i++)
		{
			string type;
stream >> type;
			if (type == "normal")
			{
				temp[i] = new Zombie();
			}
			else if (type == "football")
			{
				temp[i] = new FootballZombie();
			}
			else if (type == "flying")
			{
				temp[i] = new FlyingZombie();
			}
			else if (type == "dancing")
			{
				temp[i] = new DancingZombie();
			}
			temp[i]->Deserialize(stream);
		}
		delete zombies;
		zombies_created = temp_zombies_created;
		zombies = temp;
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
