
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;

struct coordinates {
    float x;
    float y;
};

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
        bullet = new Bullet(x, y);
        position.x = x;
        position.y = y;
        texture.loadFromFile("./Images/plant.png");
        //image is 140x140 pixels scale it to 70x70
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.scale(0.5, 0.5);
        sprite.setPosition(position.x, position.y);

    }
    //create a copy constructor
    Plant(const Plant& plant) {
        //cout << "Plant copied" << endl;
        health = plant.health;
        damage = plant.damage;
        cost = plant.cost;
        cooldown = plant.cooldown;
        bullet = new Bullet(plant.bullet->position.x, plant.bullet->position.y);
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
            bullet->position.x = position.x;
            bullet->position.y = position.y;
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

void createBack(RenderWindow& window) {
    Image map_image;
    map_image.loadFromFile("./Images/background.png");

}

void createZombie(RenderWindow& window) {
    float speed = 0.1f;
    Image zombie_image;
    zombie_image.loadFromFile("./Images/zombieOnPlace.png");
    Texture zombieTexture;
    zombieTexture.loadFromImage(zombie_image);
    Sprite z_zombie;

    int fixedY = 400;
    z_zombie.setTexture(zombieTexture);
    z_zombie.setPosition(1920 - zombieTexture.getSize().x, fixedY);

    window.draw(z_zombie);
}

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

int main() {
    RenderWindow window(VideoMode(1920, 1080, 32), "Plants Vs Zombies");
    Image icon;
    //if (!icon.loadFromFile("./Images/shot.png")) {
    //    //return 1;
    //}
    //window.setIcon(32, 32, icon.getPixelsPtr());
    Texture map;
    map.loadFromFile("./Images/background.png");
    Sprite s_map;
    s_map.setTexture(map);
    s_map.setPosition(0, 0);
    window.setVerticalSyncEnabled(true);

    const int ROWS = 5;
    const int COLS = 9;

    bool FIELD_GAME_STATUS[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            FIELD_GAME_STATUS[i][j] = true;
        }
    }

    Clock timeMoney;
    Clock clock;

    int plants_created = 0;

    Plant** plants;
    plants = new Plant * [plants_created];


    while (window.isOpen()) {
        //float time = clock.getElapsedTime().asMicroseconds();
        //float moneyTime = timeMoney.getElapsedTime().asSeconds();

        //clock.restart();
        //time = time / 800;

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
        window.clear();
        window.draw(s_map);
        // Draw the background
        //createBack(window);

        // Draw the plants
        for (int i = 0; i < plants_created; i++) {
            plants[i]->draw(window);
            plants[i]->drawBullet(window);

        }




        createZombie(window);

        window.display();
    }
    return 0;
}
