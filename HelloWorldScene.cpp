#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
//#include <iostream>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);


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

	user_car = Sprite::create("cars/Mycar.png");
	user_car->setPosition(Vec2(visibleSize.width - LEFT_CAR_POSITION, 150));
/*FOR TESTING*/
//	user_car->setPosition(Vec2(500, 150));
	user_car->setName("user");
	this->addChild(user_car,1);

	this->schedule(schedule_selector(HelloWorld::generateNewCar), 1.0f);

	this->schedule(schedule_selector(HelloWorld::logSpeedLastLine), 2.0f);

//	this->schedule(schedule_selector(HelloWorld::checkCarsNear), 0.1f);

	this->scheduleUpdate();
	//user_car->runAction(seq);

    // add the sprite as a child to this layer
   // this->addChild(sprite, 0);
    
    return true;
}

void HelloWorld::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
	accInfo = acc->x;
	CCLOG("%f", acc->x);
}

/*
onTouchBegan works only one time but must work permanent for acceleration wtf?!
can be used without shedulers but how?
!!!!!!!!!!!!!!!!!!!!!!!!FIXED!!!!!!!!!!!!!!!!!!!!!!!!!!!

Black strips on background

*/
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
	Point touchPoint(touch->getLocation().x, touch->getLocation().y);
	Rect gasRect(0, 0, 200, 200);
	Rect stopRect(600, 0, 200, 200);
	if (gasRect.containsPoint(touchPoint)) {
//		CCLOG("GOOOOO");
		onTouch = gas;
	}
	if (stopRect.containsPoint(touchPoint))
		onTouch = brakes;
//	this->schedule(schedule_selector(HelloWorld::increaseSpeed), 0.1f);
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
	onTouch = freeMovement;
//	this->schedule(schedule_selector(HelloWorld::decreaseSpeed), 0.1f);
	return;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
}

void HelloWorld::increaseSpeed(float dt) {
	carSpeed += 1.1f;
}

void HelloWorld::decreaseSpeed(float dt) {
	carSpeed -= 1.1f;
}

