#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "cordinates.h"
using namespace sf;
using namespace std;

class LawnMower {
public:
	coordinates position;
	Sprite sprite;
	Texture texture;
	float speed;
	bool shouldMove;
	bool exist;
	Clock clock;
	LawnMower(float x = 0, float y = 0) {
		cout << "Creating lawnmower at (" << x << ", " << y << ")" << endl;
		texture.loadFromFile("./Images/lawnmover.png");

		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		position.x = x;
		position.y = y;
		speed = 15;
		exist = true;
		shouldMove = false;
	}
	LawnMower(const LawnMower& lawnmower) {
		texture = lawnmower.texture;
		sprite = lawnmower.sprite;
		position.x = lawnmower.position.x;
		position.y = lawnmower.position.y;
		speed = lawnmower.speed;
		exist = lawnmower.exist;
		clock = lawnmower.clock;
		shouldMove = lawnmower.shouldMove;
	}
	void move() {
		if (exist && shouldMove) {
			if (clock.getElapsedTime().asSeconds() > 0.1) {
				position.x += speed;
				sprite.setPosition(position.x, position.y);
				if (position.x > 1300) {
					exist = false;
				}
				clock.restart();
			}
		}
	}
	void draw(RenderWindow& window) {
		if (exist) {
			window.draw(sprite);
		}
	}


};

class LawnMowerFactory {
public:
	LawnMower** lawnmowers;
	int lawnmowers_created;
	LawnMowerFactory(int numLawnMowers = 0) {
		lawnmowers_created = numLawnMowers;
		lawnmowers = new LawnMower * [lawnmowers_created];
		for (int i = 0; i < lawnmowers_created; i++) {
			lawnmowers[i] = new LawnMower(100,(i+2)*100);
		}
	}
	bool isLawnMowerThere(float x, float y) {
		for (int i = 0; i < lawnmowers_created; i++) {
			// Get the bounds of the lawnmower sprite
			FloatRect lawnmowerBounds = lawnmowers[i]->sprite.getGlobalBounds();
			// Check if the coordinates (x, y) are within the bounds of the lawnmower sprite
			if (lawnmowerBounds.contains(x, y)) {
				return true;
			}
		}
		return false;
	}
	void draw(RenderWindow& window) {
		for (int i = 0; i < lawnmowers_created; i++) {
			lawnmowers[i]->draw(window);
		}
	}
	void move() {
		for (int i = 0; i < lawnmowers_created; i++) {
			lawnmowers[i]->move();
		}
	}

	void removeLawnMower(float x, float y) {
		for (int i = 0; i < lawnmowers_created; i++) {
			// Get the bounds of the lawnmower sprite
			FloatRect lawnmowerBounds = lawnmowers[i]->sprite.getGlobalBounds();
			// Check if the coordinates (x, y) are within the bounds of the lawnmower sprite
			if (lawnmowerBounds.contains(x, y)) {
				delete lawnmowers[i];
			}
		}
	}
};