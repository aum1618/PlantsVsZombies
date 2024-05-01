#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
//#include"../SFML/Images/"
using namespace sf;
using namespace std;

struct coordinates {
	int x;
	int y;
};
struct Zombies {
	Sprite s;
	coordinates co;
};


//Drawing the background
void createBack(RenderWindow& window) {
	//Drawing the background
	Image map_image;
	map_image.loadFromFile("./Images/background.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	window.draw(s_map);
}
void initializeZombies(Zombies* z, int noOfZom, sf::Texture& zombText) {
	for (int i = 0; i < noOfZom; i++) {
		z[i].s.setTexture(zombText);
		z[i].co.x = 1280 - zombText.getSize().x;
		z[i].co.y = rand() % (700 - zombText.getSize().y);
	}
}
void drawZombie(Zombies* z, int noOfZom, sf::RenderWindow& window) {
	for (int i = 0; i < noOfZom; i++) {
		z[i].s.setPosition(z[i].co.x, z[i].co.y);
		window.draw(z[i].s);
	}
}
void moveZombie(RenderWindow& window, Zombies* zomb, int numZombies, float speed) {
	for (int i = 0; i < numZombies; ++i) {
		float currentX = zomb[i].co.x;
		float newX = 0;
		// Check if the zombie has gone off the screen
		if (currentX < 0) {
			// If the zombie is completely off-screen, reset its position to the right side
			newX = 1280 - 280;
		}
		else {
			// If the zombie is still on the screen, move it to the left
			newX = currentX - speed;
		}
		zomb[i].co.x = newX;


		// Set the new position for the current zombie (only along the X-axis)
	}
}
//Drawing the map
//void createMap(RenderWindow& window) {
//	//Drawing a map
//	Image map_image;//объект изображения для карты
//	map_image.loadFromFile("./Images/grid.png");//load the file for the map
//	Texture map;
//	map.loadFromImage(map_image);
//	Sprite s_map;
//	s_map.setTexture(map);
//	s_map.setPosition(300, 160);
//
//	window.draw(s_map);
//}


int main()
{
	srand(time(0));
	float speed = 10.0f;
	int numberOfZombies = 5;
	Image zombie_image;
	zombie_image.loadFromFile("./Images/zombieOnPlace.png");
	sf::Texture zombieTexture;
	sf::Sprite zombieSprite;
	zombieTexture.loadFromImage(zombie_image);
	zombieSprite.setTexture(zombieTexture);
	Zombies* zomb = new Zombies[numberOfZombies];
	initializeZombies(zomb, numberOfZombies, zombieTexture);


	//Create a window, n*n
	RenderWindow window(VideoMode(1280, 720), "Plants Vs Zombies");
	//Game icon
	Image icon;
	if (!icon.loadFromFile("./Images/icon.png"))
	{
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());


	///////////////////////////////////////

	//Game field (5*9)
	//Point 137*79 - leftmost point
	//length 41; width 53
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

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float moneyTime = timeMoney.getElapsedTime().asSeconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		moveZombie(window, zomb, numberOfZombies, speed);
		window.clear();
		//Create a background
		createBack(window);
		drawZombie(zomb, numberOfZombies, window);

		window.display();

	}
	return 0;
}
