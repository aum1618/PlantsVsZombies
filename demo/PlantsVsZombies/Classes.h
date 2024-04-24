#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;
using namespace std;

//Изображение растения на карте
class FlowerImage {
public:
	//Изображение растения (ссылка)
	string currentPicture;
	//Cнаряды (ссылка на картинку)
	string weapon;
	int posWeaponX;
	int posWeaponY;
	//Вызывающее действие
	string doing;
	//Скорость полета оружия
	double dx;
	//Перерисовывается (состояние)
	bool reprinting = false;
	//Модель растения
	virtual void setModel() = 0;
	//Позиция вылета снаряда
	virtual void weaponFrom() = 0;
	//Скорость полета снаряда
	virtual void setSpeedDx(double) = 0;
	//Установка вызывающего действия
	virtual void setDoing() = 0;
	//Обновление изображения пули
	virtual void updateBullet(RenderWindow& window, double time) = 0;
};
//Обработка для Подсолнуха
class SunflowerImage : public FlowerImage {
	void setDoing() {
		doing = "Кушать";
	}
	void weaponFrom() {};
	void setSpeedDx(double a) {
		dx = a;
	}
	void setModel() {
		currentPicture = "modelПодсолнух.png";
	}
	void updateBullet(RenderWindow& window, double time) {};
};

//Обработка для Горошка
class PeaImage : public FlowerImage {
	void weaponFrom() {
		weapon = "снарядГорошек.png";
		//Позиция вылета снаряда на картинке
		posWeaponX = 100;
		posWeaponY = 28;
	}

	void setSpeedDx(double speed) {
		dx = speed;
	}

	void setDoing() {
		doing = "Кушать";
	}
	void setModel() {
		currentPicture = "modelГорошек.png";
	}
	void updateBullet(RenderWindow& window, double time) {
		posWeaponX += dx * time;
		//Загрузка новой анимации

		Image bulletRender;
		bulletRender.loadFromFile("снарядГорошек.png");
		Texture texture;
		texture.loadFromImage(bulletRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//Создание новых координат для пули
		newSprite.setTextureRect(IntRect(0, 0, 40, 40));
		newSprite.setPosition(posWeaponX, posWeaponY);
		//dx = 0;
		//Нарисовать эти координаты
		window.draw(newSprite);
	}
};
//Обработка для Капусты
class CabbageImage : public FlowerImage {
	void weaponFrom() {
		weapon = "снарядКапуста.png";
		//Позиция вылета снаряда на картинке
		posWeaponX = 13;
		posWeaponY = 20;
	}
	void setSpeedDx(double speed = 0.03) {
		dx = speed;
	}
	void setDoing() {
		doing = "Кушать";
	}
	void setModel() {
		currentPicture = "modelКапуста.png";
	}
	void updateBullet(RenderWindow& window, double time) {
		posWeaponX += dx * time;
		//Загрузка новой анимации

		Image bulletRender;
		bulletRender.loadFromFile("снарядКапуста.png");
		Texture texture;
		texture.loadFromImage(bulletRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//Создание новых координат для пули
		newSprite.setTextureRect(IntRect(0, 0, 80, 80));
		newSprite.setPosition(posWeaponX, posWeaponY);
		//dx = 0;
		//Нарисовать эти координаты
		window.draw(newSprite);
	}
};

//Обработка для Ореха
class NutImage : public FlowerImage {
	void setDoing() {
		doing = "Кушать";
	}
	void weaponFrom() {};
	void setSpeedDx(double a) {};
	void setModel() {
		currentPicture = "modelОрех.png";
	}
	void updateBullet(RenderWindow& window, double time) {};
};

//Обработка для Актинии
class ActiniaImage : public FlowerImage {
	void weaponFrom() {
		weapon = "сюрикен1.png";
		//Позиция вылета снаряда на картинке
		posWeaponX = 103;
		posWeaponY = 28;
	}

