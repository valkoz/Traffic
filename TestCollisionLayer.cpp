#include "TestCollisionLayer.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include <vector>
//#include <iostream>

USING_NS_CC;





Scene* TestCollision::createScene()
{
	auto scene = Scene::create();
	auto layer = TestCollision::create();
	scene->addChild(layer);
	return scene;
}

bool TestCollision::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(TestCollision::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TestCollision::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(TestCollision::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


	this->scheduleUpdate();

	return true;
}



bool TestCollision::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
	Point touchPoint(touch->getLocation().x, touch->getLocation().y);

	return true;
}

void TestCollision::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
	return;
}

void TestCollision::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
}