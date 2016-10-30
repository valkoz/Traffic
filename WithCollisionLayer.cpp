#include "WithCollisionLayer.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include <vector>
#include <array>
//#include <iostream>

USING_NS_CC;

Scene* WithCollision::createScene()
{
    auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = WithCollision::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

bool WithCollision::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(WithCollision::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(WithCollision::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WithCollision::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WithCollision::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

//	this->scheduleUpdate();

/*    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));*/
	road = Sprite::create("road1350.jpg"/*, Rect(0, 0, 300, 300)*/);
	road->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(road);

	road_upper_part = Sprite::create("road1350.jpg");
	road_upper_part->setPosition(Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 2 + origin.y));
	this->addChild(road_upper_part);

	//*new* 
	/*
	*GAS AND BREKES Button DEFINITION
	*/
	gasButton = Sprite::create("gas_wait.png");
	gasButton->setPosition(650, 80);
	this->addChild(gasButton, 1000);

	brakesButton = Sprite::create("brakes_wait.png");
	brakesButton->setPosition(100, 80);
	this->addChild(brakesButton, 1001);

	gasButton->setScale(0.5);
	brakesButton->setScale(0.5);
	gasButton->setOpacity(150);
	brakesButton->setOpacity(150);


	/**/

	user_car = Sprite::create("cars/Mycar.png");
	user_car->setPosition(Vec2(visibleSize.width - 2.3 * LEFT_CAR_POSITION, 150));
	float userHeight = user_car->getBoundingBox().size.height;
	float userWidth = user_car->getBoundingBox().size.width;
	std::array<Point, 12> coord = { Point(-3 * userWidth / 10 ,-userHeight / 2), Point(3 * userWidth / 10, -userHeight / 2),
		Point(46 * userWidth / 100, -85 * userHeight / 200), Point(48 * userWidth / 100, -60 * userHeight / 200),
		Point(35 * userWidth / 100, -50 * userHeight / 200), Point(48 * userWidth / 100,70 * userHeight / 200),
		Point(2 * userWidth / 10, userHeight / 2), Point(-2 * userWidth / 10 , userHeight / 2),
		Point(-48 * userWidth / 100, 70 * userHeight / 200), Point(-35 * userWidth / 100,-50 * userHeight / 200),
		Point(-48 * userWidth / 100,-60 * userHeight / 200), Point(-46 * userWidth / 100, -85 * userHeight / 200) };
	auto body = PhysicsBody::createEdgePolygon(coord.data(), 12);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(true);
	user_car->setPhysicsBody(body);
	user_car->setName("user");
	this->addChild(user_car, 1);






	this->schedule(schedule_selector(WithCollision::generateNewCar), 0.5f);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(WithCollision::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


	this->scheduleUpdate();
	
for (int i = 0; i < 50; i++)
{    
	accInfo.push_back(0);
}

    return true;
}

void WithCollision::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
	accInfo.push_back(acc->x);
	if (accInfo.size() > 50)
		accInfo.erase(accInfo.begin() + 1);
	CCLOG("%f", acc->x);
}


bool WithCollision::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
	Point touchPoint(touch->getLocation().x, touch->getLocation().y);
	//Rect gasRect(0, 0, 200, 200);
	//Rect stopRect(600, 0, 200, 200);

	if (gasButton->getBoundingBox().containsPoint(touchPoint)) { //gasRect
		onTouch = gas;
		gasButton->setTexture("gas_enabled.png");
	}
	if (brakesButton->getBoundingBox().containsPoint(touchPoint)) { //stopRect
		onTouch = brakes;
		brakesButton->setTexture("brakes_enabled.png");

	}
	return true;
}

void WithCollision::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
	onTouch = freeMovement;
	gasButton->setTexture("gas_wait.png");
	brakesButton->setTexture("brakes_wait.png");
	return;
}

void WithCollision::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
}

