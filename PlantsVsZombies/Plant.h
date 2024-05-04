
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "cordinates.h";
#include "bullet.h";
using namespace sf;
using namespace std;



class Plant {
public:
    int health;
    int damage;
    int cost;
    int cooldown;
    Bullet* bullet;
    coordinates position;
    Sprite sprite;
    Texture texture;
    Clock clock;
    Plant(float x = 0, float y = 0) {
        //cout << "Plant created" << endl;
        health = 100;
        damage = 10;
        cost = 50;
        cooldown = 1;
        bullet = new Bullet(x+100, y+30);
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/plant.png");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 100, 100));
        sprite.setPosition(position.x, position.y);

    }
    //create a copy constructor
    Plant(const Plant& plant) {
        //cout << "Plant copied" << endl;
        health = plant.health;
        damage = plant.damage;
        cost = plant.cost;
        cooldown = plant.cooldown;
        bullet = new Bullet(*plant.bullet);
        position.x = plant.position.x;
        position.y = plant.position.y;
        texture = plant.texture;
        sprite = plant.sprite;
        clock = plant.clock;
    }
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
    void changePosition(float x, float y) {
        position.x = x;
        position.y = y;
        sprite.setPosition(position.x, position.y);
    }
    void fireBullet() {
        if (!bullet->exist) {
            bullet->exist = true;
            bullet->position.x = position.x+100;
            bullet->position.y = position.y+30;
            bullet->direction = false; // Bullets move left
        }
    }
    void updateBullet() {
        if (bullet->exist) {
            bullet->move();
            if (bullet->reachedRightEdge(1920)) {
                bullet->exist = false;
            }
        }
    }
    void drawBullet(RenderWindow& window) {
        if (bullet->exist) {
            bullet->draw(window);
        }
    }
};



Plant** addPlants(Plant** plantArray, int& size, float x, float y) {
    // Allocate memory for a larger array
    int newCapacity = size + 1;
    Plant** newArray;
    newArray = new Plant * [newCapacity];

    // Copy existing elements to the new array
    for (int i = 0; i < size; ++i) {
        newArray[i] = new Plant(*plantArray[i]);
    }

    // Deallocate memory for the old array
    delete[] plantArray;

    // Update plantArray to point to the new array
    newArray[size] = new Plant(x, y);

    // Update the size
    size++;
    return newArray;
}

