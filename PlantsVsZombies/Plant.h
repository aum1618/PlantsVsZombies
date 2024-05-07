
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "cordinates.h";
#include "bullet.h";
#include "Sun.h";
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
    string type;
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
        type = "Plant";
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
        type = "Plant";
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
        bullet = new Bullet(x + 100, y + 30);
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
        bullet = new Bullet(*plant.bullet);
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

            if (!bullet->exist)
            {
                bullet->exist = true;
                bullet->position.x = position.x + 100;
                bullet->position.y = position.y + 30;
                bullet->direction = false; // Bullets move left
            }
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
    void drawBullet(RenderWindow &window)
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
        bullet = new Bullet(x, y);
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
        bullet = new Bullet(*plant.bullet);
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
        cooldown = 3;
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
        cooldown = 3;
        cost = plant.cost;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "SunFlower";
    }
};

class Repeater : public Shooter
{
public:
    Bullet *bullet2;
    Clock clock2;
    Repeater(float x, float y)
    {
        health = 100;
        cost = 200;
        cooldown = 1;
        bullet = new Bullet(x, y);
        bullet2 = new Bullet(x, y);
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
        bullet = new Bullet(*plant.bullet);
        bullet2 = new Bullet(plant.position.x, plant.position.y);
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "Repeater";
        clock2 = plant.clock2;
    }
    void fireBullet()
    {
        if (clock.getElapsedTime().asSeconds() > cooldown)
        {

            if (!bullet->exist)
            {
                cout << "fired1\n";
                bullet->exist = true;
                bullet->position.x = position.x + 100;
                bullet->position.y = position.y + 30;
                bullet->direction = false; // Bullets move left
            }
            clock.restart();
        }
        if (clock2.getElapsedTime().asSeconds() > 1.5)
        {
            if (!bullet2->exist)
            {
                cout << "friend2\n"
                     << endl;
                bullet2->exist = true;
                bullet2->position.x = position.x + 100;
                bullet2->position.y = position.y + 30;
                bullet2->direction = false; // Bullets move left
            }
            clock2.restart();
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
        if (bullet2->exist)
        {
            bullet2->move();
            if (bullet2->reachedRightEdge(1920))
            {
                bullet2->exist = false;
            }
        }
    }
    void drawBullet(RenderWindow &window)
    {
        if (bullet->exist)
        {
            bullet->draw(window);
        }
        if (bullet2->exist)
        {
            bullet2->draw(window);
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
        cooldown = 1;
        bullet = new Bullet(x, y);
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/snowpea.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "SnowPea";
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
        type = "SnowPea";
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
        bullet = new Bullet(x, y);
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
        bullet = new Bullet(*plant.bullet);
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "FumeShroom";
    }
};