bool WithCollision::onContactBegin(cocos2d::PhysicsContact & contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	CCLOG("%i,%i", a->getCollisionBitmask(), b->getCollisionBitmask());
	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		auto scene = WithCollision::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
		CCLOG("Collided");
	}
	return false;
}

/*Game loop*/
void WithCollision::update(float dt) {
	this->changeSpeed();
	this->renderBackground();
	

	/*user_car with accelerometer*/
	bool rightCarBoundary = user_car->getBoundingBox().getMaxX() > 720;
	bool leftCarBoundary = user_car->getBoundingBox().getMinX() < 0;
	if((!leftCarBoundary)&&(!rightCarBoundary)) {
		double res = this->returnAccRatio();
		user_car->setRotation(2 * res);
		user_car->setPosition(Vec2(user_car->getPositionX() + res, user_car->getPositionY()));
	}
	else{
		Device::vibrate(0.1f);
		if (leftCarBoundary)
			user_car->setPositionX(user_car->getBoundingBox().getMidX() + 1);
		if (rightCarBoundary)
			user_car->setPositionX(user_car->getBoundingBox().getMidX() - 1);
	}


	/*œ–Œ–»—Œ¬ ¿ Ã¿ÿ»Õ*/ /*+ »Õ“≈ÀÀ≈ “ Ã¿ÿ»Õ (¬Œ«ÃŒ∆ÕŒ—“‹ Œ¡Œ√Õ¿“‹)*/
	Vector<Node*> allNodes = this->getChildren();
	for (auto& node : allNodes) {
		if (dynamic_cast<PhysicsCar*>(node)) {
			PhysicsCar *currentCar = dynamic_cast<PhysicsCar*>(node);
			this->removeCarFromLayer(currentCar);
			this->checkCarsNearWithUpdate(currentCar);
			//this->checkCollisionsWithPlayer(currentCar);
			this->overtake(currentCar);
		}
	}	
}

/*Renderring the Background*/
void WithCollision::renderBackground()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	road->setPosition(Vec2(visibleSize.width / 2 + origin.x, road->getPositionY() - 0.1 * carSpeed));
	road_upper_part->setPosition(Vec2(visibleSize.width / 2 + origin.x, road_upper_part->getPositionY() - 0.1 * carSpeed));
	if (road->getPositionY() < -visibleSize.height / 2 - origin.y)
		road->setPosition(Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 2 + origin.y));
	if (road_upper_part->getPositionY() < -visibleSize.height / 2 - origin.y)
		road_upper_part->setPosition(Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 2 + origin.y));
}

/* Generate new Car and set it on layer*/
void WithCollision::generateNewCar(float dt) {
	if (this->getChildrenCount() < 10) {
		auto nCar = PhysicsCar::create();
		this->addChild(nCar, 100);
		CCLOG("ADD NEW CAR");
	}
	else {
		CCLOG("TOO MUCH CARS");
	}
}

/*Removes Car *current from layer */
void WithCollision::removeCarFromLayer(PhysicsCar * current)
{
	if (current->getPositionY() < -200)
		this->removeChild(current, true);
	if (current->getPositionY() > 3000)
		this->removeChild(current, true);
}


