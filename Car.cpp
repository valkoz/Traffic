#include "Car.h"

USING_NS_CC;

Car::Car()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->initWithFile("cars/Audi.png");
	this->setPosition(this->definePosition());
	speed = this->defineSpeed();
}

Point Car::definePosition()
{
	int posX = 4 * CCRANDOM_0_1();
	CCLOG("Car line position: %i", posX);
	return Point(120 + 160*posX,1280);
}

int Car::defineSpeed()
{
	int speed = 20 + 160 * CCRANDOM_0_1();
	CCLOG("%i", speed);
	return speed;
}

Car* Car::create()
{
	Car* tmp = new Car();
	if (tmp->init())
	{
		tmp->autorelease();
		return tmp;
	}
	CC_SAFE_DELETE(tmp);
	return NULL;
}

void Car::modifySpeed(int sp)
{
	speed = sp;
	return;
}

int Car::getSpeed()
{
	return speed;
}
 
