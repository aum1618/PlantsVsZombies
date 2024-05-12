
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "cordinates.h";
#include "bullet.h";
#include "Sun.h";
#include <fstream>
using namespace sf;
using namespace std;

class Plant
{
public:
    bool isRolling;
    int health;
    int cost;
    coordinates position;
    Sprite sprite;
    Texture texture;
    Clock clock;
    int cooldown;
    int destination;
    string type;
    string category;
    bool isAlive;
    int numframes;
    int frame;
    int destinationy;
    bool freezeAll;
    bool hasFrozen;
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
        category = "Plant";
        isAlive = true;
        isRolling = true;
        destination = 0;
        freezeAll = false;
        hasFrozen = false;
        destinationy = 0;
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
        category = "Plant";
        destination = plant.destination;
        isRolling = plant.isRolling;
        freezeAll = plant.freezeAll;
        hasFrozen = plant.hasFrozen;
        destinationy = plant.destinationy;
    }

    virtual void draw(RenderWindow &window)
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
    virtual void move()
    {
    }
    virtual void Serialize(std::ostream &stream) const
    {
        stream << type << endl;
        stream << category << endl;
        stream << position.x << endl;
        stream << position.y << endl;
        stream << cooldown << endl;
        stream << destination << endl;
        stream << destinationy << endl;
        stream << freezeAll << endl;
        stream << hasFrozen << endl;
        stream << isRolling << endl;
        stream << health << endl;
        stream << cost << endl;
        stream << isAlive << endl;
        cout << frame << endl;
        cout << numframes << endl;
    }

    virtual void Deserialize(std::istream &stream)
    {
        stream >> position.x;
        stream >> position.y;
        sprite.setPosition(position.x, position.y);
        stream >> cooldown;
        stream >> destination;
        stream >> destinationy;
        stream >> freezeAll;
        stream >> hasFrozen;
        stream >> isRolling;
        stream >> health;
        stream >> cost;
        stream >> isAlive;
        stream >> frame;
        stream >> numframes;
        cout << "Plant Deserialized" << endl;
        cout << "Attributes: " << cooldown << " " << destination << " " << type << " " << category << " " << destinationy << " " << freezeAll << " " << hasFrozen << " " << isRolling << " " << health << " " << cost << endl;
    }
};

