#pragma once
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
#include "Player.h";
#include <fstream>


const int MAX_SCORES = 10; // Maximum number of high scores

struct HighScore {
    string playerName;
    int score;
};

void bubbleSort(HighScore highScores[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (highScores[j].score < highScores[j + 1].score) {
                // Swap scores
                HighScore temp = highScores[j];
                highScores[j] = highScores[j + 1];
                highScores[j + 1] = temp;
            }
        }
    }
}

class Screen
{
public:
    const int GAME_ROWS = 9;
    const int GAME_COLS = 13;
    const int CELL_SIZE = 100;
    const int GAME_WIDTH = GAME_COLS * CELL_SIZE;
    const int GAME_HEIGHT = GAME_ROWS * CELL_SIZE;
    Texture bgImg;
    Sprite background;
    Screen(RenderWindow &window)
    {
        bgImg.loadFromFile("./Images/background.png");
        background.setTexture(bgImg);
        background.setTextureRect(IntRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
        background.setScale(1.0f, 1.0f);
        background.setPosition(0, 0);
        window.setVerticalSyncEnabled(true);
    }

    virtual void renderScreen(RenderWindow &window) {};
};

class HomeScreen : public Screen
{
public:
    HomeScreen(RenderWindow &window) : Screen(window)
    {
        bgImg.loadFromFile("./Images/homescreen.png");
    }
    void renderScreen(RenderWindow &window, string &currentScreen)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Check if mouse click falls within the specified area
                if (mouseX >= 66 && mouseX <= 635 && mouseY >= 356 && mouseY <= 501)
                {
                    // Call renderGame function
                    currentScreen = "game";
                }
                else if (mouseX >= 66 && mouseX <= 635 && mouseY >= 526 && mouseY <= 669)
                {
                    currentScreen = "instructions";
                }
                else if (mouseX >= 66 && mouseX <= 635 && mouseY >= 695 && mouseY <= 839)
                {
                    currentScreen = "leaderboard";
                }
            }
        }

        window.clear();
        window.draw(background);
        window.display();
    }
};

class InstructionsScreen : public Screen
{
public:
    InstructionsScreen(RenderWindow &window) : Screen(window)
    {
        bgImg.loadFromFile("./Images/instructions.png");
    }
    void renderScreen(RenderWindow &window, string &currentScreen)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Check if mouse click falls within the specified area
                if (mouseX >= 927 && mouseX <= 1277 && mouseY >= 810 && mouseY <= 889)
                {
                    // Call renderGame function
                    currentScreen = "home";
                }
            }
        }
        window.clear();
        window.draw(background);
        window.display();
    }
};

class LeaderBoardScreen : public Screen
{
private:
    Font font;
    Text highScoresText;

public:
    LeaderBoardScreen(RenderWindow& window) : Screen(window)
    {
        bgImg.loadFromFile("./Images/leaderboard.png");

        // Load font
        if (!font.loadFromFile("arial.ttf"))
        {
            cout << "ERROR LOADING FONT" << endl;
        }

        // Initialize text for displaying high scores
        highScoresText.setFont(font);
        highScoresText.setCharacterSize(24);
        highScoresText.setFillColor(Color::White);
        highScoresText.setPosition(100, 100); // Set position where high scores will be displayed
    }

    void renderScreen(RenderWindow& window, string& currentScreen)
    {
        // Read high scores from file
        ifstream highScoresFile("highscores.txt");
        string highScoresStr;
        if (highScoresFile.is_open())
        {
            string line;
            while (getline(highScoresFile, line))
            {
                highScoresStr += line + "\n";
            }
            highScoresFile.close();
        }
        else
        {
            highScoresStr = "Unable to open highscores.txt";
        }

        // Set the text to display high scores
        highScoresText.setString(highScoresStr);

        // Event handling
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Check if mouse click falls within the specified area to go back home
                if (mouseX >= 927 && mouseX <= 1277 && mouseY >= 810 && mouseY <= 889)
                {
                    currentScreen = "home";
                }
            }
        }

        // Rendering
        window.clear();
        window.draw(background);
        window.draw(highScoresText); // Draw high scores
        window.display();
    }
};

