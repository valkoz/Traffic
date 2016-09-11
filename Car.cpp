#include "Car.h"

USING_NS_CC;

Car::Car()
{
	int current_type = 8 * CCRANDOM_0_1();
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("cars/Cars_sheet.plist");

	switch (current_type) {
	case 0:
	{
		type = Ambulance;
		speed = this->defineSpeed(100, 20);
		this->initWithSpriteFrameName("Ambulance.png");

		Vector<SpriteFrame*> animFrames;
		animFrames.pushBack(spritecache->getSpriteFrameByName("Ambulance1.png"));
		animFrames.pushBack(spritecache->getSpriteFrameByName("Ambulance2.png"));
		animFrames.pushBack(spritecache->getSpriteFrameByName("Ambulance3.png"));
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
		this->runAction(RepeatForever::create(Animate::create(animation)));
		break;
	}
	case 1:
		type = Black_viper;
		speed = this->defineSpeed(120,30);
		this->initWithSpriteFrameName("Black_viper.png");
		//this->initWithFile("cars/Black_viper.png");
		break;
	case 2:
		type = Orange_car;
		speed = this->defineSpeed(70,30);
		this->initWithSpriteFrameName("Car.png");

//		this->initWithFile("cars/Car.png");
		break;
	case 3:
		type = Mini_truck;
		speed = this->defineSpeed(50,10);
		this->initWithSpriteFrameName("Mini_truck.png");

	//	this->initWithFile("cars/Mini_truck.png");
		break;
	case 4:
		type = Mini_van;
		speed = this->defineSpeed(60,20);
		this->initWithSpriteFrameName("Mini_van.png");

//		this->initWithFile("cars/Mini_van.png");
		break;
	case 5:
	{
		type = Police;
		speed = this->defineSpeed(100, 60);
	//	this->initWithSpriteFrameName("Black_viper.png");

		this->initWithFile("cars/Police.png");

		Vector<SpriteFrame*> animFrames;
		animFrames.pushBack(spritecache->getSpriteFrameByName("Police1.png"));
		animFrames.pushBack(spritecache->getSpriteFrameByName("Police2.png"));
		animFrames.pushBack(spritecache->getSpriteFrameByName("Police3.png"));
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		this->runAction(RepeatForever::create(Animate::create(animation)));
		break;
	}
	case 6:
		type = Taxi;
		speed = this->defineSpeed(60,40);
		this->initWithSpriteFrameName("Taxi.png");

	//	this->initWithFile("cars/Taxi.png");
		break;
	case 7:
		type = Truck;
		speed = this->defineSpeed(40,40);
		this->initWithSpriteFrameName("Truck.png");

	//	this->initWithFile("cars/Truck.png");
		break;
	default:
		type = Orange_car;
		speed = this->defineSpeed(70, 30);
		this->initWithSpriteFrameName("Car.png");
		break;
	}
	this->setPosition(this->definePosition());
}

Point Car::definePosition()
{
	int posX = 4 * CCRANDOM_0_1();
	CCLOG("Car line position: %i", posX);
	return Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * posX, RESOLUTION_Y);
}

int Car::defineSpeed(int minSpeed, int deltaSpeed)
{
	int speed = minSpeed + deltaSpeed * CCRANDOM_0_1();
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
 
