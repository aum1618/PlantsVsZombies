#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Plant.h"
using namespace sf;
using namespace std;

class PlantFactory
{
public:
	Plant **plants;
	int plants_created;
	PlantFactory(int numPlants = 0)
	{
		plants_created = numPlants;
		plants = new Plant *[plants_created];
	}
	void createPlant(float x, float y, string cursor)
	{
		int newX = x / 100;
		int newY = y / 100;
		newX = newX * 100;
		newY = newY * 100;

		Plant *newPlant;
		if (cursor == "sunflower")
		{
			newPlant = new SunFlower(newX, newY);
		}
		else if (cursor == "peashooter")
		{
			newPlant = new PeeShooter(newX, newY);
		}
		else if (cursor == "repeater")
		{
			newPlant = new Repeater(newX, newY);
		}
		else if (cursor == "snowpea")
		{
			newPlant = new SnowPea(newX, newY);
		}
		else if (cursor == "fumeshroom")
		{
			newPlant = new FumeShroom(newX, newY);
		}
		else if (cursor == "wallnut")
		{
			newPlant = new WallNut(newX, newY);
		}
		else
		{
			newPlant = new CherryBomb(newX, newY);
		}

		Plant **temp = new Plant *[plants_created + 1];
		for (int i = 0; i < plants_created; i++)
		{
			temp[i] = plants[i];
		}
		temp[plants_created] = newPlant;
		plants_created++;
		delete[] plants;
		plants = temp;
	}
	bool isPlantThere(float x, float y)
	{
		for (int i = 0; i < plants_created; i++)
		{
			// Get the bounds of the plant sprite
			FloatRect plantBounds = plants[i]->sprite.getGlobalBounds();
			// Check if the coordinates (x, y) are within the bounds of the plant sprite
			if (plantBounds.contains(x, y))
			{
				return true;
			}
		}
		return false;
	}

	void removePlant(float x, float y)
	{
		for (int i = 0; i < plants_created; i++)
		{
			// Get the bounds of the plant sprite
			FloatRect plantBounds = plants[i]->sprite.getGlobalBounds();
			// Check if the coordinates (x, y) are within the bounds of the plant sprite
			if (plantBounds.contains(x, y))
			{
				delete plants[i];
				for (int j = i; j < plants_created - 1; j++)
				{
					plants[j] = plants[j + 1];
				}
				plants_created--;
				Plant **temp = new Plant *[plants_created];
				for (int j = 0; j < plants_created; j++)
				{
					temp[j] = plants[j];
				}
				delete[] plants;
				plants = temp;
				return;
			}
		}
	}

	void draw(RenderWindow &window)
	{
		for (int i = 0; i < plants_created; i++)
		{
			plants[i]->draw(window);
			plants[i]->drawBullet(window);
		}
	}
	void move()
	{
		for (int i = 0; i < plants_created; i++)
		{
			plants[i]->move();
		}
	}
		void Serialize(ostream & stream)
		{
			stream << plants_created << endl;
			for (int i = 0; i < plants_created; i++)
			{
				plants[i]->Serialize(stream);
			}
		}
		void Deserialize(istream & stream)
		{
			int temp_plants_created;
			stream >> temp_plants_created;
			Plant **temp_plants = new Plant *[temp_plants_created];
			for (int i = 0; i < temp_plants_created; i++)
			{
				string type;
				string category;
				stream >> type;
				stream >> category;
				// create a new plant based on the type these are the types available: PeeShooter SunFlower Repeater SnowPea FumeShroom WallNut CherryBomb

				if (type == "PeeShooter")
				{
					temp_plants[i] = new PeeShooter(0, 0);
				}
				else if (type == "SunFlower")
				{
					temp_plants[i] = new SunFlower(0, 0);
				}
				else if (type == "Repeater")
				{
					temp_plants[i] = new Repeater(0, 0);
				}
				else if (type == "SnowPea")
				{
					temp_plants[i] = new SnowPea(0, 0);
				}
				else if (type == "FumeShroom")
				{
					temp_plants[i] = new FumeShroom(0, 0);
				}
				else if (type == "WallNut")
				{
					temp_plants[i] = new WallNut(0, 0);
				}
				else
				{
					temp_plants[i] = new CherryBomb(0, 0);
				}
				temp_plants[i]->Deserialize(stream);
			}
			for (int i = 0; i < plants_created; i++)
			{
				delete plants[i];
			}
			delete[] plants;
			plants_created = temp_plants_created;
			plants = temp_plants;
		}
	
	~PlantFactory()
	{
		for (int i = 0; i < plants_created; i++)
		{
			delete plants[i];
		}
		delete[] plants;
	}
};
