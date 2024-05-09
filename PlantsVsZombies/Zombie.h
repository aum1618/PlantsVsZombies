#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
// #include"../SFML/Images/"
using namespace sf;
using namespace std;
#include "cordinates.h";

class Zombie
{
public:
	int health;
	float speed;
	bool isAlive;
	coordinates cordintes;
	Sprite sprite;
	Texture texture;
	Clock clock;
	Clock clock2;
	int numframes = 9;
	int frame = 0;
	bool shouldMove;
	Zombie(float x = 0, float y = 0)
	{
		health = 3;
		cordintes.x = x;
		cordintes.y = y;
		speed = 100;
		isAlive = true;
		texture.loadFromFile("./Images/zombie.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 100, 100));
		sprite.setPosition(x, y);
		shouldMove = true;
	}
	virtual void move()
	{
		if (clock2.getElapsedTime().asSeconds() > 5)
		{
			shouldMove = true;
			clock2.restart();
		}

		if (isAlive && shouldMove)
		{
			if (clock.getElapsedTime().asMilliseconds() > speed)
			{
				if (shouldMove)
				{
					frame++;
					cordintes.x -= 2;
					sprite.setPosition(cordintes.x, cordintes.y);
					sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));
					clock.restart();
					frame = frame % numframes;
					if (cordintes.x < 0)
					{
						isAlive = false;
					}
				}
			}
		}
		else
		{
			frame++;
			sprite.setTextureRect(IntRect(100 * (frame), 100, 100, 100));
			clock.restart();
			frame = frame % numframes;

			shouldMove = true;
		}
	}
	void draw(RenderWindow &window)
	{
		if (isAlive)
		{
			/*if (health == 2) {
				sprite.setTextureRect(IntRect(0, 30, 100, 70));
			}
			if (health == 1) {
				sprite.setTextureRect(IntRect(0, 60, 100, 30));
			}*/
			window.draw(sprite);
		}
	}
	// void checkWallNutCollision(Plant** plants, int numPlants) {
	//	for (int i = 0; i < numPlants; i++) {
	//		if (plants[i]->type == "WallNut") {
	//			FloatRect wallNutBounds = plants[i]->sprite.getGlobalBounds();
	//			if (wallNutBounds.intersects(sprite.getGlobalBounds())) {
	//				isMoving = false; // Adjust as needed
	//				plants[i]->health -= 20;
	//
	//				return;
	//			}
	//		}
	//	}
	// }
};

// class FootballZombie :public Zombie {
// public:
//	FootballZombie(float x = 0, float y = 0) {
//		health = 3;
//		cordintes.x = x;
//		cordintes.y = y;
//		speed = 4;
//		isAlive = true;
//		texture.loadFromFile("./Images/zombie.png");
//		texture.setSmooth(true);
//		sprite.setTexture(texture);
//		sprite.setTextureRect(IntRect(0, 0, 100, 100));
//		sprite.setPosition(x, y);
//	}
//	virtual void move() {
//		if (isAlive) {
//			if (clock.getElapsedTime().asSeconds() > 0.1) {
//				frame++;
//				cordintes.x -= speed;
//				sprite.setPosition(cordintes.x, cordintes.y);
//				sprite.setTextureRect(IntRect(100 * (
//					frame
//					), 0, 100, 100));
//				clock.restart();
//				frame = frame % numframes;
//				if (cordintes.x < 0) {
//					isAlive = false;
//				}
//			}
//		}
//	}
// };
//
// class FlyingZombie :public Zombie {
// public:
//	FlyingZombie(float x = 0, float y = 0) {
//		health = 3;
//		cordintes.x = x;
//		cordintes.y = y;
//		speed = 4;
//		isAlive = true;
//		texture.loadFromFile("./Images/zombie.png");
//		texture.setSmooth(true);
//		sprite.setTexture(texture);
//		sprite.setTextureRect(IntRect(0, 0, 100, 100));
//		sprite.setPosition(x, y);
//	}
//	virtual void move() {
//		if (isAlive) {
//			if (clock.getElapsedTime().asSeconds() > 0.1) {
//				frame++;
//				cordintes.x -= speed;
//				sprite.setPosition(cordintes.x, cordintes.y);
//				sprite.setTextureRect(IntRect(100 * (
//					frame
//					), 0, 100, 100));
//				clock.restart();
//				frame = frame % numframes;
//				if (cordintes.x < 0) {
//					isAlive = false;
//				}
//			}
//		}
//	}
// };
//
// class DancingZombie :public Zombie {
// public:
//	DancingZombie(float x = 0, float y = 0) {
//		health = 3;
//		cordintes.x = x;
//		cordintes.y = y;
//		speed = 4;
//		isAlive = true;
//		texture.loadFromFile("./Images/zombie.png");
//		texture.setSmooth(true);
//		sprite.setTexture(texture);
//		sprite.setTextureRect(IntRect(0, 0, 100, 100));
//		sprite.setPosition(x, y);
//	}
//	virtual void move() {
//		if (isAlive) {
//			if (clock.getElapsedTime().asSeconds() > 0.1) {
//				frame++;
//				cordintes.x -= speed;
//				sprite.setPosition(cordintes.x, cordintes.y);
//				sprite.setTextureRect(IntRect(100 * (
//					frame
//					), 0, 100, 100));
//				clock.restart();
//				frame = frame % numframes;
//				if (cordintes.x < 0) {
//					isAlive = false;
//				}
//			}
//		}
//	}
// };
