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
	int numframes;
	int frame;
	bool shouldMove;
	string type;
	bool hasSummoned;
	float targetY;
	int scoring;
	Zombie(float x = 0, float y = 0)
	{
		numframes = 9;
		frame = 0;
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
		targetY = 0;
		scoring = 50;
	}
	virtual void move()
	{
		if (clock2.getElapsedTime().asSeconds() > 5)
		{
			shouldMove = true;
			clock2.restart();
		}

		if (isAlive)
		{

			if (clock.getElapsedTime().asMilliseconds() > speed)
			{
					frame++;
				if (shouldMove)
				{
					cordintes.x -= 2;
					if (cordintes.x < 0)
					{
						isAlive = false;
					}
					sprite.setPosition(cordintes.x, cordintes.y);
					sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));
				}
				else
				{
					cout << frame << endl;
					sprite.setTextureRect(IntRect(100 * (frame), 100, 100, 100));

				}
					frame = frame % numframes;
					clock.restart();
			}
		}

	}
	void draw(RenderWindow &window)
	{
		if (isAlive)
		{
			window.draw(sprite);
		}
	}
};

class FootballZombie : public Zombie
{
public:
	FootballZombie(float x = 0, float y = 0)
	{
		scoring = 75;
		health = 6;
		cordintes.x = x;
		cordintes.y = y;
		speed = 50;
		isAlive = true;
		texture.loadFromFile("./Images/footballzombie.png");
		texture.setSmooth(true);
		numframes = 28;
		frame = 0;
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 100, 100));
		sprite.setPosition(x, y);
		shouldMove = true;
		type = "football";
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
					frame++;
				if (shouldMove)
				{
					if (targetY != cordintes.y)
					{
						if (targetY > cordintes.y)
						{
							cordintes.y += 2;
						}
						else
						{
							cordintes.y -= 2;
						}
					}
					else
					{

						cordintes.x -= 2;
						int random = rand() % 100;
						float newY = cordintes.y;
						if (random == 1)
						{
							if (cordintes.y != 200)

								newY = cordintes.y - 100;
							else
							{
								newY = cordintes.y + 100;
							}
						}
						else if (random == 2)
						{
							if (cordintes.y != 600)
								newY = cordintes.y + 100;
							else
							{
								newY = cordintes.y - 100;
							}
						}
						targetY = newY;
					}
				sprite.setPosition(cordintes.x, cordintes.y);
				sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));
				}
				else {
					sprite.setTextureRect(IntRect(100 * (frame), 100, 100, 100));

				}
				clock.restart();
				frame = frame % numframes;
				if (cordintes.x < 0)
				{
					isAlive = false;
				}
			}
		}
	}

	void draw(RenderWindow &window)
	{
		if (isAlive)
		{
			window.draw(sprite);
		}
	}
};

class FlyingZombie : public Zombie
{
public:
	FlyingZombie(float x = 0, float y = 0)
	{
		scoring= 100;
		numframes = 11;
		frame = 0;
		health = 3;
		cordintes.x = x;
		cordintes.y = y;
		speed = 50;
		isAlive = true;
		texture.loadFromFile("./Images/flyingzombie.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 100, 100));
		sprite.setPosition(x, y);
		shouldMove = true;
		type = "flying";
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
					frame++;
				if (shouldMove)
				{
					cordintes.x -= 2;
					sprite.setPosition(cordintes.x, cordintes.y);
					sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));
					if (cordintes.x < 0)
					{
						isAlive = false;
					}
				}
				else
				{
					sprite.setTextureRect(IntRect(100 * (frame), 100, 100, 100));
				}
					frame = frame % numframes;
					clock.restart();
			}
		}
	}
	void draw(RenderWindow &window)
	{
		if (isAlive)
		{
			window.draw(sprite);
		}
	}
};

class DancingZombie : public Zombie
{
public:
	DancingZombie(float x = 0, float y = 0)
	{
		scoring = 100;
		health = 3;
		cordintes.x = x;
		cordintes.y = y;
		speed = 150;
		numframes = 8;
		frame = 0;
		isAlive = true;
		texture.loadFromFile("./Images/dancingzombie.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 100, 100));
		sprite.setPosition(x, y);
		shouldMove = true;
		type = "dancing";
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
					frame++;
				if (shouldMove)
				{
					if (targetY != cordintes.y)
					{
						if (targetY > cordintes.y)
						{
							cordintes.y += 2;
						}
						else
						{
							cordintes.y -= 2;
						}
					}
					else
					{
						int random = rand() % 100;
						float newY = cordintes.y;
						if (random == 1)
						{
							if (cordintes.y != 200)

								newY = cordintes.y - 100;
							else
							{
								newY = cordintes.y + 100;
							}
						}
						else if (random == 2)
						{
							if (cordintes.y != 600)
								newY = cordintes.y + 100;
							else
							{
								newY = cordintes.y - 100;
							}
						}
						targetY = newY;
					}
					cordintes.x -= 2;
				sprite.setPosition(cordintes.x, cordintes.y);
				sprite.setTextureRect(IntRect(100 * (frame), 0, 100, 100));
				}
				else {
					sprite.setTextureRect(IntRect(100 * (frame), 100, 100, 100));

				}
				clock.restart();
				frame = frame % numframes;
				if (cordintes.x < 0)
				{
					isAlive = false;
				}
			}
			
		}
	}

	void draw(RenderWindow &window)
	{
		if (isAlive)
		{
			
			window.draw(sprite);
		}
	}
};
