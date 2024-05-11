#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;
using namespace std;
#include "cordinates.h";
#include "Player.h";


struct Shop {
	coordinates cordinates;
	Sprite sprite;
	Texture texture;
	Texture disable;
	Sprite* disable_array;

	Shop() {
		cordinates.x = 0;
		cordinates.y = 0;
		texture.loadFromFile("./Images/shop.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		disable.loadFromFile("./Images/disabler.png");
		disable_array = new Sprite[7];
		for (int i = 0; i < 7; i++)
		{
			disable_array[i].setTexture(disable);
			disable_array[i].setPosition(100 * (i + 1), 0);
			sf::Color color = disable_array[i].getColor();
			color.a = 180;
			disable_array[i].setColor(color);
		}
	}
	void draw(RenderWindow& window, Player& player) {
		window.draw(sprite);
        for (int i = 0; i < 7; i++)
        {
            if (player.currency < 50)
                window.draw(disable_array[i]);

            else if (player.currency >= 50 && player.currency < 75)
            {
                if (i != 0 && i != 4)
                {
                    window.draw(disable_array[i]);
                }
            }
            else if (player.currency >= 50 && player.currency <= 75)
            {
                if (i != 0 && i != 4 && i != 3)
                {
                    window.draw(disable_array[i]);
                }
            }
            else if (player.currency >= 50 && player.currency <= 100)
            {
                if (i != 0 && i != 4 && i != 3 && i != 2 && i != 6)
                {
                    window.draw(disable_array[i]);
                }
            }
            else if (player.currency >= 50 && player.currency < 150)
            {
                if (i != 0 && i != 4 && i != 3 && i != 2 && i != 6)
                {
                    window.draw(disable_array[i]);
                }
            }
            else if (player.currency >= 50 && player.currency <= 150)
            {
                if (i != 0 && i != 4 && i != 3 && i != 2 && i != 6 && i != 5)
                {
                    window.draw(disable_array[i]);
                }
            }
            else if (player.currency >= 50 && player.currency < 200)
            {
                if (i != 0 && i != 4 && i != 3 && i != 2 && i != 6 && i != 5)
                {
                    window.draw(disable_array[i]);
                }
            }
        }

	}
};