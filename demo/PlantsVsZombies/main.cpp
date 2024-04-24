#include <SFML/Graphics.hpp>
#include <ctime>
#include "Classes.h"
using namespace sf;
using namespace std;

//Добавить картинку с меню "Пауза"
void createMenuPause(RenderWindow &window) {
	Image pauseButtonRender;
	//загружаем файл для карты
	pauseButtonRender.loadFromFile("кнопкаПауза.png");
	Texture texture;
	texture.loadFromImage(pauseButtonRender);
	Sprite buttonPause;
	buttonPause.setTexture(texture);
	//Координата левого верхнего угла, ширина и высота
	buttonPause.setTextureRect(IntRect(0, 0, 140, 140));
	//В определенном квадате
	buttonPause.setPosition(1000, 10);
	window.draw(buttonPause);
}

//Добавить меню с очками
void createPoints(RenderWindow &window) {
	Image pauseButtonRender;
	//загружаем файл для карты
	pauseButtonRender.loadFromFile("modelСолнце.png");
	Texture texture;
	texture.loadFromImage(pauseButtonRender);
	Sprite buttonPause;
	buttonPause.setTexture(texture);
	//Координата левого верхнего угла, ширина и высота
	buttonPause.setTextureRect(IntRect(0, 0, 140, 140));
	//В определенном квадате
	buttonPause.setPosition(500, 23);
	window.draw(buttonPause);
}


struct coordinats {
	int x;
	int y;
};


void heroToField(RenderWindow &window, std::string path, coordinats temp) {
	//Добавить условие, что клетка не должна быть занята
	//Рисование героя
	Image hero_image;
	//загружаем файл для карты
	hero_image.loadFromFile(path);
	Texture texture;
	texture.loadFromImage(hero_image);
	Sprite hero;
	hero.setTexture(texture);
	//Координата левого верхнего угла, ширина и высота
	hero.setTextureRect(IntRect(0, 0, 120, 120));
	//В определенном квадате
	hero.setPosition(temp.x,temp.y);
	window.draw(hero);
}


//Отрисовка карточки героя
void createHeroCard(RenderWindow &window, std::string path, int number_hero, vector<coordinats> &list) {
	//Рисование карточки
	Image map_image;
	//загружаем файл для карты
	map_image.loadFromFile(path);
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 95+number_hero*68);
	coordinats temp;
	temp.x = 0;
	temp.y = 95 + number_hero * 68;
	list.push_back(temp);
	window.draw(s_map);
}

//Отрисовка заднего фона
void createBack(RenderWindow &window) {
	//Рисование фона
	Image map_image;
	map_image.loadFromFile("задний фон.jpg");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	window.draw(s_map);
}

//Отрисовка карты
void createMap(RenderWindow &window) {
	//Рисование карты
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("картаЦеликом.png");//загружаем файл для карты
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(300, 160);

	window.draw(s_map);
}
//Попали ли курсором в карту героя
bool isHitCard(coordinats temp, Vector2f click) {
    auto clickX = click.x;
    auto clickY = click.y;
	auto a = temp.y + 62 - clickY;
	return ((clickX < 106) && (temp.y + 62 - clickY > 0) && (clickY > temp.y));
}

//Возврат объекта "Цветок" по его названию
FlowerPair* callObjectSunflower(Flower play, SunflowersFactory sun_factory) {
	FlowerPair* sunflower = play.createFlower(sun_factory);
	sunflower->physic->setHealthPoint(100);
	sunflower->physic->setDamagePoint(0);
	sunflower->image->setSpeedDx(0);
	sunflower->image->setModel();
	sunflower->image->reprinting = false;
	return sunflower;
}

FlowerPair* callObjectPea(Flower play, PeaFactory pea_factory) {
	FlowerPair* pea = play.createFlower(pea_factory);
	pea->physic->setHealthPoint(150);
	pea->physic->setDamagePoint(5);
	pea->image->setSpeedDx(0.1);
	pea->image->setModel();
	pea->image->weaponFrom();
	pea->image->reprinting = false;
	return pea;
}

FlowerPair* callObjectCabbage(Flower play, CabbageFactory cab_factory) {
	FlowerPair* cabbage = play.createFlower(cab_factory);
	cabbage->physic->setHealthPoint(100);
	cabbage->physic->setDamagePoint(30);
	cabbage->image->setSpeedDx(0.05);
	cabbage->image->setModel();
	cabbage->image->weaponFrom();
	cabbage->image->reprinting = false;
	return cabbage;
}

