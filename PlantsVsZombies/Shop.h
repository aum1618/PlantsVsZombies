#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;
using namespace std;
#include "cordinates.h";

struct Shop {
	coordinates cordinates;
	Sprite sprite;
	Texture texture;

	Shop() {
		cordinates.x = 0;
		cordinates.y = 0;
		texture.loadFromFile("./Images/shop.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
	}
	void draw(RenderWindow& window) {
		window.draw(sprite);
	}
};