void HelloWorld::update(float dt) {
	/*Œœ–≈ƒ≈Àﬂ≈“ œŒ¬≈ƒ≈Õ»≈ ¿¬“Œ 1 - √¿«, -1 - “Œ–ÃŒ«, 0 - —¬Œ¡ŒƒÕŒ≈ ƒ¬»∆≈Õ»≈*/
	if ((onTouch == gas) && (carSpeed < 200))
		carSpeed += 1;
	/*else*/ if ((onTouch == brakes) && (carSpeed > MIN_SPEED))
		carSpeed -= 3;
	/*else*/ if ((onTouch == freeMovement) && (carSpeed > MIN_SPEED))
		carSpeed -= 1;
	/*œ–Œ–»—Œ¬ ¿ ‘ŒÕ¿*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	road->setPosition(Vec2(visibleSize.width / 2 + origin.x, road->getPositionY() - 0.1 * carSpeed));
	road_upper_part->setPosition(Vec2(visibleSize.width / 2 + origin.x, road_upper_part->getPositionY() - 0.1 * carSpeed));
	if (road->getPositionY() < -visibleSize.height / 2 - origin.y)
		road->setPosition(Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 2 + origin.y));
	if (road_upper_part->getPositionY() < -visibleSize.height / 2 - origin.y)
		road_upper_part->setPosition(Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 2 + origin.y));

	/*user_car with accelerometer*/
	if ((user_car->getPositionX()  + (user_car->getBoundingBox().getMaxX() - user_car->getBoundingBox().getMinX())/2 > 720) || (user_car->getPositionX() - (user_car->getBoundingBox().getMaxX() - user_car->getBoundingBox().getMinX()) / 2 < 0)) { CCLOG("vibration"); }
	else
		user_car->setPosition(Vec2(user_car->getPositionX() + 20 * accInfo, user_car->getPositionY()));


	/*œ–Œ–»—Œ¬ ¿ Ã¿ÿ»Õ*/ /*+ »Õ“≈ÀÀ≈ “ Ã¿ÿ»Õ (¬Œ«ÃŒ∆ÕŒ—“‹ Œ¡Œ√Õ¿“‹)*/

	/*if there are no cars in front of -> just move current, else make overtake (by moveng left and up) */
	Vector<Node*> allNodes = this->getChildren();
	for (auto& node : allNodes) {
		if (dynamic_cast<Car*>(node)) {
			Car *currentCar = dynamic_cast<Car*>(node);
			removeCarFromLayer(currentCar);

			//	if ((int(currentCar->getPositionY()) % ROAD_LINE_WIDTH) == LEFT_CAR_POSITION)
			checkCarsNearWithUpdate(currentCar);

			/*Collision Detection-> GAME OVER*/
			checkCollisions(currentCar);
			

			/*ƒÎˇ Ó·„ÓÌ‡ Ë ‚ÎÂ‚Ó Ë ‚Ô‡‚Ó (“‡Í Ë ÌÂ Á‡‡·ÓÚ‡ÎÓ)*/
	/*			if (currentCar->getIsFront()) {  //isNearOvertakenCar(currentCar) // opt.getIsFront()
					if (!currentCar->getIsLeft()) //!isLeftCar(currentCar) //!opt.getIsLeft()
						currentCar->moveToLeftLine(carSpeed);
					else if (!currentCar->getIsRight()) { //!opt.getIsRight()
						currentCar->moveToRightLine(carSpeed);
					}
					else { currentCar->decreaseSpeed(carSpeed); }
				}
				else { currentCar->increaseSpeed(carSpeed); }
	*/

	/*ƒÎˇ Ó·„ÓÌ‡ ‚ÎÂ‚Ó */
		/*	if (!currentCar->getActionByTag(1)) {
			if (currentCar->getIsFront())
			{
				if (currentCar->getIsLeft())
					currentCar->decreaseSpeed(carSpeed);
				else
					currentCar->moveToLeftLine(carSpeed);
			}
			else { currentCar->increaseSpeed(carSpeed); }
		}
		*/
			/*ƒÎˇ Ó·„ÓÌ‡ ‚ÂÁ‰Â Ì‡ıÛÈ  */
			if (!currentCar->getActionByTag(1)) {
				if (currentCar->getIsFront())
				{
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
				else { currentCar->increaseSpeed(carSpeed); }
			}



		}
	}	
}


void HelloWorld::generateNewCar(float dt) {
	auto nCar = Car::create();
//	Coordinate a;
//	a.x = nCar->getPositionX();
//	a.y = nCar->getPositionY();
//	carPositions.push_back(a);
	this->addChild(nCar,100);
//	CCLOG("Current Speed: %i", carSpeed);
}

void HelloWorld::removeCarFromLayer(Car * current)
{
	if (current->getPositionY() < -200)
		this->removeChild(current, true);
	if (current->getPositionY() > 3000)
		this->removeChild(current, true);
}

bool HelloWorld::isNearOvertakenCar(Car *current)
{
	Vector <Node*> fuckingFronts = this->getChildren();
	for (auto& car : fuckingFronts) {
		if (dynamic_cast<Car*>(car)) {
			Car *currentCar = dynamic_cast<Car*>(car);
			if(current->getPosition() != currentCar->getPosition())
			if ((abs(current->getPositionX() - currentCar->getPositionX())< 150) && (abs(currentCar->getPositionY() - current->getPositionY()) < 400) && (currentCar->getPositionY() - current->getPositionY() > 0)) {
				CCLOG("overtake!!!");
				return true;
			}

		}
	}
	return false;
}

bool HelloWorld::isLeftCar(Car *current)
{
	Vector <Node*> fuckingFronts = this->getChildren();
	for (auto& car : fuckingFronts) {
		if (dynamic_cast<Car*>(car)) {
			Car *currentCar = dynamic_cast<Car*>(car);
			if (current->getPosition() != currentCar->getPosition())
				if (((currentCar->getPositionX() - current->getPositionX()) > 150) && ((currentCar->getPositionX() - current->getPositionX()) < 300) && (abs(currentCar->getPositionY() - current->getPositionY()) < 300)) {
					CCLOG("overtake!!!");
					return true;
				}

		}
	}
	return false;
}

void HelloWorld::checkCarsNear(float dt)
{
/*	Vector<Node*> allNodes = this->getChildren();
	for (auto& node : allNodes) {
		if (dynamic_cast<Car*>(node)) {
			Car *current = dynamic_cast<Car*>(node);
			MoveOption opt = MoveOption(false, false, false);
			Vector <Node*> fuckingFronts = this->getChildren();
			for (auto& car : fuckingFronts) {
				if (dynamic_cast<Car*>(car)) {
					Car *nearbyCar = dynamic_cast<Car*>(car);
					if (current->getPosition() != nearbyCar->getPosition()) {
						if ((abs(current->getPositionX() - nearbyCar->getPositionX()) < ROAD_LINE_WIDTH) && (nearbyCar->getPositionY() - current->getPositionY() < 400) && (nearbyCar->getPositionY() - current->getPositionY() > 0)) {
							//			CCLOG("Car in front of !!!");
							if (nearbyCar->getSpeed() < current->getSpeed())
								opt.setIsFront(true);
						}
						if ((nearbyCar->getPositionX() - current->getPositionX() ==  ROAD_LINE_WIDTH) && (abs(nearbyCar->getPositionY() - current->getPositionY()) < 300)) {
							//		CCLOG("Car left");
							opt.setIsLeft(true);
						}
						if ((current->getPositionX() - nearbyCar->getPositionX() == ROAD_LINE_WIDTH) && (abs(nearbyCar->getPositionY() - current->getPositionY()) < 300)) {
							//		CCLOG("Car right!!!");
							opt.setIsRight(true);
						}
					}
				}
				current->setMoveOption(opt.getIsFront(), opt.getIsLeft(), opt.getIsRight());
			}
		}
	}*/
}

void HelloWorld::checkCarsNearWithUpdate(Car *current)
{
	MoveOption opt = MoveOption(false, false, false);
	Vector <Node*> fuckingFronts = this->getChildren();
	for (auto& car : fuckingFronts) {
		if (dynamic_cast<Car*>(car)) {
			Car *nearbyCar = dynamic_cast<Car*>(car);
			if (current->getPosition() != nearbyCar->getPosition()) {
				if ((current->getPositionX() == nearbyCar->getPositionX()) && (nearbyCar->getPositionY() - current->getPositionY() < 400) && (nearbyCar->getPositionY() - current->getPositionY() > 0)) {
					//			CCLOG("Car in front of !!!");
					if (nearbyCar->getSpeed() <= current->getSpeed())
						opt.setIsFront(true);
				}
				if ((current->getPositionX() - nearbyCar->getPositionX() <= ROAD_LINE_WIDTH) && (current->getPositionX() - nearbyCar->getPositionX() > 0) && (abs(nearbyCar->getPositionY() - current->getPositionY()) < 600)) {
					//		CCLOG("Car left");
					opt.setIsLeft(true);
				}
				if ((nearbyCar->getPositionX() - current->getPositionX() <= ROAD_LINE_WIDTH) && (nearbyCar->getPositionX() - current->getPositionX() > 0 ) && (abs(nearbyCar->getPositionY() - current->getPositionY()) < 600)) {
					//		CCLOG("Car right!!!");
					opt.setIsRight(true);
				}
			}
		}
		current->setMoveOption(opt.getIsFront(), opt.getIsLeft(), opt.getIsRight());
	}
}

void HelloWorld::checkCollisions(Car * currentCar)
{
	Rect a = user_car->getBoundingBox();
	float minX = a.getMinX() + 5;
	float maxX = a.getMaxX() - 5;
	float minY = a.getMinY();
	float maxY = a.getMaxY();
	Rect *newRectangle = new Rect(minX, minY, maxX - minX, maxY - minY - 5);


	if (currentCar->getBoundingBox().intersectsRect(*newRectangle)) {
		auto scene = HelloWorld::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
	}
}

void HelloWorld::logSpeedLastLine(float dt)
{
	Vector <Node*> fuckingFronts = this->getChildren();
	for (auto& car : fuckingFronts) {
		if (dynamic_cast<Car*>(car)) {
			Car *nearbyCar = dynamic_cast<Car*>(car);
			if (nearbyCar->getPositionX() > 500) {
				CCLOG("Current Speed: %i", nearbyCar->getSpeed());
			}
		}
	}
	CCLOG("_____________________________________");
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
 //   Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
 //   exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

