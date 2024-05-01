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
	Zombie(float x = 0, float y = 0) {
		health = 3;
		cordintes.x = x;
		cordintes.y = y;
		speed = 2;
isAlive = true;
		texture.loadFromFile("./Images/zombieOnPlace.png");
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
	}
	void move() {
		if (isAlive) {
			if (clock.getElapsedTime().asSeconds() > 0.1) {

				cordintes.x -= speed;
				sprite.setPosition(cordintes.x, cordintes.y);
				clock.restart();
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

