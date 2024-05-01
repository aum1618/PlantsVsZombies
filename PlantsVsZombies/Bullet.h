
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "cordinates.h";
using namespace sf;
using namespace std;

class Bullet {
public:
    int damage;
    int speed;
    bool exist;
    bool direction; //true - right, false - left
    coordinates position;
    Sprite sprite;
    Texture texture;
    Clock clock;
    Bullet(float x = 0, float y = 0) {
        damage = 10;
        speed = 10;
        exist = false;
        direction = true;

        texture.loadFromFile("./Images/shot.png");
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        sprite.rotate(90);
        sprite.setPosition(x, y);
        position.x = x;
        position.y = y;
    }
    Bullet(const Bullet& bullet) {
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
    void move() {
        if (clock.getElapsedTime().asMicroseconds() > 2) {
            clock.restart();

            if (direction) {
                // Move right
                position.x -= speed;
            }
            else {
                // Move left
                position.x += speed;
            }
            sprite.setPosition(position.x, position.y);
        }
    }
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
    // Method to check if bullet reached the right edge
    bool reachedRightEdge(int windowWidth) {
        return position.x >= windowWidth;
    }
};