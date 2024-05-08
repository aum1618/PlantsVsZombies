
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "cordinates.h";
#include "bullet.h";
#include "Sun.h";
#include "Bomb.h";
using namespace sf;
using namespace std;

class Plant
{
public:
    int health;
    int cost;
    coordinates position;
    Sprite sprite;
    Texture texture;
    Clock clock;
    int cooldown;
    BulletFactory bulletFactory;
    string type;
    Bomb* bomb;
    int destination;
    int destinationy;
    bool freezeAll;

    SunFactory sunFactory;
    Plant(float x = 0, float y = 0)
    {
        // cout << "Plant created" << endl;
        health = 100;
        cost = 50;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/plant.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        cooldown = 1;
        type = "Plant";
        bomb = nullptr;
    }
    // create a copy constructor
    Plant(const Plant &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        cooldown = plant.cooldown;
        type = "Plant";
        bomb = nullptr;
    }

    void draw(RenderWindow &window)
    {
        window.draw(sprite);
    }
    void changePosition(float x, float y)
    {
        position.x = x;
        position.y = y;
        sprite.setPosition(position.x, position.y);
    }
    virtual void fireBullet()
    {
    }
    virtual void updateBullet() {};
    virtual void drawBullet(RenderWindow &window) {};
};

class Shooter : public Plant
{
public:
    Shooter(float x = 0, float y = 0)
    {
        health = 100;
        cost = 50;
        cooldown = 1;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/plant.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "Shooter";
    }
    Shooter(const Shooter &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "Shooter";
    }
    void fireBullet()
    {
        if (clock.getElapsedTime().asSeconds() > cooldown)
        {
            cout << "Bullet fired" << endl;
            bulletFactory.removeNonExistantBullets();
            bulletFactory.addBullet(position.x + 100, position.y + 30);
            clock.restart();
        }
    }
    void updateBullet()
    {
        for (int i = 0; i < bulletFactory.bulletCount; i++) {

        if (bulletFactory.bullets[i]->exist)
        {
            bulletFactory.bullets[i]->move();
            if (bulletFactory.bullets[i]->reachedRightEdge(1300))
            {
                bulletFactory.bullets[i]->exist = false;
            }
        }
        }
    }
    void drawBullet(RenderWindow &window)
    {
        bulletFactory.drawBullets(window);
    }
};
class NonShooter : public Plant
{
public:
    NonShooter(float x = 0, float y = 0)
    {
        health = 100;
        cost = 50;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/plant.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "NonShooter";
    }
    NonShooter(const NonShooter &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "NonShooter";
    }
};

class PeeShooter : public Shooter
{
public:
    PeeShooter(float x = 0, float y = 0)
    {
        health = 100;
        cost = 100;
        cooldown = 2;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/plant.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "PeeShooter";
    }
    PeeShooter(const PeeShooter &plant)
    {
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "PeeShooter";
    }
};
class SunFlower : public NonShooter
{
public:
    SunFlower(float x, float y)
    {
        health = 100;
        cost = 100;
        cooldown = 10;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/sunflower.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "SunFlower";
    }
    SunFlower(const SunFlower &plant)
    {
        health = plant.health;
        cooldown = 10;
        cost = plant.cost;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "SunFlower";
    }
    //make function to add sun there should only be 1 sun at a time
    void fireBullet()
	{
		float elapsed1 = clock.getElapsedTime().asSeconds();
		if (elapsed1 >= cooldown)
		{
            int count=0;
            for (int i = 0; i < sunFactory.suns_created; i++)
			{
				if (sunFactory.suns[i]->exist)
				{
					count++;
				}
			}
            if (count >= 1) {
                clock.restart();
            }
            else {

			sunFactory.addSunFromPlant(position.x + 50, position.y - 25);
			clock.restart();
            }
		}
	}
    void updateBullet() {
        sunFactory.move();
	}
    void drawBullet(RenderWindow &window) {
        sunFactory.draw(window);
    }
};

class Repeater : public Shooter
{
public:
    Repeater(float x, float y)
    {
        health = 100;
        cost = 200;
        cooldown = 2;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/repeater.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "Repeater";
        
    }
    Repeater(const Repeater &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "Repeater";
    }
    void fireBullet() {
        float elapsed1 = clock.getElapsedTime().asSeconds();

        // Fire first bullet after base cooldown
        if (elapsed1 >= cooldown) {
            bulletFactory.removeNonExistantBullets();
            bulletFactory.addBullet(position.x + 90, position.y + 30);
            bulletFactory.addBullet(position.x + 130, position.y + 30);
            clock.restart();  // Restart timer for first bullet
        }

       
    }
   
};
class WallNut : public NonShooter
{
public:
    WallNut(float x, float y)
    {
        health = 100;
        cost = 50;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/wallnut.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "WallNut";
    }
    WallNut(const WallNut &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "WallNut";
    }
};
class SnowPea : public Shooter
{
public:

    SnowPea(float x, float y)
    {
        health = 100;
        cost = 200;
        cooldown = 4;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/snowpea.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "SnowPea";
        destination = (rand() % 201) + 900;  // Generates random number between 1300 and 2300
        destinationy = (rand() % 501) + 200;
        int newY = -100;          // Generates random number between 0 and 900
        bomb = new Bomb(destination, newY);
        freezeAll = false;
    }
    SnowPea(const SnowPea &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "SnowPea";
        destination = plant.destination;
        destinationy = plant.destinationy;
        bomb = new Bomb(*plant.bomb);
        freezeAll = plant.freezeAll;
    }
    void fireBullet()
    {
        if (clock.getElapsedTime().asSeconds() > cooldown)
        {
            cout << "Bullet fired" << endl;
            bulletFactory.removeNonExistantBullets();
            bulletFactory.addBullet(position.x + 100, position.y + 30);
            if (!bomb->exist) {
                bomb->exist = true;
            }
            clock.restart();
        }
    }
    void updateBullet()
    {
        for (int i = 0; i < bulletFactory.bulletCount; i++) {

            if (bulletFactory.bullets[i]->exist)
            {
                bulletFactory.bullets[i]->move();
                if (bulletFactory.bullets[i]->reachedRightEdge(1300))
                {
                    bulletFactory.bullets[i]->exist = false;
                }
            }
        }
        if (bomb->exist) {
            bomb->move();
            if (bomb->reachedRightEdge(destinationy)) {
                bomb->exist = false;
                freezeAll = true;
            }
        }
    }
    void drawBullet(RenderWindow& window)
    {
        bulletFactory.drawBullets(window);
        if(bomb->exist)
        bomb->draw(window);
    }

};
class CherryBomb : public NonShooter
{
public:
    CherryBomb(float x, float y)
    {
        health = 100;
        cost = 150;

        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/cherrybomb.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "CherryBomb";
    }
    CherryBomb(const CherryBomb &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "CherryBomb";
    }
};
class FumeShroom : public Shooter
{
public:
    FumeShroom(float x, float y)
    {
        health = 100;
        cost = 75;
        cooldown = 1;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/fumeshroom.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "FumeShroom";
    }
    FumeShroom(const FumeShroom &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "FumeShroom";
    }
};
