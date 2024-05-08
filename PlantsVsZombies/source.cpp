#include <SFML/Window/Cursor.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include "PlantFactory.h"
#include "ZombieFactory.h"
#include "Sun.h"
#include "Cursor.h"
#include "Shop.h"
#include "LawnMowerFactory.h"
using namespace sf;
using namespace std;

int main()
{
    srand(time(0));
    const int GAME_ROWS = 9;
    const int GAME_COLS = 13;
    const int CELL_SIZE = 100;
    const int GAME_WIDTH = GAME_COLS * CELL_SIZE;
    const int GAME_HEIGHT = GAME_ROWS * CELL_SIZE;
    RenderWindow window(VideoMode(GAME_WIDTH, GAME_HEIGHT, 32), "Plants Vs Zombies");
    Image icon;
    if (!icon.loadFromFile("./Images/Icon.png"))
    {
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
    Texture grid;
    grid.loadFromFile("./Images/grid.png");
    Sprite s_grid;
    s_grid.setTexture(grid);
    s_grid.setPosition(200, 200);

    GameCursor cursor;
    Shop sh;

    PlantFactory plantFactory;
    ZombieFactory zombieFactory(20);
    SunFactory sunFactory(20);
    LawnMowerFactory lawnMowerFactory(5);

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                // Get the mouse click position
                coordinates clickPosition;
                clickPosition.x = event.mouseButton.x;
                clickPosition.y = event.mouseButton.y;

                cursor.renderCursor(clickPosition);
                if (sunFactory.isSunThere(clickPosition.x, clickPosition.y))
                {
                    sunFactory.moveSunToOrigin(clickPosition.x, clickPosition.y);
                }
                else
                {

                    if (!plantFactory.isPlantThere(clickPosition.x, clickPosition.y))
                    {

                        // limit it between 200 and 700 at y axis and 200 and 1100 at x axis
                        if (clickPosition.y >= 200 && clickPosition.y <= 700 && clickPosition.x >= 200 && clickPosition.x <= 1100 && cursor.getCurrentCursor() != "default")
                            plantFactory.createPlant(clickPosition.x, clickPosition.y, cursor.getCurrentCursor());
                    }
                    if (cursor.getCurrentCursor() == "shovel" && plantFactory.isPlantThere(clickPosition.x, clickPosition.y))
                    {
                        plantFactory.removePlant(clickPosition.x, clickPosition.y);
                    }
                }
            }
        }
        // check for collision of lawnmower with zombies. If collision occurs, kill the zombie and set the lawnmower to move

        for (int i = 0; i < lawnMowerFactory.lawnmowers_created; i++)
        {
            if (lawnMowerFactory.lawnmowers[i]->exist)
            {
                for (int j = 0; j < zombieFactory.zombies_created; j++)
                {
                    if (zombieFactory.zombies[j]->isAlive)
                    {
                        FloatRect lawnmowerBounds = lawnMowerFactory.lawnmowers[i]->sprite.getGlobalBounds();
                        FloatRect zombieBounds = zombieFactory.zombies[j]->sprite.getGlobalBounds();
                        if (lawnmowerBounds.intersects(zombieBounds))
                        {
                            zombieFactory.zombies[j]->isAlive = false;
                            lawnMowerFactory.lawnmowers[i]->shouldMove = true;
                        }
                    }
                }
            }
        }
        // Bullet creation and updatind logic

        for (int i = 0; i < plantFactory.plants_created; i++)

        {
                plantFactory.plants[i]->fireBullet();

                plantFactory.plants[i]->updateBullet();
                if (
                    plantFactory.plants[i]->bullet != nullptr)
                {

                    // Check for collision with zombies
                    for (int j = 0; j < zombieFactory.zombies_created; j++)
                    {
                        if (plantFactory.plants)
                            if (plantFactory.plants[i]->bullet->exist && zombieFactory.zombies[j]->isAlive)
                            {
                                FloatRect bulletBounds = plantFactory.plants[i]->bullet->sprite.getGlobalBounds();
                                FloatRect zombieBounds = zombieFactory.zombies[j]->sprite.getGlobalBounds();

                                if (bulletBounds.intersects(zombieBounds))
                                {
                                    // Bullet hits the zombie
                                    zombieFactory.zombies[j]->health -= plantFactory.plants[i]->bullet->damage;
                                    if (zombieFactory.zombies[j]->health <= 0)
                                    {
                                        // Zombie is killed
                                        zombieFactory.zombies[j]->isAlive = false;
                                    }
                                    // Remove the bullet
                                    plantFactory.plants[i]->bullet->exist = false;
                                }
                            }
                    }
                }
            }
        for (int i = 0; i < plantFactory.plants_created; i++)
        {
            for (int j = 0; j < zombieFactory.zombies_created; j++)
            {
                if (plantFactory.plants[i]->type == "CherryBomb") {
                    if (plantFactory.plants[i]->clock.getElapsedTime().asSeconds() >= plantFactory.plants[i]->cooldown) {
                        /*zombieFactory.killZombie(plantFactory.plants[i]->position.x + 100, plantFactory.plants[i]->position.y);
                        zombieFactory.killZombie(plantFactory.plants[i]->position.x - 100, plantFactory.plants[i]->position.y);
                        zombieFactory.killZombie(plantFactory.plants[i]->position.x, plantFactory.plants[i]->position.y+100);
                        zombieFactory.killZombie(plantFactory.plants[i]->position.x, plantFactory.plants[i]->position.y-100);
                        zombieFactory.killZombie(plantFactory.plants[i]->position.x + 100, plantFactory.plants[i]->position.y+100);
                        zombieFactory.killZombie(plantFactory.plants[i]->position.x + 100, plantFactory.plants[i]->position.y - 100);
                        zombieFactory.killZombie(plantFactory.plants[i]->position.x - 100, plantFactory.plants[i]->position.y + 100);
                        zombieFactory.killZombie(plantFactory.plants[i]->position.x - 100, plantFactory.plants[i]->position.y - 100);*/
                        zombieFactory.deleteZombiesInRect(plantFactory.plants[i]->position.x-100, plantFactory.plants[i]->position.y - 100, plantFactory.plants[i]->position.x + 100, plantFactory.plants[i]->position.y + 100);
                        plantFactory.plants[i]->health = 0;
                    }
                }
            }
        }
        for (int i = 0; i < zombieFactory.zombies_created; i++)
        {
            for (int j = 0; j < plantFactory.plants_created; j++)
            {
                    FloatRect wallNutBounds = plantFactory.plants[j]->sprite.getGlobalBounds();
                    FloatRect zombieBounds = zombieFactory.zombies[i]->sprite.getGlobalBounds();
                    cout << zombieBounds.height << zombieBounds.width << zombieBounds.left << zombieBounds.top << endl;
                    if (wallNutBounds.intersects(zombieBounds))
                    {
                        zombieFactory.zombies[i]->isMoving = false;
                        plantFactory.plants[j]->health -= 1;
                    }
                    if (plantFactory.plants[j]->health <= 0)
                        plantFactory.removePlant(plantFactory.plants[j]->position.x, plantFactory.plants[j]->position.y);
            }
        }

            sunFactory.move();
            lawnMowerFactory.move();
            for (int i = 0; i < zombieFactory.zombies_created; i++)
            {
                zombieFactory.zombies[i]->move();
            }

            window.clear();
            window.draw(s_map);
            window.draw(s_grid);
            for (int i = 0; i < zombieFactory.zombies_created; i++)
            {
                zombieFactory.zombies[i]->draw(window);
            }

            for (int i = 0; i < plantFactory.plants_created; i++)
            {
                plantFactory.plants[i]->draw(window);
                plantFactory.plants[i]->drawBullet(window);
            }
            lawnMowerFactory.draw(window);
            sunFactory.draw(window);
            sh.draw(window);
            cursor.applyCursor(window);
            window.display();
        }
        return 0;
    }
