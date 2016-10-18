#include "Car.h"

USING_NS_CC;

/*Car::Car()
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
		this->setPosition(this->definePosition(Ambulance));
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
		this->setPosition(this->definePosition(Black_viper));
		break;
	case 2:
		type = Orange_car;
		speed = this->defineSpeed(70, 30);
		this->initWithSpriteFrameName("Car.png");
		this->setPosition(this->definePosition(Orange_car));

		//		this->initWithFile("cars/Car.png");
		break;
	case 3:
		type = Mini_truck;
		speed = this->defineSpeed(50, 10);
		this->initWithSpriteFrameName("Mini_truck.png");
		this->setPosition(this->definePosition(Mini_truck));

		//	this->initWithFile("cars/Mini_truck.png");
		break;
	case 4:
		type = Mini_van;
		speed = this->defineSpeed(60, 20);
		this->initWithSpriteFrameName("Mini_van.png");
		this->setPosition(this->definePosition(Mini_van));

		//		this->initWithFile("cars/Mini_van.png");
		break;
	case 5:
	{
		type = Police;
		speed = this->defineSpeed(100, 60);
		//	this->initWithSpriteFrameName("Black_viper.png");

		this->initWithSpriteFrameName("Police.png");
		this->setPosition(this->definePosition(Police));

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
		this->setPosition(this->definePosition(Taxi));

		//	this->initWithFile("cars/Taxi.png");
		break;
	case 7:
		type = Truck;
		speed = this->defineSpeed(40, 40);
		this->initWithSpriteFrameName("Truck.png");
		this->setPosition(this->definePosition(Truck));

		//	this->initWithFile("cars/Truck.png");
		break;
	default:
		type = Orange_car;
		speed = this->defineSpeed(70, 30);
		this->initWithSpriteFrameName("Car.png");
		this->setPosition(this->definePosition(Orange_car));

		break;
	}
}
*/
Car::Car() {
	int current_type = 20 * CCRANDOM_0_1();
	if (current_type < 4)
		type = Orange_car;
	else if (current_type < 8)
		type = Taxi;
	else if (current_type < 11)
		type = Black_viper;
	else if (current_type < 14)
		type = Mini_van;
	else if (current_type < 16)
		type = Mini_truck;
	else if (current_type < 17)
		type = Truck;
	else if (current_type < 19)
		type = Ambulance;
	else type = Police;
	this->define(type);
}

void Car::define(CarType type) {
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("cars/Cars_sheet.plist");
	switch (type) {
	case Ambulance:
	{
		speed = this->setSpeed(100, 20);
		this->initWithSpriteFrameName("Ambulance.png");
		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * int(2 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		Vector<SpriteFrame*> animFrames;
		animFrames.pushBack(spritecache->getSpriteFrameByName("Ambulance1.png"));
		animFrames.pushBack(spritecache->getSpriteFrameByName("Ambulance2.png"));
		animFrames.pushBack(spritecache->getSpriteFrameByName("Ambulance3.png"));
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
		this->runAction(RepeatForever::create(Animate::create(animation)));
		break;
	}
	case Black_viper:
		speed = this->setSpeed(140, 60);
		this->initWithSpriteFrameName("Black_viper.png");
		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * int(2 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Orange_car:
		speed = this->setSpeed(100, 40);
		this->initWithSpriteFrameName("Car.png");
		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * int(4 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Mini_truck:
		speed = this->setSpeed(70, 30);
		this->initWithSpriteFrameName("Mini_truck.png");
		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * 2 + ROAD_LINE_WIDTH * int(2 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Mini_van:
		speed = this->setSpeed(80, 20);
		this->initWithSpriteFrameName("Mini_van.png");
		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * 2 + ROAD_LINE_WIDTH * int(2 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Police:
	{
		speed = this->setSpeed(120, 60);
		
		this->initWithSpriteFrameName("Police.png");
		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * int(2 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));

		Vector<SpriteFrame*> animFrames;
		animFrames.pushBack(spritecache->getSpriteFrameByName("Police1.png"));
		animFrames.pushBack(spritecache->getSpriteFrameByName("Police2.png"));
		animFrames.pushBack(spritecache->getSpriteFrameByName("Police3.png"));
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		this->runAction(RepeatForever::create(Animate::create(animation)));
		break;
	}
	case Taxi:
		speed = this->setSpeed(100, 40);
		this->initWithSpriteFrameName("Taxi.png");
		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * int(4 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Truck:
		speed = this->setSpeed(60, 20);
		this->initWithSpriteFrameName("Truck.png");
		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * 3, 3 * RESOLUTION_Y / 2));
		break;
	default:
		break;
	}

	CCLOG("%i, %f, speed=%i", this->getType(), this->getPositionX(), this->getDefaultSpeed());
}

int Car::setSpeed(int minSpeed, int deltaSpeed)
{
	defaultSpeed = minSpeed + deltaSpeed * CCRANDOM_0_1();
	return defaultSpeed;
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

int Car::getType()
{
	return this->type;
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

}

void Car::moveToRightLine(int carSpeed)
{
	auto rotateBy = RotateBy::create(0.1, 10.0f);
	auto rotateOut = RotateBy::create(0.1, -10.0f);

	auto moveTo1 = MoveTo::create(0.3, Vec2(this->getPositionX() + ROAD_LINE_WIDTH, this->getPositionY() - 0.1 * (carSpeed - this->getSpeed())));
	auto moveTo = MoveTo::create(0.3, Vec2(this->getPositionX() + ROAD_LINE_WIDTH, this->getPositionY() - 0.2 * (carSpeed - this->getSpeed())));

	auto mySpawn = Spawn::createWithTwoActions(rotateBy, moveTo1);
	auto mySpawn2 = Spawn::createWithTwoActions(rotateOut, moveTo);


	auto seq = Sequence::create(mySpawn, mySpawn2, nullptr);
	seq->setTag(1);
	this->runAction(seq);

}

void Car::setMoveOption(bool f, bool l, bool r)
{
	moveOption = new MoveOption(f, l, r);
}
