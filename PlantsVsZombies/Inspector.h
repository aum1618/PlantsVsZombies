#pragma once
#include <SFML/Window/Cursor.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include "PlantFactory.h"
#include "ZombieFactory.h"
#include "Sun.h"
#include "Cursor.h"
#include "Shop.h"
#include "LawnMowerFactory.h"
using namespace sf;
using namespace std;

class Inspector
{
public:
	void collectSun(coordinates& clickPosition, SunFactory& sunFactory, int& currency, PlantFactory& plantFactory) {
        if (sunFactory.isSunThere(clickPosition.x, clickPosition.y))
        {
            sunFactory.moveSunToOrigin(clickPosition.x, clickPosition.y);
            currency += 25;
            cout << "Currency: " << currency << endl;
        }
        for (int i = 0; i < plantFactory.plants_created; i++)
        {
            if (plantFactory.plants[i]->type == "SunFlower")
            {
                SunFlower* sunFlower = (SunFlower*)(plantFactory.plants[i]);

                if (sunFlower->sunFactory.isSunThere(clickPosition.x, clickPosition.y))
                {
                    sunFlower->sunFactory.restartClock();
                    sunFlower->sunFactory.moveSunToOrigin(clickPosition.x, clickPosition.y);
                    currency += 25;
                    cout << "Currency: " << currency << endl;
                }
            }
        }
	}
    void addPlantOnClick(coordinates& clickPosition ,int& currency,PlantFactory& plantFactory, GameCursor& cursor) {
        if (!plantFactory.isPlantThere(clickPosition.x, clickPosition.y))
        {
            if (clickPosition.y >= 200 && clickPosition.y <= 700 && clickPosition.x >= 200 && clickPosition.x <= 1100 && cursor.getCurrentCursor() != "default")
            {
                if (cursor.getCurrentCursor() == "peashooter" && currency >= 50)
                {
                    plantFactory.createPlant(clickPosition.x, clickPosition.y, cursor.getCurrentCursor());
                    currency -= 50;
                    cout << "Currency is: " << currency << endl;
                }
                else if (cursor.getCurrentCursor() == "repeater" && currency >= 200)
                {
                    plantFactory.createPlant(clickPosition.x, clickPosition.y, cursor.getCurrentCursor());
                    currency -= 200;
                    cout << "Currency is: " << currency << endl;
                }
                else if (cursor.getCurrentCursor() == "snowpea" && currency >= 100)
                {
                    plantFactory.createPlant(clickPosition.x, clickPosition.y, cursor.getCurrentCursor());
                    currency -= 100;
                    cout << "Currency is: " << currency << endl;
                }
                else if (cursor.getCurrentCursor() == "fumeshroom" && currency >= 75)
                {
                    plantFactory.createPlant(clickPosition.x, clickPosition.y, cursor.getCurrentCursor());
                    currency -= 75;
                    cout << "Currency is: " << currency << endl;
                }
                else if (cursor.getCurrentCursor() == "wallnut" && currency >= 50)
                {
                    plantFactory.createPlant(clickPosition.x, clickPosition.y, cursor.getCurrentCursor());
                    currency -= 50;
                    cout << "Currency is: " << currency << endl;
                }
                else if (cursor.getCurrentCursor() == "cherrybomb" && currency >= 150)
                {
                    plantFactory.createPlant(clickPosition.x, clickPosition.y, cursor.getCurrentCursor());
                    currency -= 150;
                    cout << "Currency is: " << currency << endl;
                }
                else if (cursor.getCurrentCursor() == "sunflower" && currency >= 100)
                {
                    plantFactory.createPlant(clickPosition.x, clickPosition.y, cursor.getCurrentCursor());
                    currency -= 100;
                    cout << "Currency is: " << currency << endl;
                }
            }
        }
        if (cursor.getCurrentCursor() == "shovel" && plantFactory.isPlantThere(clickPosition.x, clickPosition.y))
        {
            plantFactory.removePlant(clickPosition.x, clickPosition.y);
        }
    }

