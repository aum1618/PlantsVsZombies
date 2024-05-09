#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
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
	bool isMoving;
	string type;
	bool hasSummoned;
	float targetY;
	Zombie(float x = 0, float y = 0)
	{
		health = 3;
		cordintes.x = x;
		cordintes.y = y;
		speed = 150;
		isAlive = true;
		texture.loadFromFile("./Images/zombie.png");
		texture.setSmooth(true);
		
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 100, 100));
		sprite.setPosition(x, y);
		shouldMove = true;
		isMoving = true;
		type="zombie";
hasSummoned = false;
targetY = cordintes.y;

	}
	//create copy constructor
Zombie(const Zombie &z)
	{
		health = z.health;
		speed = z.speed;
		isAlive = z.isAlive;
		cordintes.x = z.cordintes.x;
		cordintes.y = z.cordintes.y;
		texture = z.texture;
		sprite = z.sprite;
		clock = z.clock;
		clock2 = z.clock2;
		numframes = z.numframes;
		frame = z.frame;
		shouldMove = z.shouldMove;
		isMoving = z.isMoving;
		type = z.type;
		hasSummoned = z.hasSummoned;
		targetY = z.targetY;
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
				if (isMoving)
				{
					frame++;
					cordintes.x -= 2;
					sprite.setPosition(cordintes.x, cordintes.y);
					sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));
					// sprite.setScale(1.1, 1.1);
					clock.restart();
					frame = frame % numframes;
					if (cordintes.x < 0)
					{
						isAlive = false;
					}
				}
				else
				{
					frame++;
					sprite.setTextureRect(IntRect(100 * (frame), 100, 100, 100));
					clock.restart();
					frame = frame % numframes;

					isMoving = true;
				}
			}
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
	
};


class FootballZombie :public Zombie {
public:
	FootballZombie(float x = 0, float y = 0)
	{
		cout << "football zombie created at" << x<< y<<  endl;
		health = 6;
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
		isMoving = true;
		type="football";
		targetY = cordintes.y;
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
				if (isMoving)
				{
					frame++;
					if(targetY!=cordintes.y)
					{
						cout << "targetY: " << targetY << " cordintes.y: " << cordintes.y << endl;
						if (targetY > cordintes.y)
						{
							cordintes.y += 4;
						}
						else
						{
							cordintes.y -= 4;
						}
					}
					else {
						cout << "cordinates: " << cordintes.x << endl;

					cordintes.x -= 2;
					int random = rand() % 100;
					float newY = cordintes.y;
					if (random == 1)
					{
						if (cordintes.y != 200)

							newY = cordintes.y - 100;
						else {
							newY = cordintes.y + 100;
						}
					}
					else if (random == 2)
					{
						if (cordintes.y != 600)
							newY = cordintes.y + 100;
						else {
							newY = cordintes.y - 100;
						}
					}
					targetY = newY;

					}
					//randomly move the zombie from either up or down 100 on the y axis ....there is a 10% chance that it will move along the y axis  also if the zombies is at y =200 it will only move down and if it is at y=600 it will only move up

					
				}
				sprite.setPosition(cordintes.x, cordintes.y);
				sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));
				// sprite.setScale(1.1, 1.1);
				clock.restart();
				frame = frame % numframes;
				if (cordintes.x < 0)
				{
					isAlive = false;
				}
			}
			else
			{
				/*frame++;
				sprite.setTextureRect(IntRect(100 * (frame), 100, 100, 100));
				frame = frame % numframes;

				isMoving = true;*/
			}
		}
	}

	 void draw(RenderWindow& window)
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
 };

 class FlyingZombie :public Zombie {
 public:
	 FlyingZombie(float x = 0, float y = 0)
	 {
		 health = 3;
		 cordintes.x = x;
		 cordintes.y = y;
		 speed = 150;
		 isAlive = true;
		 texture.loadFromFile("./Images/zombie.png");
		 texture.setSmooth(true);
		 sprite.setTexture(texture);
		 sprite.setTextureRect(IntRect(0, 0, 100, 100));
		 sprite.setPosition(x, y);
		 shouldMove = true;
		 isMoving = true;
		 type="flying";
		 
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
				 if (isMoving)
				 {
					 frame++;
					 cordintes.x -= 2;
					 sprite.setPosition(cordintes.x, cordintes.y);
					 sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));
					 // sprite.setScale(1.1, 1.1);
					 clock.restart();
					 frame = frame % numframes;
					 if (cordintes.x < 0)
					 {
						 isAlive = false;
					 }
				 }
				 else
				 {
					 frame++;
					 sprite.setTextureRect(IntRect(100 * (frame), 100, 100, 100));
					 clock.restart();
					 frame = frame % numframes;

					 isMoving = true;
				 }
			 }
		 }
	 }
	 void draw(RenderWindow& window)
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
 };

 class DancingZombie :public Zombie {
 public:
	 DancingZombie(float x = 0, float y = 0)
	 {
		 health = 3;
		 cordintes.x = x;
		 cordintes.y = y;
		 speed = 150;
		 isAlive = true;
		 texture.loadFromFile("./Images/zombie.png");
		 texture.setSmooth(true);

		 sprite.setTexture(texture);
		 sprite.setTextureRect(IntRect(0, 0, 100, 100));
		 sprite.setPosition(x, y);
		 shouldMove = true;
		 isMoving = true;
		 type = "dancing";
		 targetY= cordintes.y;
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
				 if (isMoving)
				 {
					 frame++;
					 if (targetY != cordintes.y)
					 {
						 cout << "targetY: " << targetY << " cordintes.y: " << cordintes.y << endl;
						 if (targetY > cordintes.y)
						 {
							 cordintes.y += 2;
						 }
						 else
						 {
							 cordintes.y -= 2;
						 }
					 }
					 else {
						 cout << "cordinates: " << cordintes.x << endl;
						 int random = rand() % 100;
						 float newY = cordintes.y;
						 if (random == 1)
						 {
							 if (cordintes.y != 200)

								 newY = cordintes.y - 100;
							 else {
								 newY = cordintes.y + 100;
							 }
						 }
						 else if (random == 2)
						 {
							 if (cordintes.y != 600)
								 newY = cordintes.y + 100;
							 else {
								 newY = cordintes.y - 100;
							 }
						 }
						 targetY = newY;

					 }
					 cordintes.x -= 2;

					 //randomly move the zombie from either up or down 100 on the y axis ....there is a 10% chance that it will move along the y axis  also if the zombies is at y =200 it will only move down and if it is at y=600 it will only move up


				 }
				 sprite.setPosition(cordintes.x, cordintes.y);
				 sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));
				 // sprite.setScale(1.1, 1.1);
				 clock.restart();
				 frame = frame % numframes;
				 if (cordintes.x < 0)
				 {
					 isAlive = false;
				 }
			 }
			 else
			 {
				 /*frame++;
				 sprite.setTextureRect(IntRect(100 * (frame), 100, 100, 100));
				 frame = frame % numframes;

				 isMoving = true;*/
			 }
		 }
	 }


	 void draw(RenderWindow& window)
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
 };
