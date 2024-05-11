#include <SFML/Window/Cursor.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include "PlantFactory.h"
#include "ZombieFactory.h"
#include "Sun.h"
#include "Cursor.h"
#include "Shop.h"
#include "Inspector.h"
#include "LawnMowerFactory.h"
using namespace sf;
using namespace std;
void renderHome(int,int,RenderWindow&);
void renderInstructions(int,int,RenderWindow&);
void renderLeaderboard(int, int, RenderWindow&);
void renderGame(
    int GAME_WIDTH,
	int GAME_HEIGHT,
	RenderWindow &window
) {
    Font font;
    if (!font.loadFromFile("new.ttf")) {
        cout << "ERROR LOADING FONT" << endl;
    }
    Texture map;
    map.loadFromFile("./Images/background.png");
    map.setRepeated(true);
    Sprite s_map;
    s_map.setTexture(map);
    s_map.setTextureRect(IntRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
    s_map.setScale(1.0f, 1.0f);
    s_map.setPosition(0, 0);
    window.setVerticalSyncEnabled(true);
    Texture grid;
    grid.loadFromFile("./Images/grid.png");
    Sprite s_grid;
    s_grid.setTexture(grid);
    s_grid.setPosition(200, 200);
    GameCursor cursor;
    Shop sh;
    int currency = 0;
    Text currencyText;
    currencyText.setFont(font); 
    currencyText.setCharacterSize(24); 
    currencyText.setFillColor(Color::Black); 
    currencyText.setString(to_string(currency)); 
    currencyText.setPosition(40, 70); 
    PlantFactory plantFactory;
    ZombieFactory zombieFactory(20);
    SunFactory sunFactory(20);
    LawnMowerFactory lawnMowerFactory(5);
    Inspector inspector;

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                coordinates clickPosition;
                clickPosition.x = event.mouseButton.x;
                clickPosition.y = event.mouseButton.y;
                inspector.collectSun(clickPosition, sunFactory, currency,plantFactory);
                inspector.addPlantOnClick(clickPosition, currency, plantFactory, cursor);
                cursor.renderCursor(clickPosition, currency);
            }
        }
        inspector.checkLawnmoverCollision(lawnMowerFactory,zombieFactory);
        inspector.checkPlantZombieBulletCollision(plantFactory, zombieFactory);


        zombieFactory.summonZombies();
        sunFactory.move();
        lawnMowerFactory.move();
        zombieFactory.move();
        window.clear();
        window.draw(s_map);
        window.draw(s_grid);
        zombieFactory.draw(window);

        plantFactory.draw(window);
        lawnMowerFactory.draw(window);
        sunFactory.draw(window);
        sh.draw(window,currency);
        currencyText.setString(to_string(currency));
        cursor.applyCursor(window);
        window.draw(currencyText);
        window.display();
    }
    return;
}

void renderHome(
    int GAME_WIDTH,
    int GAME_HEIGHT,
    RenderWindow& window
) {
    Texture HomeTexture;
    HomeTexture.loadFromFile("./Images/homescreen.png");
    Sprite home;
    home.setTexture(HomeTexture);
    home.setPosition(0, 0);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Check if mouse click falls within the specified area
                if (mouseX >= 66 && mouseX <= 635 && mouseY >= 356 && mouseY <= 501) {
                    // Call renderGame function
                    renderGame(GAME_WIDTH, GAME_HEIGHT, window);
                }
                else if (mouseX >= 66 && mouseX <= 635 && mouseY >= 526 && mouseY <= 669) {
                    renderInstructions(GAME_WIDTH, GAME_HEIGHT, window);
                }
                else if (mouseX >= 66 && mouseX <= 635 && mouseY >= 695 && mouseY <= 839) {
                    renderLeaderboard(GAME_WIDTH, GAME_HEIGHT, window);
                }
            }
        }

        window.clear();
        window.draw(home);
        window.display();
    }
}
void renderLeaderboard(int GAME_WIDTH,
    int GAME_HEIGHT,
    RenderWindow& window) {
    Texture instructionsTexture;
    instructionsTexture.loadFromFile("./Images/leaderboard.png");
    Sprite instructions;
    instructions.setTexture(instructionsTexture);
    instructions.setPosition(0, 0);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Check if mouse click falls within the specified area
                if (mouseX >= 927 && mouseX <= 1277 && mouseY >= 810 && mouseY <= 889) {
                    // Call renderGame function
                    renderHome(GAME_WIDTH, GAME_HEIGHT, window);
                }
            }

        }

        window.clear();
        window.draw(instructions);
        window.display();
    }
}
void renderInstructions(int GAME_WIDTH,
    int GAME_HEIGHT,
    RenderWindow& window) {
    Texture instructionsTexture;
    instructionsTexture.loadFromFile("./Images/instructions.png");
    Sprite instructions;
    instructions.setTexture(instructionsTexture);
    instructions.setPosition(0, 0);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Check if mouse click falls within the specified area
                if (mouseX >= 927 && mouseX <= 1277 && mouseY >= 810 && mouseY <= 889) {
                    // Call renderGame function
                    renderHome(GAME_WIDTH, GAME_HEIGHT, window);
                }
            }
            
        }

        window.clear();
        window.draw(instructions);
        window.display();
    }
}
int main()
{
    srand(time(0));
    const int GAME_ROWS = 9;
    const int GAME_COLS = 13;
    const int CELL_SIZE = 100;
    const int GAME_WIDTH = GAME_COLS * CELL_SIZE;
    const int GAME_HEIGHT = GAME_ROWS * CELL_SIZE;
    RenderWindow window(VideoMode(GAME_WIDTH, GAME_HEIGHT, 32), "Plants Vs Zombies");
    Image icon;
    if (!icon.loadFromFile("./Images/Icon.png"))
    {
        return 1;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());
    renderHome(GAME_WIDTH, GAME_HEIGHT, window);

    /*renderGame(GAME_WIDTH,GAME_HEIGHT,window);*/
}