FlowerPair* callObjectNut(Flower play, NutFactory nut_factory) {
	FlowerPair* nut = play.createFlower(nut_factory);
	nut->physic->setHealthPoint(100);
	nut->physic->setDamagePoint(0);
	nut->image->setSpeedDx(0);
	nut->image->setModel();
	nut->image->reprinting = false;
	return nut;
}

FlowerPair* callObjectActinia(Flower play, ActiniaFactory act_factory) {
	FlowerPair* actinia = play.createFlower(act_factory);
	actinia->physic->setHealthPoint(100);
	actinia->physic->setDamagePoint(30);
	actinia->image->setSpeedDx(0.06);
	actinia->image->setModel();
	actinia->image->weaponFrom();
	actinia->image->reprinting = false;
	return actinia;
}

FlowerPair* callObjectBomb(Flower play, BombFactory bom_factory) {
	FlowerPair* bomb = play.createFlower(bom_factory);
	bomb->physic->setHealthPoint(1);
	bomb->physic->setDamagePoint(0);
	bomb->image->setSpeedDx(0);
	bomb->image->setModel();
	bomb->image->reprinting = false;
	return bomb;
}



int main()
{
	//Создадим окно, n*n
	RenderWindow window(VideoMode(1200, 700), "Plants Vs Zombies");
	//Иконка игры
	Image icon;
	if (!icon.loadFromFile("icon.png"))
	{
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());
	
	///////////////////////////////////////
	//Поле игры (5*9)
	//Точка 137*79 - крайняя левая точка
	//длина 41; ширина 53
	vector < vector<bool> > FIELD_GAME_STATUS;
	for (auto i = 0; i < 5; i++) {
		vector <bool> tempVector;
		for (auto j = 0; j < 9; j++) {
			tempVector.push_back(true);
		}
		FIELD_GAME_STATUS.push_back(tempVector);
	}
	bool heroIsReadyToBeStandToFeld = false;
	string heroPath;
	///////////////////////////////////////



	//Время с начала запуска игры, чтобы запускать в игру зомби
	Clock timerStart;
	vector <int> timingsToGoZombie = { 4, 3, 2, 1, 5, 1, 1, 3, 4, 68};
	vector <int> numberWays = {1,2,2,4,1,3,2,5,4,1};
	double cooldaunShoot = 2;
	Clock timeToCooldaun;
	Clock timeMoney;
	int balance = 0;
	

	Clock clock;

	//Машины
	Car carOne = Car(window, 0);
	Car carTwo = Car(window, 1);
	Car carThree = Car(window, 2);
	Car carFour = Car(window, 3);
	Car carFive = Car(window, 4);
	CarCollection listCars;
	listCars.push(carOne);
	listCars.push(carTwo);
	listCars.push(carThree);
	listCars.push(carFour);
	listCars.push(carFive);
	

	//Зомби
	vector <Zombie> zombiesList;
	for (int i = 0; i < 10; ++i) {
		Zombie temp = Zombie(window, numberWays[i]);
		zombiesList.push_back(temp);
	}
	//Сейчас идут по карте 0 зомби
	auto currentInRun = 0;		
	//Если идут зомби, то начать стрелять
    //Матрица (тут 5 дорожек)
	vector<vector<int>> numberZombieInLine(5);

	for (auto i = 0; i < numberWays.size(); i++) {
		if (numberWays[i] == 1) {
			numberZombieInLine[0].push_back(i);
		}
		if (numberWays[i] == 2) {
			numberZombieInLine[1].push_back(i);
		}
		if (numberWays[i] == 3) {
			numberZombieInLine[2].push_back(i);
		}
		if (numberWays[i] == 4) {
			numberZombieInLine[3].push_back(i);
		}
		if (numberWays[i] == 5) {
			numberZombieInLine[4].push_back(i);
		}
	}


	//Растения
	vector<pair<coordinats, string>> vectorFlowersToRender;
	vector<bool> bulletIsRendering;
	//6 фабрик под порождение растений
	Flower play;
	SunflowersFactory sun_factory;
	PeaFactory pea_factory;
	CabbageFactory cab_factory;
	NutFactory nut_factory;
	BombFactory bomb_factory;
	ActiniaFactory act_factory;
	//Пули летящие
	std::vector<string> listBullets;
	vector<FlowerPair*> listFlowers;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float moneyTime = timeMoney.getElapsedTime().asSeconds();
		if (moneyTime > 5) {
			timeMoney.restart();
			balance += 50;
		}

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//Создание заднего фона
		createBack(window);
		vector <std::string> paths = { "Горошек.png", "Подсолнух.png", "Капуста.png", "Актиния.png", "Бомба.png", "Поу.png" };
		vector <coordinats> placeCards;
		//Рисование карточки героев
		for (int i = 0; i < 6; i++) {
			std::string path = "card" + paths[i];
			auto number_hero = i;
			createHeroCard(window, path, number_hero + 1, placeCards);
		}
		//Сооздание карты
		createMap(window);
		//Создание кнопки пауза
		createMenuPause(window);
		//Создание окна с "Солнышками"
		createPoints(window);

		//Обновление телег
		for (int i = 0; i<5; i++) {
			listCars.items[i].dx = 0;
		}
		

		CarIterator it(listCars);
		int q = 0;
		for (; it(); ++it) {
			if (!(*it).isRun())
				(*it).update(window, time, q);
			q++;
		}
		

		/*
		if (!carOne.isRun())
		    carOne.update(window, time, 0);
		if (!carTwo.isRun())
		    carTwo.update(window, time, 1);
		if (!carThree.isRun())
		    carThree.update(window, time, 2);
		if (!carFour.isRun())
		    carFour.update(window, time, 3);
		if (!carFive.isRun())
		    carFive.update(window, time, 4);*/
		
		//Обновление Зомби
		int secondsFromStart = timerStart.getElapsedTime().asSeconds();
		//Если подошло время выпускать зомби, то выпустить его
		if (currentInRun != 10) {
			if ((secondsFromStart > timingsToGoZombie[currentInRun]) && (currentInRun <= 9)) {
				zombiesList[currentInRun].dx = -0.01;
				zombiesList[currentInRun].update(window, time);
				zombiesList[currentInRun].statusAviliable = false;
				zombiesList[currentInRun].isLive = true;
				zombiesList[currentInRun].isEaten = false;
				currentInRun++;
				timerStart.restart();
			}
		}
		//Перерисовка на каждом шаге тех, кто уже идет (и не ест)
		for (int i = 0; i < zombiesList.size(); ++i) {
			if ((zombiesList[i].statusAviliable == false) && (zombiesList[i].isEaten == false)) {
				if (zombiesList[i].isLive == false) 
					continue;
				zombiesList[i].dx = -0.01;
				zombiesList[i].update(window, time);
			}
		}
	
        //Перерисовка растений на карте
		for (int i = 0; i < vectorFlowersToRender.size(); i++) {
			if (listFlowers[i]->physic->health > 0)
			    heroToField(window, vectorFlowersToRender[i].second, vectorFlowersToRender[i].first);
		}

		////////////////////////////////////////////////////////
		//Атака растений//
		bool needToShoot = true;
		//Цикл по всем линиям (их 5)
		for (auto k = 0; k < 5; k++) {
			//Если хотя бы один из этих зомби идет по линии, то начать стрелять
			for (auto i = 0; i < numberZombieInLine[k].size(); ++i) {
				//Зомби должен пойти, чтобы цветок активировался
				if ((zombiesList[numberZombieInLine[k][i]].statusAviliable == false)&&(zombiesList[numberZombieInLine[k][i]].isLive == true)) {
					//Найдем все стоящие на этой линии растения и заставим их стрелять
					for (int j = 0; j < vectorFlowersToRender.size(); j++) {
						if (listFlowers[j]->image->reprinting == false) {
							coordinats tempCoordinats = vectorFlowersToRender[j].first;
							string nameFlower = vectorFlowersToRender[j].second;
							int xHigh = 296;
							int yLeft = 162;
							int CageX = (tempCoordinats.x+20 - xHigh) / 92;
							int CageY = (tempCoordinats.y+20 - yLeft) / 107;
							//Если растение в этой строке, то заставить его стрелять
							if (CageY == k) {
								listFlowers[j]->physic->zombieInWay = true;
								listFlowers[j]->image->posWeaponX = 296 + CageX * 92 - 20 + 100;
								listFlowers[j]->image->posWeaponY = 162 + CageY * 107;
								listFlowers[j]->image->reprinting = true;
								timeToCooldaun.restart();
								}
							}
						}
					}
				}
			}
		
		///////////////////////////////////////////////////////
		//Все растения (не все) из живых спискаРастений должны стрелять, если на них нападает зомби
		for (int i=0; i < listFlowers.size(); ++i) {
			if ((listFlowers[i]->physic->zombieInWay == true)&&((listFlowers[i]->physic->health > 0))) {
				bulletIsRendering[i] = true;
			}
		}

		//Перерисовать все пули
		for (int i = 0; i < bulletIsRendering.size(); ++i) {
			if (bulletIsRendering[i]) {
				if ((listFlowers[i]->physic->health > 0) && (listFlowers[i]->image->currentPicture != "modelПодсолнух.png") && (listFlowers[i]->image->currentPicture != "modelПоу.png") && (listFlowers[i]->image->currentPicture != "modelБомба.png")) {
					listFlowers[i]->image->dx = 0.1;
					listFlowers[i]->image->updateBullet(window, time);
					}
				}
			}
	

		//Нанесем урон всем зомби (урон всем растениям)
		for (int i = 0; i < 5; ++i) {
			for (int k = 0; k < numberZombieInLine[i].size(); ++k){
			//Это живой зомби
				if (zombiesList[numberZombieInLine[i][k]].isLive == true) {
					for (int j = 0; j < listFlowers.size(); j++)
						if ((zombiesList[numberZombieInLine[i][k]].x < listFlowers[j]->image->posWeaponX) && ((listFlowers[j]->physic->health > 0))) {
							//Линии должны совпадать
							if (((vectorFlowersToRender[j].first.y-142)/107 == i)) {
									//Получить урон от растения
									zombiesList[numberZombieInLine[i][k]].getDamage(listFlowers[j]->physic);
									if (zombiesList[numberZombieInLine[i][k]].health <= 0) {
										zombiesList[numberZombieInLine[i][k]].isLive = false;
										//Прекратить стрельбу при убийстве
										listFlowers[j]->physic->zombieInWay = false;
								}
								listFlowers[j]->image->reprinting = false;
								//Если зомби подошло к растению, то может его атаковать
								if (zombiesList[numberZombieInLine[i][k]].x <= vectorFlowersToRender[j].first.x + 60) {
									zombiesList[numberZombieInLine[i][k]].isEaten = true;
									zombiesList[numberZombieInLine[i][k]].setNextPictureEating(window);
									zombiesList[numberZombieInLine[i][k]].setDamage(listFlowers[j]->physic);
									//В след раз не перерисуется при смерти
								}
							}
						}
				}
			}
		}


		//Если прямоугольник тачки пересекся с прямоугольником зомби, то его необходимо переехать
		//Реализовать для всех!

		for (int i = 0; i < 5; i++) {
			int x1 = listCars.items[i].x + 32;
			listCars.items[i].carIsRunning(window, x1, zombiesList, numberZombieInLine[i], time);
		}



		//////////////////////////////////////////////////////////
		//Считаем позицию мыши при нажатии левой кнопки
		//Выберем определенную картинку
		bool tempBool = true;
		if (!heroIsReadyToBeStandToFeld) {
			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(pixelPos);
			Event eventClick;
			while (window.pollEvent(eventClick)) {
				if (eventClick.type == Event::MouseButtonPressed)
					if (eventClick.key.code == Mouse::Left) {
						for (auto i = 0; i < 6; i++)
						{
							if (isHitCard(placeCards[i], pos)) {
								//Выбрать карточку
								heroPath = paths[i];
								//Запретить заходить сюда при след отрисовке
								heroIsReadyToBeStandToFeld = true;
								tempBool = false;
								break;
							}
						}
					}
				if (!tempBool) break;
			}
			if (!tempBool) continue;
		}
		/////////////////////////////////////////////////////


		//Событие поставить героя на поле
		if (heroIsReadyToBeStandToFeld) {
			Vector2i fieldPos = Mouse::getPosition(window);
			Vector2f posField = window.mapPixelToCoords(fieldPos);
			Event eventToField;
			while (window.pollEvent(eventToField)) {
				if (eventToField.type == Event::MouseButtonPressed)
					if (eventToField.key.code == Mouse::Left) {
						//Определяем клетку
						int xStart = 296;
						int yStart = 162;
						int CageX = (posField.x - xStart) / 92;
						int CageY = (posField.y - yStart) / 107;
						//Нельзя выйти за пределы карты
						if (posField.x > 1128) break;
						if (FIELD_GAME_STATUS[CageY][CageX] == false)
							break;
						else
						{
							//Вставить в центр клетки с небольшим смещением влево
							coordinats temp;
							temp.x = 296 + CageX * 92 - 20;
							temp.y = 162 + CageY * 107 -20;
							if (heroPath == "Капуста.png")
								temp.x -= 15;
							heroToField(window, "model"+heroPath, temp);
							pair<coordinats, string> tempPair(temp, "model" + heroPath);
							FlowerPair* x;
							if (heroPath == "Подсолнух.png") {
								x = callObjectSunflower(play, sun_factory);
								if (balance - 50 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 50;
							}
							if (heroPath == "Капуста.png") {
								x = callObjectCabbage(play, cab_factory);
								if (balance - 100 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 100;
							}
							if (heroPath == "Поу.png") {
								x = callObjectNut(play, nut_factory);
								if (balance - 50 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 50;
							}
							if (heroPath == "Горошек.png") {
								x = callObjectPea(play, pea_factory);
								if (balance - 100 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 100;
							}
							if (heroPath == "Бомба.png") {
								x = callObjectBomb(play, bomb_factory);
								if (balance - 25 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 25;
							}
							if (heroPath == "Актиния.png") {
								x = callObjectActinia(play, act_factory);
								if (balance - 175 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 175;
							}
							FIELD_GAME_STATUS[CageY][CageX] = false;
							vectorFlowersToRender.push_back(tempPair);
							listFlowers.push_back(x);
							bulletIsRendering.push_back(false);
							//Герой уже поставлен
							heroIsReadyToBeStandToFeld = false;
							break;
						}
					}
			}
		}
		
		//Покажем баланс на счету
		//Рисовать от (600; 45)
		string sumString = std::to_string(balance);
		int startX = 600;
		int startY = 45;
		for (int i = 0; i < sumString.size(); ++i) {
			string filename;
			if (sumString[i] == '0') {
				filename = "0.png";
			}
			if (sumString[i] == '1') {
				filename = "1.png";
			}
			if (sumString[i] == '2') {
				filename = "2.png";
			}
			if (sumString[i] == '3') {
				filename = "3.png";
			}
			if (sumString[i] == '4') {
				filename = "4.png";
			}
			if (sumString[i] == '5') {
				filename = "5.png";
			}
			if (sumString[i] == '6') {
				filename = "6.png";
			}
			if (sumString[i] == '7') {
				filename = "7.png";
			}
			if (sumString[i] == '8') {
				filename = "8.png";
			}
			if (sumString[i] == '9') {
				filename = "9.png";
			}
			//Рисование цифр
			Image number;
			number.loadFromFile(filename);
			Texture map;
			map.loadFromImage(number);
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(startX, startY);
			startX += 50;
			window.draw(s_map);
		}


		//////////////////////////////////////////////////////////
		bool isNext = true;
		string gameOverSprite;
		//Если хотя бы один из зомби зашел на плацдарм, мы проиграли
		for (auto i = 0; i < zombiesList.size(); i++) {
			if (zombiesList[i].x < 195) {
				//Рисование картинки поражения
				Image mapLose;
				mapLose.loadFromFile("Проигрыш.png");
				Texture map;
				map.loadFromImage(mapLose);
				Sprite loser;
				loser.setTexture(map);
				//В полный экран
				loser.setPosition(0, 0);
				window.draw(loser);
			}
		}
		///////////////////////////////////////////////////////////
		//Отметим победу
		bool flag = true;
		int i = 0;
		for (i; i < zombiesList.size(); ++i) {
			if ((zombiesList[i].health <= 0)&&(zombiesList[i].statusAviliable == false)) continue;
			else break;
		}
		
		if (i == zombiesList.size()) {
			//Рисование картинки победы
			Image mapWin;
			mapWin.loadFromFile("Победа.jpg");
			Texture map;
			map.loadFromImage(mapWin);
			Sprite winner;
			winner.setTexture(map);
			//В полный экран
			winner.setPosition(0, 0);
			window.draw(winner);
		}
		//////////////////////////////////////////////////////////
		window.setSize(sf::Vector2u(550, 340));
		window.display();
	}
	return 0;
}