	void setSpeedDx(double speed = 0.03) {
		//dx = speed;
	}
	void setDoing() {
		doing = "Кушать";
	}
	void setModel() {
		currentPicture = "modelАктиния.png";
	}
	void updateBullet(RenderWindow& window, double time) {
		posWeaponX += dx * time;
		//Загрузка новой анимации

		Image bulletRender;
		if (posWeaponX % 2 == 0)
			bulletRender.loadFromFile("сюрикен1.png");
		else
			bulletRender.loadFromFile("сюрикен2.png");
		Texture texture;
		texture.loadFromImage(bulletRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//Создание новых координат для пули
		newSprite.setTextureRect(IntRect(0, 0, 40, 40));
		newSprite.setPosition(posWeaponX, posWeaponY);
		//Нарисовать эти координаты
		window.draw(newSprite);
	}

};

//Обработка для бомбы
class BombImage : public FlowerImage {
	void setDoing() {
		doing = "Кушать";
	}
	void weaponFrom() {};
	void setSpeedDx(double a) {};
	void setModel() {
		currentPicture = "modelБомба.png";
	}
	void updateBullet(RenderWindow& window, double time) {};
};
//Интерфейс "Физика цветка" и 5 реализаций для него
class FlowerPhysic {
public:
	int health;
	int damage;
	//true, если нужно (атаковать)
	bool zombieInWay;
	bool isAvialiable;
	int weaponX;
	Clock timeToCooldaun;
public:
	//Количество здоровья, урон, модель
	virtual void setHealthPoint(int) = 0;
	virtual void setDamagePoint(int) = 0;
	virtual int getHealthPoint() = 0;
	virtual int getDamage() = 0;
	// Необходимость активироваться
	virtual bool needToActivate(int) = 0;


	void ripFlower() {
		isAvialiable = false;
	}

	bool isOnMap() {
		return isAvialiable;
	}

	virtual ~FlowerPhysic() {}
};

//Реализации для каждого из цветков

//Подсолнух нежится на солнышке
class SunflowerPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 100) {
		health = point;
	}
	void setDamagePoint(int point = 0) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int i = 1) {
		zombieInWay = true;
		return zombieInWay;
	}
	virtual ~SunflowerPhysic() {}
};
//Горошек плюет горошинами (больно) 
class PeaPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 150) {
		health = point;
	}
	void setDamagePoint(int point = 20) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - координата горошка
		//x2 - координата зомби
		//Если зомби правее пули, то активироваться
		if (x2 > weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}
	virtual ~PeaPhysic() {}
};

//Орех - сильный блок, его тяжело раскусить!
class NutPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 150) {
		health = point;
	}
	void setDamagePoint(int point = 0) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - координата горошка
		//x2 - координата зомби
		//Если зомби правее пули, то активироваться
		if (x2 > weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}

	virtual ~NutPhysic() {}
};

//Капуста - не промахивается кочерыжками!
class CabbagePhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 100) {
		health = point;
	}
	void setDamagePoint(int point = 30) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - координата ореха
		//x2 - координата зомби
		//Если зомби правее , то активироваться
		if (x2 < weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}
	virtual ~CabbagePhysic() {}
};

//Актиния имеет сюрикены, бойся!
class ActiniaPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 120) {
		health = point;
	}
	void setDamagePoint(int point = 10) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - координата бомбы
		//x2 - координата зомби
		//Если зомби левее бомбы, то активироваться
		if (x2 < weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}
	virtual ~ActiniaPhysic() {}
};

//Бомба - ты в ловушке!
class BombPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 0) {
		health = point;
	}
	void setDamagePoint(int point = 0) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - координата сюрикена
		//x2 - координата зомби
		//Если зомби правее сюрикена, то активироваться
		if (x2 > weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}

	virtual ~BombPhysic() {}
};

//Абстрактная фабрика растений
class FlowerFactory {
public:
	virtual FlowerImage* makeFlower() = 0;
	virtual FlowerPhysic* makePhysic() = 0;
};

