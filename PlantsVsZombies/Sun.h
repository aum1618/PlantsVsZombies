#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "cordinates.h"
#include <fstream>
using namespace sf;
using namespace std;


class Sun {
public:
	int value;
	bool exist;
	bool animating;
	bool willMove;
	coordinates position;
	Sprite sprite;
	Texture texture;
	Clock clock;
	Sun(float x = 0, float y = 0) {
		value = 25;
		texture.loadFromFile("./Images/sun.png");
		sprite.setTexture(texture);
		sprite.setOrigin(25, 25);
		sprite.setPosition(x, y);
		position.x = x;
		exist = true;
		animating = false;
		position.y = y;
		willMove = true;
	}
	Sun(const Sun& sun) {
		value = sun.value;
		texture = sun.texture;
		sprite = sun.sprite;
		position.x = sun.position.x;
		position.y = sun.position.y;
		exist = sun.exist;
		animating = sun.animating;
		willMove = sun.willMove;
	}
	void draw(RenderWindow& window) {
		if (exist || animating) {
		window.draw(sprite);
		}
	}
	void move() {
		if (exist && willMove) {

		if (clock.getElapsedTime().asMilliseconds() > 50) {
			clock.restart();
			animate();
		position.y += 1;
		sprite.setPosition(position.x, position.y);
		}
		}
		else if (animating){
			float dx = 0 - position.x; 
			float dy = 0 - position.y; 

			float distance = sqrt(dx * dx + dy * dy);

			float speed = 2.0f; 
			float time = distance / speed;

			float speedX = dx / time;
			float speedY = dy / time;


			if (clock.getElapsedTime().asMilliseconds() < time) {
				float deltaTime = clock.restart().asMilliseconds();
				position.x += speedX * deltaTime;
				position.y += speedY * deltaTime;
				sprite.setPosition(position.x, position.y);
			}
else {
				position.x = 0;	
position.y = 0;
				animating = false;
				exist = false;
			}
			
		}
	}
	void animate() {
		sprite.rotate(1);
	}

	void Serialize(std::ostream& stream) const {
stream << value << endl;
		stream << exist << endl;
		stream << animating << endl;
		stream << willMove << endl;
		stream << position.x << endl;
		stream << position.y << endl;
	}

	void Deserialize(std::istream& stream) {
stream >> value;
		stream >> exist;
		stream >> animating;
		stream >> willMove;
		stream >> position.x;
		stream >> position.y;
		sprite.setPosition(position.x, position.y);
		cout << "Sun Deserialized" << endl;
		cout<< "attributes: " << value << " " << exist << " " << animating << " " << willMove << " " << position.x << " " << position.y << endl;
	}
	

};






class SunFactory {
public:
	Sun** suns;
	int suns_created;
	SunFactory(int numSuns = 0) {
		suns_created = numSuns;
		suns = new Sun * [suns_created];
		for (int i = 0; i < numSuns; i++) {
			int newX = (rand() % 1299);  
			int newY = -((rand() % 899)+100);        

			newX = newX / 50 * 50;
			newY = newY / 50 * 50;
			suns[i] = new Sun(newX, newY);
		}
	}
	void move() {
		for (int i = 0; i < suns_created; i++) {
			suns[i]->move();
		}
	}
	void draw(RenderWindow& window) {
		for (int i = 0; i < suns_created; i++) {
			suns[i]->draw(window);
		}
	}
	bool isSunThere(float x, float y) {
		for (int i = 0; i < suns_created; i++) {
			FloatRect sunBounds = suns[i]->sprite.getGlobalBounds();
			if (sunBounds.contains(x, y)) {
				return true;
			}
		}
		return false;
	}

	void moveSunToOrigin(float x, float y) {
		for (int i = 0; i < suns_created; i++) {
			FloatRect sunBounds = suns[i]->sprite.getGlobalBounds();
			if (sunBounds.contains(x, y)) {
				suns[i]->animating = true;
				suns[i]->exist = false;	
				return;
			}
		}
	}
	void restartClock() {
		for (int i = 0; i < suns_created; i++) {
			suns[i]->clock.restart();
		}
	}

	void addSunFromPlant(float x, float y) {
		Sun** temp = new Sun * [suns_created + 1];
		for (int i = 0; i < suns_created; i++) {
			temp[i] = suns[i];
		}
		temp[suns_created] = new Sun(x, y);
		temp[suns_created]->willMove = false;
		delete[] suns;
		suns = temp;
		suns_created++;
	}

	void removeNonExistantSun() {
for (int i = 0; i < suns_created; i++) {
			if (!suns[i]->exist && !suns[i]->animating) {
				delete suns[i];
				for (int j = i; j < suns_created - 1; j++) {
					suns[j] = suns[j + 1];
				}
				suns_created--;
				Sun** temp = new Sun * [suns_created];
				for (int j = 0; j < suns_created; j++) {
					temp[j] = suns[j];
				}
				delete[] suns;
				suns = temp;
			}
		}	
	}
	int getExistantSunCount() {
		int count = 0;
		for (int i = 0; i < suns_created; i++) {
			if (suns[i]->exist) {
				count++;
			}
		}
		return count;
	}

	void removeSun(float x, float y) {
		for (int i = 0; i < suns_created; i++) {
			if (suns[i]->position.x == x && suns[i]->position.y == y) {
				delete suns[i];
				for (int j = i; j < suns_created - 1; j++) {
					suns[j] = suns[j + 1];
				}
				suns_created--;
				Sun** temp = new Sun * [suns_created];
				for (int j = 0; j < suns_created; j++) {
					temp[j] = suns[j];
				}
				delete[] suns;
				suns = temp;
				return;
			}
		}
	}

	~SunFactory() {
		for (int i = 0; i < suns_created; i++) {
			delete suns[i];
		}
		delete[] suns;
	}
	void Serialize(std::ostream& stream) const {
	stream << suns_created << endl;
		for (int i = 0; i < suns_created; i++) {
			suns[i]->Serialize(stream);
		}
	}

	void Deserialize(std::istream& stream) {
		int temp_suns_created;
	stream >> temp_suns_created;
	Sun** temp_suns = new Sun * [temp_suns_created];
		for (int i = 0; i < temp_suns_created; i++) {
			temp_suns[i] = new Sun();
			temp_suns[i]->Deserialize(stream);
		}
for (int i = 0; i < suns_created; i++) {
			delete suns[i];
		}
		delete[] suns;
suns_created = temp_suns_created;
suns = temp_suns;
	}

};


