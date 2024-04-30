#include <SFML/Graphics.hpp>
#include <ctime>
//#include"../SFML/Images/"
using namespace sf;
using namespace std;


struct coordinats {
	int x;
	int y;
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
void createZombie(RenderWindow& window){
	float speed = 0.1f;
	Image zombie_image;
	zombie_image.loadFromFile("./Images/zombieOnPlace.png");
	Texture zombieTexture;
	zombieTexture.loadFromImage(zombie_image);
	Sprite z_zombie;

	// Set random y-value
	int fixedY = 400;
	// Set position at x-value of 1920 and random y-value
	z_zombie.setTexture(zombieTexture);
	z_zombie.setPosition(1920 - zombieTexture.getSize().x, fixedY);

	window.draw(z_zombie);
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
	//Create a window, n*n
	RenderWindow window(VideoMode(1920, 1080), "Plants Vs Zombies");
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

		//Create a background
		createBack(window);
		//createMap(window);
		createZombie(window);



		window.setSize(sf::Vector2u(1920, 1080));
		window.display();
	}
	return 0;
}