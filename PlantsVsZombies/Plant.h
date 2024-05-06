
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "cordinates.h";
#include "bullet.h";
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
Bullet *bullet;
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
        bullet = nullptr;
        cooldown = 1;
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
bullet = plant.bullet;
		cooldown = plant.cooldown;
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
    virtual void drawBullet(RenderWindow& window) {};
};

class Shooter : public Plant
{
public:

    Shooter(float x=0, float y=0)
    {
        health = 100;
        cost = 50;
        cooldown = 1;
        bullet = new Bullet(x, y);
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/plant.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
    }
    Shooter(const Shooter& plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        bullet = new Bullet(*plant.bullet);
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
    }
    void fireBullet()
    {
        if (!bullet->exist)
        {
            bullet->exist = true;
            bullet->position.x = position.x;
            bullet->position.y = position.y;
            bullet->direction = false; // Bullets move left
        }
    }
    void updateBullet()
    {
        if (bullet->exist)
        {
            bullet->move();
            if (bullet->reachedRightEdge(1920))
            {
                bullet->exist = false;
            }
        }
    }
    void drawBullet(RenderWindow& window)
    {
        if (bullet->exist)
        {
            bullet->draw(window);
        }
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
    }
    NonShooter(const NonShooter& plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
    }

};

class PeeShooter : public Shooter
{
public:
    PeeShooter(float x=0, float y=0)
    {
        health = 100;
        cost = 100;
        cooldown = 2;
        bullet = new Bullet(x, y);
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/plant.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
    }
    PeeShooter(const PeeShooter &plant)
    {
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        bullet = new Bullet(*plant.bullet);
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
    }
};
class SunFlower : public NonShooter
{
public:
    SunFlower(float x, float y)
    {
        health = 100;
        cost = 100;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/sunflower.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
    }
    SunFlower(const SunFlower &plant)
    {
        health = plant.health;
        cost = plant.cost;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
    }
};
class Repeater : public Shooter
{
public:
    Repeater(float x, float y)
    {
        health = 100;
        cost = 200;
        cooldown = 1;
        bullet = new Bullet(x, y);
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/repeater.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
    }
    Repeater(const Repeater &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        bullet = new Bullet(*plant.bullet);
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
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
    }
};
class SnowPea : public Shooter
{
public:
    SnowPea(float x, float y)
    {
        health = 100;
        cost = 200;
        cooldown = 1;
         bullet = new Bullet(x, y);
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/snowpea.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
    }
    SnowPea(const SnowPea &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        bullet = new Bullet(*plant.bullet);
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
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
         bullet = new Bullet(x, y);
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/fumeshroom.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
    }
    FumeShroom(const FumeShroom &plant)
    {
        // cout << "Plant copied" << endl;
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        bullet = new Bullet(*plant.bullet);
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
    }
};