//Фабрика Подсолнухов возвращает Подсолнух и его Физику
//Аналогично, для остальных растений
class SunflowersFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new SunflowerImage();
	}
	FlowerPhysic* makePhysic() {
		return new SunflowerPhysic();
	}
};

class PeaFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new PeaImage();
	}
	FlowerPhysic* makePhysic() {
		return new PeaPhysic();
	}
};

class CabbageFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new CabbageImage();
	}
	FlowerPhysic* makePhysic() {
		return new CabbagePhysic();
	}
};

class NutFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new NutImage();
	}
	FlowerPhysic* makePhysic() {
		return new NutPhysic();
	}
};

class ActiniaFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new ActiniaImage();
	}
	FlowerPhysic* makePhysic() {
		return new ActiniaPhysic();
	}
};

class BombFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new BombImage();
	}
	FlowerPhysic* makePhysic() {
		return new BombPhysic();
	}
};

//Класс, в котором пара (Изображение, Физика)
class FlowerPair
{
public:
	FlowerImage* image;
	FlowerPhysic* physic;
};

//Класс с заполненной парой (Изображения и физики)
class Flower {
public:
	FlowerPair* createFlower(FlowerFactory& factory) {
		FlowerPair* p = new FlowerPair;
		p->image = factory.makeFlower();
		p->physic = factory.makePhysic();
		return p;
	}
};
/////////////////////////////////////////////////////////
//Класс "Зомби"
class Zombie {
public:
	//Изменение по оси x
	//Для зомби всегда против оси
	float dx;
	float dy;
	string fileName;
	//Помещение картинки
	float x;
	float y;
	Sprite sprite;
	//Доступность
	bool statusAviliable;
	//Количество жизней и урон
	int health;
	int damage;
	//Текущее состояние жизни
	bool isLive;
	//Сейчас - кушает
	bool isEaten;

	//Конструктор 
	Zombie(RenderWindow &window, int posLine) {
		//Зомби доступно для первого взятия
		statusAviliable = true;
		isLive = false;
		isEaten = false;
		Image ZombieRender;
		//загружаем файл для карты
		fileName = "zombieOnPlace.png";
		ZombieRender.loadFromFile(fileName);
		Texture texture;
		texture.loadFromImage(ZombieRender);
		sprite.setTexture(texture);
		//Случайная позиция на любом из квадратов (из 5)
		srand(time(0));
		x = 1100;
		//Параллельно "тачкам"
		y = 125 + (posLine - 1) * 110;
		dx = -0.01;
		sprite.setTextureRect(IntRect(0, 0, 140, 140));
		sprite.setPosition(x, y);
		health = 150;
		damage = 10;
	}

