#include <SFML/Graphics.hpp>
#include <iostream>
#include "cordinates.h"
using namespace sf;
using namespace std;



class GameCursor {
private:
    sf::Cursor cursor;
    sf::Image cursorImg;
    sf::Sprite cursorSprite;
    string type;

public:
    GameCursor() {
        cursor.loadFromSystem(sf::Cursor::Arrow);
        type = "default";
    }

    void setCursor(const std::string& imagePath) {
        if (cursorImg.loadFromFile(imagePath)) {
            cursor.loadFromPixels(cursorImg.getPixelsPtr(), cursorImg.getSize(), sf::Vector2u(50, 50));
        }
    }

    void setDefaultCursor() {
        cursor.loadFromSystem(sf::Cursor::Arrow);
    }

    void renderCursor(coordinates clickPosition) {
        if ((clickPosition.x >= 100 && clickPosition.x <= 200) && (clickPosition.y >= 0 && clickPosition.y <= 100)) {
			setCursor("./Images/peeshooter.png");
            type="peashooter";
		}
        if ((clickPosition.x >= 200 && clickPosition.x <= 300) && (clickPosition.y >= 0 && clickPosition.y <= 100)) {
			setCursor("./Images/repeater.png");
            type="repeater";
		}
        if ((clickPosition.x >= 300 && clickPosition.x <= 400) && (clickPosition.y >= 0 && clickPosition.y <= 100)) {
			setCursor("./Images/snowpea.png");
            type="snowpea";
		}
        if ((clickPosition.x >= 400 && clickPosition.x <= 500) && (clickPosition.y >= 0 && clickPosition.y <= 100)) {
			setCursor("./Images/fumeshroom.png");
            type="fumeshroom";
		}
        if ((clickPosition.x >= 500 && clickPosition.x <= 600) && (clickPosition.y >= 0 && clickPosition.y <= 100)) {
			setCursor("./Images/wallnut.png");
            type="wallnut";
		}
        if ((clickPosition.x >= 600 && clickPosition.x <= 700) && (clickPosition.y >= 0 && clickPosition.y <= 100)) {
			setCursor("./Images/cherrybomb.png");
            type="cherrybomb";
		}
        if ((clickPosition.x >= 700 && clickPosition.x <= 800) && (clickPosition.y >= 0 && clickPosition.y <= 100)) {
			setCursor("./Images/sunflower.png");
            			type="sunflower";
		}
        if ((clickPosition.x >= 800 && clickPosition.x <= 900) && (clickPosition.y >= 0 && clickPosition.y <= 100)) {
			setCursor("./Images/shovel.png");
            type="shovel";
		}
        if ((clickPosition.x >= 0 && clickPosition.x <= 1300) && (clickPosition.y >= 100 && clickPosition.y <= 900)) {
			setDefaultCursor();
		}
	}
    string getCurrentCursor() {
		return type;
	}

    void applyCursor(sf::RenderWindow& window) {
        window.setMouseCursor(cursor);
    }
};
