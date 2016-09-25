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
		speed = this->defineSpeed(120, 30);
		this->initWithSpriteFrameName("Black_viper.png");
		//this->initWithFile("cars/Black_viper.png");
		break;
	case 2:
		type = Orange_car;
		speed = this->defineSpeed(70, 30);
		this->initWithSpriteFrameName("Car.png");

		//		this->initWithFile("cars/Car.png");
		break;
	case 3:
		type = Mini_truck;
		speed = this->defineSpeed(50, 10);
		this->initWithSpriteFrameName("Mini_truck.png");

		//	this->initWithFile("cars/Mini_truck.png");
		break;
	case 4:
		type = Mini_van;
		speed = this->defineSpeed(60, 20);
		this->initWithSpriteFrameName("Mini_van.png");

		//		this->initWithFile("cars/Mini_van.png");
		break;
	case 5:
	{
		type = Police;
		speed = this->defineSpeed(100, 60);
		//	this->initWithSpriteFrameName("Black_viper.png");

		this->initWithSpriteFrameName("Police.png");

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
		speed = this->defineSpeed(60, 40);
		this->initWithSpriteFrameName("Taxi.png");

		//	this->initWithFile("cars/Taxi.png");
		break;
	case 7:
		type = Truck;
		speed = this->defineSpeed(40, 40);
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
	currentLine = posX;
	//	CCLOG("Car line position: %i", posX);
	return Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * posX, 3 * RESOLUTION_Y / 2);  
}

int Car::defineSpeed(int minSpeed, int deltaSpeed)
{
	int speed = minSpeed + deltaSpeed/* * CCRANDOM_0_1()*/;
	defaultSpeed = speed;
	//	CCLOG("%i", speed);
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

int Car::getDefaultSpeed()
{
	return defaultSpeed;
}

void Car::decreaseSpeed(int carSpeed)
{
	if (this->getSpeed() > 40)
		this->modifySpeed(this->getSpeed() - 5);
	this->setPosition(Vec2(this->getPositionX(), this->getPositionY() - 0.1 * (carSpeed - this->getSpeed())));
}

void Car::increaseSpeed(int carSpeed)
{
	if (this->getSpeed() < this->getDefaultSpeed())
		this->modifySpeed(this->getSpeed() + 5);
	this->setPosition(Vec2(this->getPositionX(), this->getPositionY() - 0.1 * (carSpeed - this->getSpeed())));
}

void Car::moveToLeftLine(int carSpeed)
{
	auto rotateBy = RotateBy::create(0.1, -10.0f);
	auto rotateOut = RotateBy::create(0.1, 10.0f);

	auto moveTo1 = MoveTo::create(0.3, Vec2(this->getPositionX() - ROAD_LINE_WIDTH, this->getPositionY() - 0.1 * (carSpeed - this->getSpeed())));
	auto moveTo = MoveTo::create(0.3, Vec2(this->getPositionX() - ROAD_LINE_WIDTH, this->getPositionY() - 0.2 * (carSpeed - this->getSpeed())));

	auto mySpawn = Spawn::createWithTwoActions(rotateBy, moveTo1);
	auto mySpawn2 = Spawn::createWithTwoActions(rotateOut, moveTo);


	auto seq = Sequence::create(mySpawn, mySpawn2, nullptr);
	seq->setTag(1);
	this->runAction(seq);

	/*auto first = MoveTo::create(0.3, Vec2(this->getPositionX() - ROAD_LINE_WIDTH, this->getPositionY() - 0.1 * (carSpeed - this->getSpeed())));
	first->setTag(1);
	this->runAction(first);*/
}

void Car::moveToRightLine(int carSpeed)
{
	/*Скорость должна зависеть от carSpeed как по х так и по у (Придумать как)
	**Можно использовать easeIn easeOut для каждого из движений
																*/
	auto rotateBy = RotateBy::create(0.1, 10.0f);
//	auto rotateByWithEasing = EaseOut::create(rotateBy->clone(),0.1);
	auto rotateOut = RotateBy::create(0.1, -10.0f);
//	auto rotateOutWithEasing = EaseOut::create(rotateOut->clone(),0.1);

	auto moveTo1 = MoveTo::create(0.3, Vec2(this->getPositionX() + ROAD_LINE_WIDTH, this->getPositionY() - 0.1 * (carSpeed - this->getSpeed())));
	auto moveTo = MoveTo::create(0.3, Vec2(this->getPositionX() + ROAD_LINE_WIDTH, this->getPositionY() - 0.2 * (carSpeed - this->getSpeed())));

	auto mySpawn = Spawn::createWithTwoActions(rotateBy, moveTo1);
	auto mySpawn2 = Spawn::createWithTwoActions(rotateOut, moveTo);


	auto seq = Sequence::create(mySpawn, mySpawn2, nullptr);
	seq->setTag(1);
	this->runAction(seq);

	/*auto first = MoveTo::create(0.3, Vec2(this->getPositionX() + ROAD_LINE_WIDTH, this->getPositionY() - 0.1 * (carSpeed - this->getSpeed())));
	first->setTag(1);
	this->runAction(first);*/
}

void Car::setMoveOption(bool f, bool l, bool r)
{
	moveOption = new MoveOption(f, l, r);
}
