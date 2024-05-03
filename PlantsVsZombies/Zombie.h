#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
//#include"../SFML/Images/"
using namespace sf;
using namespace std;
#include "cordinates.h";

struct Zombie {
	int health;
	float speed;
	bool isAlive;
	coordinates cordintes;
	Sprite sprite;
	Texture texture;
	Clock clock;
	int numframes = 5;
	int frame = 0;
	Zombie(float x = 0, float y = 0) {
		health = 3;
		cordintes.x = x;
		cordintes.y = y;
		speed = 4;
		isAlive = true;
		texture.loadFromFile("./Images/zombie.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 100, 100));
		sprite.setPosition(x, y);
	}
	void move() {
		if (isAlive) {
			if (clock.getElapsedTime().asSeconds() > 0.1) {
				frame++;
				cordintes.x -= speed;
				sprite.setPosition(cordintes.x, cordintes.y);
				sprite.setTextureRect(IntRect(100 *(
					frame
					), 0, 100, 100));
				clock.restart();
				frame=frame%numframes;
				if (cordintes.x < 0) {
					isAlive = false;
				}
			}
		}
	}
	void draw(RenderWindow& window) {
		if (isAlive) {
			window.draw(sprite);
		}
	}
};