class PauseScreen : public Screen
{
public:
    PauseScreen(RenderWindow &window) : Screen(window)
    {
        bgImg.loadFromFile("./Images/pausesccreen.png");
    }
    void renderScreen(RenderWindow &window, string &currentScreen)
    {
        while (true)
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                {
                    coordinates clickPosition;
                    clickPosition.x = event.mouseButton.x;
                    clickPosition.y = event.mouseButton.y;
                    if ((clickPosition.x >= 377 && clickPosition.x <= 923) && (clickPosition.y >= 318 && clickPosition.y <= 450))
                    {
                        currentScreen = "game";
                        return;
                    }
                    else if ((clickPosition.x >= 205 && clickPosition.x <= 1095) && (clickPosition.y >= 440 && clickPosition.y <= 617))
                    {
                        currentScreen = "home";
                        return;
                    }
                }
            }
            window.clear();
            window.draw(background);
            window.display();
        };
    }
};

class LevelUpScreen : public Screen
{
public:
    Clock clock;
    LevelUpScreen(RenderWindow &window) : Screen(window)
    {
        bgImg.loadFromFile("./Images/levelup.png");
    }
    void renderScreen(RenderWindow &window, string &currentScreen)
    {
        clock.restart();
        while (clock.getElapsedTime().asSeconds() < 3)
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
            }
            window.clear();
            window.draw(background);
            window.display();
        };
        currentScreen = "game";
    }
};

class GameScreen : public Screen
{
public:
    Texture pauseButton;
    Sprite pause_button;
    GameCursor cursor;
    Shop sh;
    Text currencyText;
    Font font;
    Text score;
    Text level;
    PlantFactory *plantFactory;
    ZombieFactory *zombieFactory;
    SunFactory *sunFactory;
    LawnMowerFactory *lawnMowerFactory;
    Player player;
    Inspector inspector;
    GameScreen(RenderWindow &window) : Screen(window)
    {
        if (!font.loadFromFile("new.ttf"))
        {
            cout << "ERROR LOADING FONT" << endl;
        }
        bgImg.loadFromFile("./Images/background.png");
        bgImg.setRepeated(true);
        currencyText.setFont(font);
        currencyText.setCharacterSize(24);
        currencyText.setFillColor(Color::Black);
        currencyText.setString(to_string(player.currency));
        currencyText.setPosition(30, 70);
        score.setFont(font);
        score.setCharacterSize(24);
        score.setFillColor(Color::White);
        score.setString("Score:  " + to_string(player.score));
        score.setPosition(1150, 850);
        level.setFont(font);
        level.setCharacterSize(24);
        level.setFillColor(Color::Red);
        level.setString("Level: " + to_string(player.level));
        level.setPosition(20, 850);
        pauseButton.loadFromFile("./Images/pause.png");
        pause_button.setTexture(pauseButton);
        pause_button.setPosition(1200, 0);
        sunFactory = new SunFactory(10);
        zombieFactory = new ZombieFactory(10, player.level);
        lawnMowerFactory = new LawnMowerFactory(5);
        plantFactory = new PlantFactory();
        cout << "Deserializing game state...\n";
        Deserialize();
    }
    GameScreen(const GameScreen &gs) : Screen(gs)
    {
        currencyText = gs.currencyText;
        font = gs.font;
        plantFactory = gs.plantFactory;
        zombieFactory = gs.zombieFactory;
        sunFactory = gs.sunFactory;
        lawnMowerFactory = gs.lawnMowerFactory;
        inspector = gs.inspector;
        player = gs.player;
    };
    void Serialize()
    {
        ofstream saveFile("save.txt", ios::trunc);
        if (saveFile.is_open())
        {
            zombieFactory->Serialize(saveFile);
            sunFactory->Serialize(saveFile);
            lawnMowerFactory->Serialize(saveFile);
            player.Serialize(saveFile);
            plantFactory->Serialize(saveFile);
            saveFile.close();
        }
        else
        {
            cout << "Error opening the save file.\n";
        }
    }
    void Deserialize()
    {
        ifstream stream("save.txt");
        if (!stream.is_open())
        {
            cout << "Error opening the save file.\n";
            return;
        }
        zombieFactory->Deserialize(stream);
        sunFactory->Deserialize(stream);
        lawnMowerFactory->Deserialize(stream);
        player.Deserialize(stream);
        plantFactory->Deserialize(stream);
        stream.close();
    }
    void renderScreen(RenderWindow &window, string &currentScreen)
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                cout << "Saving game state...\n";
                Serialize();

