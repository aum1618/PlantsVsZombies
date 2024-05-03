
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include "Plant.h"
#include "Zombie.h"
using namespace sf;
using namespace std;


bool isPlantThere(Plant** plants, int plants_created, float x, float y) {
    for (int i = 0; i < plants_created; i++) {
        if (plants[i]->position.x == x && plants[i]->position.y == y) {
			return true;
		}
	}
	return false;
}


int main() {
    srand(time(0));
    const int GAME_ROWS = 9;
    const int GAME_COLS = 13;
    const int CELL_SIZE = 100;
    const int GAME_WIDTH = GAME_COLS * CELL_SIZE;
    const int GAME_HEIGHT = GAME_ROWS * CELL_SIZE;
    RenderWindow window(VideoMode(GAME_WIDTH, GAME_HEIGHT, 32), "Plants Vs Zombies");
    Image icon;
    if (!icon.loadFromFile("./Images/Icon.png")) {
        return 1;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());
    Texture map;
    map.loadFromFile("./Images/background.png");
    map.setRepeated(true);
    Sprite s_map;
    s_map.setTexture(map);
    s_map.setTextureRect(IntRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
    s_map.setScale(1.0f, 1.0f);
    s_map.setPosition(0, 0);
    window.setVerticalSyncEnabled(true);


    int plants_created = 0;
    int noOfZombies = 20;

    Plant** plants;
    plants = new Plant * [plants_created];
    Zombie** zombies = new Zombie * [noOfZombies];
    for (int i = 0; i < noOfZombies; i++) {
        int newX = (rand() % 1001) + 1300;  // Generates random number between 1300 and 2300
        int newY = (rand() % 899);          // Generates random number between 0 and 900

        // Make newX and newY multiples of 100
        newX = newX / 100 * 100;
        newY = newY / 100 * 100;
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
                clickPosition.x=floor(clickPosition.x / 100.0f) * 100.0f;
                clickPosition.y=floor(clickPosition.y / 100.0f) * 100.0f;

                if (!isPlantThere(plants, plants_created, clickPosition.x, clickPosition.y)) {
                plants = addPlants(plants, plants_created, clickPosition.x, clickPosition.y);
				}


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