class Shooter : public Plant
{
public:
    BulletFactory bulletFactory;
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
        category = "Shooter";
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
        category = "Shooter";
    }
    virtual void Serialize(std::ostream &stream) const
    {
        Plant::Serialize(stream);
        bulletFactory.Serialize(stream);
    }
    virtual void Deserialize(std::istream &stream)
    {
        Plant::Deserialize(stream);
        bulletFactory.Deserialize(stream);
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
    virtual void updateBullet()
    {
        for (int i = 0; i < bulletFactory.bulletCount; i++)
        {

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
        category = "NonShooter";
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
        category = "NonShooter";
    }
};

class PeeShooter : public Shooter
{
public:
    Clock clock1;
    PeeShooter(float x = 0, float y = 0)
    {
        health = 100;
        cost = 50;
        cooldown = 2;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/peeshoot.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "PeeShooter";
        category = "Shooter";
        numframes = 20;
        frame = 0;
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
        category = "Shooter";
        clock1 = plant.clock1;
    }
    virtual void move()
    {
        if (clock1.getElapsedTime().asMilliseconds() > 20)
        {
            if (isAlive)
            {
                frame++;
                sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));

                frame = frame % numframes;
                clock1.restart();
            }
        }
    }
};
class SunFlower : public NonShooter
{
public:
    SunFactory sunFactory;
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
        category = "NonShooter";
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
        category = "NonShooter";
    }
    // make function to add sun there should only be 1 sun at a time

    virtual void Serialize(std::ostream &stream) const
    {
        Plant::Serialize(stream);
        sunFactory.Serialize(stream);
    }
    virtual void Deserialize(std::istream &stream)
    {
        Plant::Deserialize(stream);
        sunFactory.Deserialize(stream);
    }

    void fireBullet()
    {
        float elapsed1 = clock.getElapsedTime().asSeconds();
        if (elapsed1 >= cooldown)
        {
            int count = 0;
            for (int i = 0; i < sunFactory.suns_created; i++)
            {
                if (sunFactory.suns[i]->exist)
                {
                    count++;
                }
            }
            if (count >= 1)
            {
                clock.restart();
            }
            else
            {

                sunFactory.addSunFromPlant(position.x + 50, position.y - 25);
                clock.restart();
            }
        }
    }
    void updateBullet()
    {
        sunFactory.move();
    }
    void drawBullet(RenderWindow &window)
    {
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
        category = "Shooter";
    }
    Repeater(const Repeater &plant)
    {
        health = plant.health;
        cost = plant.cost;
        cooldown = plant.cooldown;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "Repeater";
        category = "Shooter";
    }
    void fireBullet()
    {
        float elapsed1 = clock.getElapsedTime().asSeconds();

        if (elapsed1 >= cooldown)
        {
            bulletFactory.removeNonExistantBullets();
            bulletFactory.addBullet(position.x + 90, position.y + 30);
            bulletFactory.addBullet(position.x + 130, position.y + 30);
            clock.restart();
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
        isRolling = true;
        destination = 0;
        category = "NonShooter";
    }
    WallNut(const WallNut &plant)
    {
        health = plant.health;
        cost = plant.cost;
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
        type = "WallNut";
        isRolling = plant.isRolling;
    }
    virtual void draw(RenderWindow &window)
    {
        window.draw(sprite);
    }
    virtual void move()
    {
        float speed = 5.0f; // Adjust the speed as desired
        // Move the WallNut towards its target x position
        if (destination < position.x)
        {
            destination += speed;
            sprite.setPosition(destination, position.y);
        }
    }
};
class SnowPea : public Shooter
{
public:
    Bomb *bomb;
    SnowPea(float x, float y)
    {
        health = 100;
        cost = 100;
        cooldown = 4;
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/snowpea.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);
        type = "SnowPea";
        destination = (rand() % 201) + 900;
        destinationy = (rand() % 501) + 200;
        int newY = -100;
        bomb = new Bomb(destination, newY);
        freezeAll = false;
        hasFrozen = false;
        category = "Shooter";
    }
    SnowPea(const SnowPea &plant)
    {
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
        hasFrozen = plant.hasFrozen;
        category = "Shooter";
    }

    virtual void Serialize(std::ostream &stream) const
    {
        Shooter::Serialize(stream);
        bomb->Serialize(stream);
    }

    virtual void Deserialize(std::istream &stream)
    {
        Shooter::Deserialize(stream);
        bomb->Deserialize(stream);
    }
    void fireBullet()
    {
        if (clock.getElapsedTime().asSeconds() > cooldown)
        {
            cout << "Bullet fired" << endl;
            bulletFactory.removeNonExistantBullets();
            bulletFactory.addBullet(position.x + 100, position.y + 30);
            if (!bomb->exist)
            {
                bomb->exist = true;
            }
            clock.restart();
        }
    }
    void updateBullet()
    {
        for (int i = 0; i < bulletFactory.bulletCount; i++)
        {

            if (bulletFactory.bullets[i]->exist)
            {
                bulletFactory.bullets[i]->move();
                if (bulletFactory.bullets[i]->reachedRightEdge(1300))
                {
                    bulletFactory.bullets[i]->exist = false;
                }
            }
        }
        if (bomb->exist)
        {
            bomb->move();
            if (bomb->reachedRightEdge(destinationy))
            {
                bomb->exist = false;
                freezeAll = true;
                cout << "Bomb reached destination" << endl;
            }
        }
    }
    void drawBullet(RenderWindow &window)
    {
        bulletFactory.drawBullets(window);
        if (bomb->exist)
            bomb->draw(window);
    }
};
class CherryBomb : public NonShooter
{
public:
    int radius;
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
        radius = 1;
        category = "NonShooter";
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
        radius = plant.radius;
        type = "CherryBomb";
        category = "NonShooter";
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
        category = "Shooter";
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
        category = "Shooter";
    }
};