                window.close();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                coordinates clickPosition;
                clickPosition.x = event.mouseButton.x;
                clickPosition.y = event.mouseButton.y;
                inspector.collectSun(clickPosition, sunFactory, plantFactory, player);
                inspector.addPlantOnClick(clickPosition, plantFactory, cursor, player);
                cursor.renderCursor(clickPosition, player);
                if ((clickPosition.x >= 1200 && clickPosition.x <= 1300) && (clickPosition.y >= 0 && clickPosition.y <= 100))
                {
                    currentScreen = "pause";
                }
            }
        }
        inspector.checkLawnmoverCollision(lawnMowerFactory, zombieFactory, player);
        inspector.checkPlantZombieBulletCollision(plantFactory, zombieFactory, player);
        inspector.hasZombieReachedEdge(zombieFactory, player);
        if (zombieFactory->areZombiesDead())
        {
            player.level++;
            delete zombieFactory;
            delete plantFactory;
            delete sunFactory;
            delete lawnMowerFactory;
            zombieFactory = new ZombieFactory(player.level * 10, player.level);
            plantFactory = new PlantFactory();
            sunFactory = new SunFactory(player.level * 20);
            lawnMowerFactory = new LawnMowerFactory(5);
            player.currency = 0;
            currentScreen = "levelUp";
        }
        if (player.lives <= 0)
        {
            ofstream saveFile("save.txt", ios::trunc);
            currentScreen = "gameover";
            Texture endTexture;
            string playerName;
            Text playerNameText;
            playerNameText.setFont(font);
            playerNameText.setCharacterSize(50);
            playerNameText.setFillColor(sf::Color::White);
            // set origin to be center of the text
            playerNameText.setOrigin(
                playerNameText.getLocalBounds().left + playerNameText.getLocalBounds().width / 2,
                playerNameText.getLocalBounds().top + playerNameText.getLocalBounds().height / 2);
            playerNameText.setPosition((GAME_WIDTH / 2) - 100, (GAME_HEIGHT / 2));
            Sprite endSprite;
            endTexture.loadFromFile("./Images/levelup.png");
            endSprite.setTexture(endTexture);
            endSprite.setPosition(0, 0);

            while (true)
            {
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::TextEntered)
                    {
                        if (event.text.unicode < 128)
                        {
                            if (event.text.unicode == 13)
                            {
                                // Enter key pressed
                                // Save the name
                                if (!playerName.empty())
                                {
                                    HighScore highScores[MAX_SCORES];
                                    int numScores = 0;

                                    // Read existing high scores from file
                                    ifstream scoreFile("highscores.txt");
                                    if (scoreFile.is_open()) {
                                        while (numScores < MAX_SCORES && scoreFile >> highScores[numScores].playerName >> highScores[numScores].score) {
                                            numScores++;
                                        }
                                        scoreFile.close();
                                    }
                                    else {
                                        cout << "Error opening the highscores file.\n";
                                    }

                                    // Sort high scores
                                    bubbleSort(highScores, numScores);

                                    // Store sorted high scores back to file
                                    ofstream saveFile("highscores.txt", ios::trunc);
                                    if (saveFile.is_open()) {
                                        for (int i = 0; i < numScores; ++i) {
                                            saveFile << highScores[i].playerName << " " << highScores[i].score << "\n";
                                        }
                                        saveFile.close();
                                    }
                                    else {
                                        cout << "Error opening the highscores file for writing.\n";
                                    }
                                }
                                window.close();
                            }
                            else if (event.text.unicode == 8 && !playerName.empty())
                            {
                                // Backspace pressed
                                playerName.pop_back();
                            }
                            else
                            {
                                playerName += (char)(event.text.unicode);
                            }
                            playerNameText.setString(playerName);
                        }
                    }
                }
                window.clear();
                window.draw(endSprite);
                window.draw(playerNameText);
                window.display();
            }
        }

        zombieFactory->summonZombies();
        sunFactory->move();
        lawnMowerFactory->move();
        zombieFactory->move();
        plantFactory->move();
        window.clear();
        window.draw(background);
        zombieFactory->draw(window);
        window.draw(pause_button);
        plantFactory->draw(window);
        lawnMowerFactory->draw(window);
        sunFactory->draw(window);
        sh.draw(window, player, player.level);
        currencyText.setString(to_string(player.currency));
        score.setString("Score:  " + to_string(player.score));
        level.setString("Level: " + to_string(player.level));
        cursor.applyCursor(window);
        window.draw(currencyText);
        window.draw(score);
        window.draw(level);
        window.display();
    }
};
