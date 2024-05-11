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
#include "Screen.h";
using namespace sf;
using namespace std;

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
    LeaderBoardScreen leaderboard(window);
    GameScreen *game = nullptr;
    HomeScreen home(window);
    PauseScreen pause(window);
    InstructionsScreen instructions(window);
    bool gameScreenInitialized = false;

    string screen = "home";
    while (window.isOpen())
    {
        if (screen == "home")
        {
            home.renderScreen(window, screen);
        }
        else if (screen == "instructions")
        {
            instructions.renderScreen(window, screen);
        }
        else if (screen == "leaderboard")
        {
            leaderboard.renderScreen(window, screen);
        }
        else if (screen == "game")
        {
            if (!gameScreenInitialized)
            {
                game = new GameScreen(window);
                gameScreenInitialized = true;
            }
            if (
                game != nullptr)
                game->renderScreen(window, screen);
        }
        else if (screen == "pause") {
pause.renderScreen(window, screen);
		}
        else
        {
            window.close();
        }
    }
}
