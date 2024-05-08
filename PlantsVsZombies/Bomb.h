#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "cordinates.h";
using namespace sf;
using namespace std;



class Bomb {
public:
    int damage;
    int speed;
    bool exist;
    bool direction; //true - right, false - left
    coordinates position;
    Sprite sprite;
    Texture texture;
    Clock clock;
    Bomb(float x = 0, float y = 0) {
        damage = 1;
        speed = 5;
        exist = false;
        direction = false;

        texture.loadFromFile("./Images/shot.png");
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        sprite.rotate(180);
        sprite.setPosition(x, y);
        position.x = x;
        position.y = y;
    }
    Bomb(const Bomb& bomb) {
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
    void move() {
        if (clock.getElapsedTime().asMicroseconds() > 2) {
            clock.restart();

            if (direction) {
                // Move up
                position.y -= speed;
            }
            else {
                // Move Down
                position.y += speed;
            }
            sprite.setPosition(position.x, position.y);
        }
    }
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
    // Method to check if bullet reached the right edge
    bool reachedRightEdge(int windowWidth) {
        return position.y >= windowWidth;
    }
};
