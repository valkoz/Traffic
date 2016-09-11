#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("coc", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

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

	user_car = Sprite::create("cars/taxi.png");
	user_car->setPosition(Vec2(visibleSize.width - 120,150));
	user_car->setName("user");
	//user_car->setRotation(-90);
	this->addChild(user_car,1);

	this->schedule(schedule_selector(HelloWorld::generateNewCar), 1.0f);

	this->scheduleUpdate();
	//user_car->runAction(seq);

    // add the sprite as a child to this layer
   // this->addChild(sprite, 0);
    
    return true;
}

void HelloWorld::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
	auto user_car = Sprite::create("car_red.png");
	user_car->setPosition(0,0);
	this->addChild(user_car, 1);
	CCLOG("%f", acc->z);
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
	Rect stopRect(800, 0, 200, 200);
	if (gasRect.containsPoint(touchPoint)) {
		CCLOG("GOOOOO");
		onTouch = 1;
	}
	if (stopRect.containsPoint(touchPoint))
		onTouch = -1;
//	this->schedule(schedule_selector(HelloWorld::increaseSpeed), 0.1f);
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
	onTouch = 0;
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
	/*нопедекъер онбедемхе юбрн 1 - цюг, -1 - рнплнг, 0 - ябнандмне дбхфемхе*/
	if ((onTouch == 1) && (carSpeed < 200))
		carSpeed += 1;
	else if ((onTouch == -1) && (carSpeed > 20))
		carSpeed -= 3;
	else if ((onTouch == 00000) && (carSpeed > 20))
		carSpeed -= 1;
	/*опнпхянбйю тнмю*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	road->setPosition(Vec2(visibleSize.width / 2 + origin.x, road->getPositionY() - 0.1 * carSpeed));
	road_upper_part->setPosition(Vec2(visibleSize.width / 2 + origin.x, road_upper_part->getPositionY() - 0.1 * carSpeed));
	if (road->getPositionY() < -visibleSize.height / 2 - origin.y)
		road->setPosition(Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 2 + origin.y));
	if (road_upper_part->getPositionY() < -visibleSize.height / 2 - origin.y)
		road_upper_part->setPosition(Vec2(visibleSize.width / 2 + origin.x, 3 * visibleSize.height / 2 + origin.y));

	/*опнпхянбйю люьхм*/
	Vector<Node*> allNodes = this->getChildren();
	for (auto& node : allNodes) {
		if (dynamic_cast<Car*>(node)) {
			Car *target = dynamic_cast<Car*>(node);
			target->setPosition(Vec2(target->getPositionX() , target->getPositionY() - 0.1 * (carSpeed - target->getSpeed())));
		}
	}
}

void HelloWorld::generateNewCar(float dt) {
	auto nCar = Car::create();
	this->addChild(nCar,100);
	CCLOG("Current Speed: %i", carSpeed);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
