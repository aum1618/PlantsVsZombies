
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "cordinates.h";
#include <fstream>;
using namespace sf;
using namespace std;


class Bullet
{
public:
    int damage;
    int speed;
    bool exist;
    bool direction; // true - right, false - left
    coordinates position;
    Sprite sprite;
    Texture texture;
    Clock clock;
    Bullet(float x = 0, float y = 0)
    {
        damage = 1;
        speed = 5;
        exist = false;
        direction = true;
        texture.loadFromFile("./Images/ProjectilePea.png");
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        sprite.rotate(90);
        sprite.setPosition(x, y);
        position.x = x;
        position.y = y;
    }
    Bullet(const Bullet &bullet)
    {
        damage = bullet.damage;
        speed = bullet.speed;
        exist = bullet.exist;
        direction = bullet.direction;
        texture = bullet.texture;
        sprite = bullet.sprite;
        clock = bullet.clock;
        position.x = bullet.position.x;
        position.y = bullet.position.y;
    }

    void Serialize(std::ostream& stream) const {
        stream << damage << endl;
        stream << speed << endl;
        stream << exist << endl;
        stream << direction << endl;
        stream << position.x << endl;
        stream << position.y << endl;
    }
void Deserialize(std::istream& stream) {
        stream >> damage;
        stream >> speed;
        stream >> exist;
        stream >> direction;
        stream >> position.x;
        stream >> position.y;
        sprite.setPosition(position.x, position.y);
	}

    void move()
    {
        if (clock.getElapsedTime().asMicroseconds() > 2)
        {
            clock.restart();

            if (direction)
            {
                position.x -= speed;
            }
            else
            {
                position.x += speed;
            }
            sprite.setPosition(position.x, position.y);
        }
    }
    void draw(RenderWindow &window)
    {
        window.draw(sprite);
    }
    bool reachedRightEdge(int windowWidth)
    {
        return position.x >= windowWidth;
    }
};

class Bomb : public Bullet
{
public:
    Bomb(float x = 0, float y = 0) : Bullet(x, y)
    {
        direction = false;
        texture.loadFromFile("./Images/ProjectileSnowPea.png");
        sprite.setTexture(texture);
        sprite.rotate(180);
    }
    Bomb(const Bomb &bomb)
    {
        damage = bomb.damage;
        speed = bomb.speed;
        exist = bomb.exist;
        direction = bomb.direction;
        texture = bomb.texture;
        sprite = bomb.sprite;
        clock = bomb.clock;
        position.x = bomb.position.x;
        position.y = bomb.position.y;
    }
    void move()
    {
        if (clock.getElapsedTime().asMicroseconds() > 2)
        {
            clock.restart();
            if (direction)
            {
                position.y -= speed;
            }
            else
            {
                position.y += speed;
            }
            sprite.setPosition(position.x, position.y);
        }
    }
    void draw(RenderWindow &window)
    {
        window.draw(sprite);
    }
    bool reachedRightEdge(int windowWidth)
    {
        return position.y >= windowWidth;
    }
};

class BulletFactory
{
public:
    Bullet **bullets;
    int bulletCount;
    BulletFactory(int count = 0)
    {
        bulletCount = count;
        bullets = new Bullet *[bulletCount];
        for (int i = 0; i < bulletCount; i++)
        {
            bullets[i] = new Bullet();
        }
    }
    BulletFactory(const BulletFactory &bulletFactory)
    {
        bulletCount = bulletFactory.bulletCount;
        bullets = new Bullet *[bulletCount];
        for (int i = 0; i < bulletCount; i++)
        {
            bullets[i] = new Bullet(*bulletFactory.bullets[i]);
        }
    }
    void addBullet(float x, float y)
    {
        Bullet **temp = new Bullet *[bulletCount + 1];
        for (int i = 0; i < bulletCount; i++)
        {
            temp[i] = bullets[i];
        }
        temp[bulletCount] = new Bullet(x, y);
        temp[bulletCount]->exist = true;
        temp[bulletCount]->direction = false;
        delete[] bullets;
        bullets = temp;
        bulletCount++;
    }
    void moveBullets()
    {
        for (int i = 0; i < bulletCount; i++)
        {
            if (bullets[i]->exist)
            {
                bullets[i]->move();
            }
        }
    }
    void drawBullets(RenderWindow &window)
    {
        for (int i = 0; i < bulletCount; i++)
        {
            if (bullets[i]->exist)
            {
                bullets[i]->draw(window);
            }
        }
    }
    void removeNonExistantBullets()
    {
        Bullet **temp = new Bullet *[bulletCount];
        int j = 0;
        for (int i = 0; i < bulletCount; i++)
        {
            if (bullets[i]->exist)
            {
                temp[j] = bullets[i];
                j++;
            }
            else
            {
                delete bullets[i];
            }
        }
        delete[] bullets;
        bullets = temp;
        bulletCount = j;
    }


    void Serialize(std::ostream& stream) const {
        stream << bulletCount << endl;
        for (int i = 0; i < bulletCount; i++)
        {
            bullets[i]->Serialize(stream);
        }
    }

    void Deserialize(std::istream& stream) {
        int temp_bulletCount;
        stream >> temp_bulletCount;
        Bullet **temp_bullets = new Bullet *[temp_bulletCount];
        for (int i = 0; i < temp_bulletCount; i++) {
        temp_bullets[i] = new Bullet();
	        temp_bullets[i]->Deserialize(stream);
        }
        for (int i = 0; i < bulletCount; i++) {
        delete bullets[i];
        }
        delete[] bullets;
        bulletCount = temp_bulletCount;
        bullets = temp_bullets;
    }

    ~BulletFactory()
    {
        for (int i = 0; i < bulletCount; i++)
        {
            delete bullets[i];
        }
        delete[] bullets;
    }
};