/*Checks nerby cars and set moveOption variable for Car *current*/
void WithCollision::checkCarsNearWithUpdate(PhysicsCar *current)
{
	MoveOption opt = MoveOption(false, false, false);
	Vector <Node*> fuckingFronts = this->getChildren();
	for (auto& car : fuckingFronts) {
		if (dynamic_cast<PhysicsCar*>(car)) {
			PhysicsCar *nearbyCar = dynamic_cast<PhysicsCar*>(car);
			/* Œ—“€À‹ - Â¯ÂÌËÂ ÔÓ·ÎÂÏ Ò Ì‡ÍÎ‡‰ÍÓÈ Ï‡¯ËÌ*/
			if ((nearbyCar->getBoundingBox().intersectsRect(current->getBoundingBox())&&(nearbyCar != current)&&(nearbyCar->getPositionX() == current->getPositionX()))) {
				this->removeChild(nearbyCar, true);
			}
			else {
				if (current->getPosition() != nearbyCar->getPosition()) {
					if ((current->getPositionX() == nearbyCar->getPositionX()) && (nearbyCar->getPositionY() - current->getPositionY() < 400) && (nearbyCar->getPositionY() - current->getPositionY() > 0)) {
						if (nearbyCar->getSpeed() <= current->getSpeed())
							opt.setIsFront(true);
					}
					if ((current->getPositionX() - nearbyCar->getPositionX() <= ROAD_LINE_WIDTH) && (current->getPositionX() - nearbyCar->getPositionX() > 0) && (abs(nearbyCar->getPositionY() - current->getPositionY()) < 600)) {
						opt.setIsLeft(true);
					}
					if ((nearbyCar->getPositionX() - current->getPositionX() <= ROAD_LINE_WIDTH) && (nearbyCar->getPositionX() - current->getPositionX() > 0) && (abs(nearbyCar->getPositionY() - current->getPositionY()) < 600)) {
						opt.setIsRight(true);
					}
				}
			}
		}
		current->setMoveOption(opt.getIsFront(), opt.getIsLeft(), opt.getIsRight());
	}
}

/*Collision Detection-> GAME OVER*/
void WithCollision::checkCollisionsWithPlayer(PhysicsCar * currentCar)
{
	Rect a = user_car->getBoundingBox();
	float minX = a.getMinX() + 15;
	float maxX = a.getMaxX() - 15;
	float minY = a.getMinY();
	float maxY = a.getMaxY();
	Rect *newRectangle = new Rect(minX, minY, maxX - minX, maxY - minY - 5);


	if (currentCar->getBoundingBox().intersectsRect(*newRectangle)) {
		auto scene = WithCollision::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
	}
}

/*Checks if overtake is nessesry and making an overtake*/
void WithCollision::overtake(PhysicsCar * currentCar)
{
	bool noUserNear = this->checkDistanceBetweenPlayerAndCar(currentCar);

		if (!currentCar->getActionByTag(1)) {
			if (currentCar->getIsFront())
			{
				if (noUserNear){
				if (currentCar->getIsLeft()) {
					if (currentCar->getIsRight())
						currentCar->decreaseSpeed(carSpeed);
					else {
						if (currentCar->getPositionX() != LEFT_CAR_POSITION + 3 * ROAD_LINE_WIDTH)
							currentCar->moveToRightLine(carSpeed);
						else
							currentCar->decreaseSpeed(carSpeed);
					}
				}
				else {
					if (currentCar->getPositionX() != LEFT_CAR_POSITION)
						currentCar->moveToLeftLine(carSpeed);
					else if (currentCar->getIsRight())
						currentCar->decreaseSpeed(carSpeed);
					else
						currentCar->moveToRightLine(carSpeed);
				}
			}
				else { currentCar->decreaseSpeed(carSpeed); }
			}
			else { currentCar->increaseSpeed(carSpeed); }
		}
}

bool WithCollision::checkDistanceBetweenPlayerAndCar(PhysicsCar * currentCar)
{
	if ((abs(user_car->getPositionX() - currentCar->getPositionX()) < 3 * ROAD_LINE_WIDTH / 2)&&(abs(user_car->getPositionY() - currentCar->getPositionY()) < 400))
		return false;
	else
		return true;
}

/*Returns value of accelerometer coefficient*/
double WithCollision::returnAccRatio()
{
	double res = 0;
	for (auto i : accInfo) 
		res = res + 0.3 * (i+1) * accInfo[49 - i];
	return res;
}

/*Making player's car to move faster or slower */
void WithCollision::changeSpeed()
{
	if ((onTouch == gas) && (carSpeed < MAX_SPEED))
		carSpeed += 1;
	if ((onTouch == brakes) && (carSpeed > MIN_SPEED))
		carSpeed -= 3;
	if ((onTouch == freeMovement) && (carSpeed > MIN_SPEED))
		carSpeed -= 1;
}