    void checkLawnmoverCollision(LawnMowerFactory& lawnMowerFactory,ZombieFactory& zombieFactory) {
        for (int i = 0; i < lawnMowerFactory.lawnmowers_created; i++)
        {
            if (lawnMowerFactory.lawnmowers[i]->exist)
            {
                for (int j = 0; j < zombieFactory.zombies_created; j++)
                {
                    if (zombieFactory.zombies[j]->isAlive)
                    {
                        FloatRect lawnmowerBounds = lawnMowerFactory.lawnmowers[i]->sprite.getGlobalBounds();
                        FloatRect zombieBounds = zombieFactory.zombies[j]->sprite.getGlobalBounds();
                        if (lawnmowerBounds.intersects(zombieBounds))
                        {
                            zombieFactory.zombies[j]->isAlive = false;
                            lawnMowerFactory.lawnmowers[i]->shouldMove = true;
                        }
                    }
                }
            }
        }

    }

    void checkPlantZombieBulletCollision(PlantFactory& plantFactory, ZombieFactory& zombieFactory){
        for (int i = 0; i < plantFactory.plants_created; i++)
        { 
                plantFactory.plants[i]->fireBullet();
                plantFactory.plants[i]->updateBullet();
            
            //snowpea bomb collision
            if (plantFactory.plants[i]->type == "SnowPea")
            {
             SnowPea* snowPea = (SnowPea*)(plantFactory.plants[i]);

                if (snowPea->freezeAll && !snowPea->hasFrozen)
                {
                    int tempx = snowPea->destination / 100 * 100;
                    int tempy = snowPea->destinationy / 100 * 100;
                    zombieFactory.freezeZombies(tempx - 100, tempy - 100);
                    snowPea->hasFrozen = true;
                }
            }
            //cherry bomb blast collision
            if (plantFactory.plants[i]->type == "CherryBomb")
            {
                if (plantFactory.plants[i]->clock.getElapsedTime().asSeconds() >= plantFactory.plants[i]->cooldown)
                {
                    zombieFactory.deleteZombiesInRect(plantFactory.plants[i]->position.x - 100, plantFactory.plants[i]->position.y - 100);
                    plantFactory.plants[i]->health = 0;
                }
            }

            // Check for collision with zombies
            for (int j = 0; j < zombieFactory.zombies_created; j++)
            {
                if (plantFactory.plants[i]->category=="Shooter") {
                    Shooter* shooter = (Shooter*)(plantFactory.plants[i]);
                    for (int k = 0; k < shooter->bulletFactory.bulletCount; k++)
                    {

                        if (shooter->bulletFactory.bullets[k]->exist && zombieFactory.zombies[j]->isAlive)
                        {
                            FloatRect bulletBounds = shooter->bulletFactory.bullets[k]->sprite.getGlobalBounds();
                            FloatRect zombieBounds = zombieFactory.zombies[j]->sprite.getGlobalBounds();

                            if (bulletBounds.intersects(zombieBounds))
                            {
                                cout << "Bullet hit the zombie" << endl;
                                // Bullet hits the zombie
                                zombieFactory.zombies[j]->health -= shooter->bulletFactory.bullets[k]->damage;
                                if (shooter->type == "SnowPea")
                                {

                                    zombieFactory.zombies[j]->speed += 150;
                                }
                                if (zombieFactory.zombies[j]->health == 0)
                                {
                                    zombieFactory.zombies[j]->isAlive = false;
                                }
                                shooter->bulletFactory.bullets[k]->exist = false;
                            }
                        }
                    }
                }
                FloatRect wallNutBounds = plantFactory.plants[i]->sprite.getGlobalBounds();
                FloatRect zombieBounds = zombieFactory.zombies[j]->sprite.getGlobalBounds();
                if (wallNutBounds.intersects(zombieBounds))
                {
                    if (zombieFactory.zombies[j]->type != "flying")
                    {
                        if (zombieFactory.zombies[j]->shouldMove) {
                            zombieFactory.zombies[j]->clock2.restart();
                        }
                        zombieFactory.zombies[j]->shouldMove = false;
                        plantFactory.plants[i]->health -= 1;
                        if (plantFactory.plants[i]->health <= 0) {
                            zombieFactory.zombies[j]->shouldMove = true;

                        }
                    }

                }

            }
            if (plantFactory.plants[i]->health <= 0) {
                plantFactory.removePlant(plantFactory.plants[i]->position.x, plantFactory.plants[i]->position.y);
            }

        }
    }
    
};
