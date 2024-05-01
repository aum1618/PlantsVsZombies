
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Plant.h"
#include "Zombie.h"
using namespace sf;
using namespace std;


int main() {
    srand(time(0));
    RenderWindow window(VideoMode(1280, 720, 32), "Plants Vs Zombies");
    Image icon;
    if (!icon.loadFromFile("./Images/Icon.png")) {
        return 1;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());
    Texture map;
    map.loadFromFile("./Images/background.png");
    Sprite s_map;
    s_map.setTexture(map);
    s_map.setPosition(0, 0);
    window.setVerticalSyncEnabled(true);


    int plants_created = 0;
    int noOfZombies = 10;

    Plant** plants;
    plants = new Plant * [plants_created];
    Zombie** zombies = new Zombie * [noOfZombies];
    for (int i = 0; i < noOfZombies; i++) {
        int newX = (1280) + (rand() % 1000);
        int newY = (rand() % 700) -140;
        zombies[i] = new Zombie(newX,newY);
    }

    while (window.isOpen()) {


        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                // Get the mouse click position
                coordinates clickPosition;
                clickPosition.x = event.mouseButton.x;
                clickPosition.y = event.mouseButton.y;

                plants = addPlants(plants, plants_created, clickPosition.x, clickPosition.y);


            }
        }
        for (int i = 0; i < plants_created; i++) {
            if (plants[i]->clock.getElapsedTime().asSeconds() > plants[i]->cooldown) {

                plants[i]->fireBullet();
                plants[i]->clock.restart();
            }
        }
        for (int i = 0; i < plants_created; i++) {
            plants[i]->updateBullet();
        }
        for (int i = 0; i < noOfZombies; i++) {
            zombies[i]->move();
        }
        window.clear();
        window.draw(s_map);
        for (int i = 0; i < noOfZombies; i++) {
            zombies[i]->draw(window);
        }

        for (int i = 0; i < plants_created; i++) {
            plants[i]->draw(window);
            plants[i]->drawBullet(window);

        }
        window.display();
    }
    return 0;
}
