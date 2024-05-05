#include <SFML/Window/Cursor.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include "PlantFactory.h"
#include "ZombieFactory.h"
#include "Cursor.h"
#include "Shop.h"
using namespace sf;
using namespace std;


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


    GameCursor cursor;
    PlantFactory plantFactory;
    Shop sh;
    
   ZombieFactory zombieFactory(20);

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

                cursor.renderCursor(clickPosition);
                if (!plantFactory.isPlantThere( clickPosition.x, clickPosition.y)) {
                    if(clickPosition.y>100)
                    plantFactory.createPlant(clickPosition.x, clickPosition.y);
				}
            }
        }
        for (int i = 0; i < plantFactory.plants_created; i++) {
            if (plantFactory.plants[i]->clock.getElapsedTime().asSeconds() > plantFactory.plants[i]->cooldown) {
                plantFactory.plants[i]->fireBullet();
                plantFactory.plants[i]->clock.restart();
            }
        }
        for (int i = 0; i < plantFactory.plants_created; i++) {
            plantFactory.plants[i]->updateBullet();
        }
        for (int i = 0; i < zombieFactory.zombies_created; i++) {
            zombieFactory.zombies[i]->move();
        }  
        for (int i = 0; i < plantFactory.plants_created; i++) {
            if (plantFactory.plants[i]->clock.getElapsedTime().asSeconds() > plantFactory.plants[i]->cooldown) {
                plantFactory.plants[i]->fireBullet();
                plantFactory.plants[i]->clock.restart();
            }
            plantFactory.plants[i]->updateBullet();

            // Check for collision with zombies
            for (int j = 0; j < zombieFactory.zombies_created; j++) {
                if (plantFactory.plants[i]->bullet->exist && zombieFactory.zombies[j]->isAlive) {
                    FloatRect bulletBounds =plantFactory.plants[i]->bullet->sprite.getGlobalBounds();
                    FloatRect zombieBounds = zombieFactory.zombies[j]->sprite.getGlobalBounds();

                    if (bulletBounds.intersects(zombieBounds)) {
                        // Bullet hits the zombie
                        zombieFactory.zombies[j]->health -= plantFactory.plants[i]->damage;
                        if (zombieFactory.zombies[j]->health <= 0) {
                            // Zombie is killed
                            zombieFactory.zombies[j]->isAlive = false;
                        }
                        // Remove the bullet
                        plantFactory.plants[i]->bullet->exist = false;
                    }
                }
            }
        }
        window.clear();
        window.draw(s_map);
        sh.draw(window);
        for (int i = 0; i < zombieFactory.zombies_created; i++) {
            zombieFactory.zombies[i]->draw(window);
        }

        for (int i = 0; i < plantFactory.plants_created; i++) {
            plantFactory.plants[i]->draw(window);
            plantFactory.plants[i]->drawBullet(window);

        }
        cursor.applyCursor(window);
        window.display();
    }
    return 0;
}