	//Движение зомби
	void update(RenderWindow &window, float time) {
		x += dx * time;
		//Загрузка новой анимации
		if (fileName.find("On") != -1)
			fileName = "zombieInRun.png";
		else
			fileName = "zombieOnPlace.png";

		Image ZombieRender;
		ZombieRender.loadFromFile(fileName);
		Texture texture;
		texture.loadFromImage(ZombieRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//Создание новых координат для зомби
		newSprite.setTextureRect(IntRect(0, 0, 140, 140));
		newSprite.setPosition(x, y);
		dx = 0;
		//Нарисовать эти координаты
		window.draw(newSprite);

	}

	double myDamage() {
		return damage;
	}

	//Сделать недоступным для повторного взятия
	void setUnvialible() {
		statusAviliable = false;
	}

	//Проверка на доступность
	bool isAvialible() {
		return statusAviliable;
	}

	//Получение урона (от цветка)
	void getDamage(FlowerPhysic* someFlower) {
		health -= someFlower->getDamage();
		if (health <= 0)
			ripZombie();
	}

	//Цветок получает урон
	void setDamage(FlowerPhysic* someFlower) {
		someFlower->health -= damage;
		if (someFlower->health <= 0) {
			someFlower->ripFlower();
			this->isEaten = false;
		}
	}

	//Зомби умер
	void ripZombie() {
		statusAviliable = false;
	}

	bool isZombieRip() {
		return statusAviliable;
	}

	//Смена картинок при еде
	void setNextPictureEating(RenderWindow& window) {
		//Загрузка новой анимации
		if (fileName.find("Ест") == -1)
			fileName = "ЗомбиЕст.png";
		else
			fileName = "zombieOnPlace.png";

		Image ZombieRender;
		ZombieRender.loadFromFile(fileName);
		Texture texture;
		texture.loadFromImage(ZombieRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//Создание новых координат для зомби
		newSprite.setTextureRect(IntRect(0, 0, 140, 140));
		newSprite.setPosition(x, y);
		dx = 0;
		//Нарисовать эти координаты
		window.draw(newSprite);
	}
};

///////////////////////////////////////////
// Класс "Тележка"
class Car {
public:
	//Изменение по оси x
	//Для машины всегда по оси
	float dx;
	string fileName;
	//Помещение картинки
	float x;
	float y;
	Sprite sprite;
	bool isRunningStatus;

	//Конструктор 
	Car(RenderWindow &window, int numberCar) {
		Image car;
		//загружаем файл для тачки
		car.loadFromFile("modelТачка.png");
		Texture texture;
		texture.loadFromImage(car);
		sprite.setTexture(texture);
		//Координата левого верхнего угла, ширина и высота
		sprite.setTextureRect(IntRect(0, 0, 120, 120));
		//В определенных квадратах
		auto i = numberCar;
		sprite.setPosition(190, 140 + i * 110);
		x = 190;
		y = 140 + i * 110;
		dx = 0.1;
		isRunningStatus = false;
		window.draw(sprite);
	}
	//Движение машины (движение вправо)
	void update(RenderWindow &window, float time, int num) {
		x += dx * time;

		Image car;
		//загружаем файл для тачки
		car.loadFromFile("modelТачка.png");
		Texture texture;
		texture.loadFromImage(car);
		sprite.setTexture(texture);
		//Координата левого верхнего угла, ширина и высота
		sprite.setTextureRect(IntRect(0, 0, 120, 120));

		//Создание новых координат для машины
		sprite.setPosition(x, y);
		dx = 0;
		//Нарисовать эти координаты
		window.draw(sprite);
	}

	bool isRun() {
		return isRunningStatus;
	}

	//Движение машины
	void carIsRunning(RenderWindow& window, int x1, vector<Zombie> &listZombies, vector<int> zombiesInLine, double time) {
		for (auto i = 0; i < zombiesInLine.size(); i++) {
			int x2 = listZombies[zombiesInLine[i]].x;
			if ((x1 > x2) && (x1 < 1100)) {
				dx = 0.02;
				update(window, time, 0);
				listZombies[zombiesInLine[i]].isLive = false;
				listZombies[zombiesInLine[i]].health = -1;
				isRunningStatus = true;
			}
		}
	}

	void getDamage(Zombie* zombie) {
		zombie->health -= 200;
		if (zombie->health <= 0)
			zombie->ripZombie();
	}

};


//Коллекция машин
class CarCollection {
public:
	friend class CarsIterator;
	vector<Car> items;
	int position;
	CarCollection() {
		position = -1;
	}
	void push(Car in)
	{
		items.push_back(in);
	}
	Car pop()
	{
		return items[position--];
	}
	bool isEmpty()
	{
		return (position == -1);
	}

};

//Итератор по машинам
class CarIterator
{
	const CarCollection &car;
	int index;
public:
	CarIterator(const CarCollection &s) : car(s)
	{
		index = 0;
	}
	void operator++()
	{
		index++;
	}
	void operator--()
	{
		index--;
	}
	bool operator()()
	{
		return index != 5;
	}
	Car operator *()
	{
		return car.items[index];
	}
};
