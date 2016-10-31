#include "PhysicsCar.h"
#include <array>
USING_NS_CC;

PhysicsCar::PhysicsCar() {
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

void PhysicsCar::define(CarType type) {
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("cars/Cars_sheet.plist");
	float height = 0;
	float width = 0;
	PhysicsBody *body = nullptr;
	std::array<Point, 12> coord;
	switch (type) {
	case Ambulance:
	{
		speed = this->setSpeed(120, 60);
		this->initWithSpriteFrameName("Ambulance.png");

		height = this->getBoundingBox().size.height;
		width = this->getBoundingBox().size.width;
		coord = { Point(-this->getBoundingBox().size.width / 2 + 10,  -this->getBoundingBox().size.height / 2),
			Point(-this->getBoundingBox().size.width / 2 + 10, this->getBoundingBox().size.height / 2 - 10),
			Point(this->getBoundingBox().size.width / 2 - 10,  this->getBoundingBox().size.height / 2 - 10),
			Point(this->getBoundingBox().size.width / 2 - 10, -this->getBoundingBox().size.height / 2),
			Point(this->getBoundingBox().size.width / 2 - 20,  this->getBoundingBox().size.height / 2),
			Point(-this->getBoundingBox().size.width / 2 + 20,  this->getBoundingBox().size.height / 2) };
		body = PhysicsBody::createPolygon(coord.data(), 6);
		body->setCollisionBitmask(2);	
		body->setDynamic(false);
		body->setContactTestBitmask(true);
		this->setPhysicsBody(body);

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

		height = this->getBoundingBox().size.height;
		width = this->getBoundingBox().size.width;
		coord = { Point(-40,-105), Point(40, -105),
			Point(42, -50), Point(45,70), Point(25, 105), Point(-25,105),
			Point(-45, 70), Point(-42,-50) };
		body = PhysicsBody::createEdgePolygon(coord.data(), 8);
		body->setCollisionBitmask(2);
		body->setContactTestBitmask(true);

		this->setPhysicsBody(body);


		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * int(2 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Orange_car:
		speed = this->setSpeed(100, 40);
		this->initWithSpriteFrameName("Car.png");

		height = this->getBoundingBox().size.height;
		width = this->getBoundingBox().size.width;
		coord = { Point(-width / 2 + 5 ,  -height / 2),
			Point(-width / 2 + 5 , height / 2),
			Point(width / 2 - 5 ,  height / 2),
			Point(width / 2 - 5 , -height / 2) };
		body = PhysicsBody::createEdgePolygon(coord.data(), 4);
		body->setCollisionBitmask(2);
		body->setContactTestBitmask(true);

		this->setPhysicsBody(body);
		

		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * int(4 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Mini_truck:
		speed = this->setSpeed(70, 30);
		this->initWithSpriteFrameName("Mini_truck.png");

		height = this->getBoundingBox().size.height;
		width = this->getBoundingBox().size.width;
		coord = { Point(-width / 2 + 10 ,  -height / 2),
			Point(-width / 2 + 10 , height / 2),
			Point(width / 2 - 10 ,  height / 2),
			Point(width / 2 - 10 , -height / 2) };
		body = PhysicsBody::createEdgePolygon(coord.data(), 4);
		body->setCollisionBitmask(2);
		body->setContactTestBitmask(true);

		this->setPhysicsBody(body);


		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * 2 + ROAD_LINE_WIDTH * int(2 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Mini_van:
		speed = this->setSpeed(80, 20);
		this->initWithSpriteFrameName("Mini_van.png");

		height = this->getBoundingBox().size.height;
		width = this->getBoundingBox().size.width;
		coord = { Point(-width / 2 + 5 * width / 46,  -height / 2),
			Point(-width / 2 + 5 * width / 46, height / 2 - height / 8),
			Point(width / 2 - 5 * width / 46,  height / 2 - height / 8),
			Point(width / 2 - 5 * width / 46, -height / 2),
			Point(width / 2 - 30 * width / 46, height / 2),
			Point(-width / 2 + 30 * width / 46, height / 2) };
		body = PhysicsBody::createPolygon(coord.data(), 6);
		body->setDynamic(false);
		body->setCollisionBitmask(2);
		body->setContactTestBitmask(true);

		this->setPhysicsBody(body);


		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * 2 + ROAD_LINE_WIDTH * int(2 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Police:
	{
		speed = this->setSpeed(120, 60);
		
		this->initWithSpriteFrameName("Police.png");

		height = this->getBoundingBox().size.height;
		width = this->getBoundingBox().size.width;
		coord = { Point(-3 * width / 10 ,-height / 2), Point(3 * width / 10, -height / 2),
			Point(46 * width / 100, -85 * height / 200), Point(48 * width / 100, -60 * height / 200),
			Point(35 * width / 100, -50 * height / 200), Point(48 * width / 100,70 * height / 200),
			Point(2 * width / 10, height / 2), Point(-2 * width / 10 , height / 2),
			Point(-48 * width / 100, 70 * height / 200), Point(-35 * width / 100,-50 * height / 200),
			Point(-48 * width / 100,-60 * height / 200), Point(-46 * width / 100, -85 * height / 200) };
		body = PhysicsBody::createEdgePolygon(coord.data(), 12);
		body->setCollisionBitmask(2);
		body->setContactTestBitmask(true);

		this->setPhysicsBody(body);


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

		height = this->getBoundingBox().size.height;
		width = this->getBoundingBox().size.width;
		coord = { Point(-width / 2 + 10 ,  -height / 2),
			Point(-width / 2 + 10 , height / 2),
			Point(width / 2 - 10 ,  height / 2),
			Point(width / 2 - 10 , -height / 2) };
		body = PhysicsBody::createEdgePolygon(coord.data(), 4);
		body->setCollisionBitmask(2);
		body->setContactTestBitmask(true);

		this->setPhysicsBody(body);


		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * int(4 * CCRANDOM_0_1()), 3 * RESOLUTION_Y / 2));
		break;
	case Truck:
		speed = this->setSpeed(60, 20);
		this->initWithSpriteFrameName("Truck.png");

		height = this->getBoundingBox().size.height;
		width = this->getBoundingBox().size.width;
		coord = { Point(-width / 2 + 5 ,  -height / 2),
			Point(-width / 2 + 5 , height / 2),
			Point(width / 2 - 5 ,  height / 2),
			Point(width / 2 - 5 , -height / 2) };
		body = PhysicsBody::createEdgePolygon(coord.data(), 4);
		body->setCollisionBitmask(2);
		body->setContactTestBitmask(true);

		this->setPhysicsBody(body);


		this->setPosition(Point(LEFT_CAR_POSITION + ROAD_LINE_WIDTH * 3, 3 * RESOLUTION_Y / 2));
		break;
	default:
		break;
	}

	CCLOG("%i, %f, speed=%i", this->getType(), this->getPositionX(), this->getDefaultSpeed());
}

int PhysicsCar::setSpeed(int minSpeed, int deltaSpeed)
{
	defaultSpeed = minSpeed + deltaSpeed * CCRANDOM_0_1();
	return defaultSpeed;
}

PhysicsCar* PhysicsCar::create()
{
	PhysicsCar* tmp = new PhysicsCar();
	if (tmp->init())
	{
		tmp->autorelease();
		return tmp;
	}
	CC_SAFE_DELETE(tmp);
	return NULL;
}

void PhysicsCar::modifySpeed(int sp)
{
	speed = sp;
	return;
}

int PhysicsCar::getSpeed()
{
	return speed;
}

int PhysicsCar::getType()
{
	return this->type;
}

int PhysicsCar::getDefaultSpeed()
{
	return defaultSpeed;
}

void PhysicsCar::decreaseSpeed(int carSpeed)
{
	if (this->getSpeed() > 40)
		this->modifySpeed(this->getSpeed() - 5);
	this->setPosition(Vec2(this->getPositionX(), this->getPositionY() - 0.1 * (carSpeed - this->getSpeed())));
}

void PhysicsCar::increaseSpeed(int carSpeed)
{
	if (this->getSpeed() < this->getDefaultSpeed())
		this->modifySpeed(this->getSpeed() + 5);
	this->setPosition(Vec2(this->getPositionX(), this->getPositionY() - 0.1 * (carSpeed - this->getSpeed())));
}

void PhysicsCar::moveToLeftLine(int carSpeed)
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

void PhysicsCar::moveToRightLine(int carSpeed)
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

void PhysicsCar::setMoveOption(bool f, bool l, bool r)
{
	moveOption = new PhysicsMoveOption(f, l, r);
}
