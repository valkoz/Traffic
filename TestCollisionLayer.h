#ifndef __TESTCOLLISION_LAYER_H__
#define __TESTCOLLISION_LAYER_H__

#include "cocos2d.h"
#include "Car.h"
#include <vector>

class TestCollision : public cocos2d::Layer
{
private:
	cocos2d::Sprite *user_car;
	void update(float dt);
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *event);

	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event *event);



	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __TESTCOLLISION_LAYER_H__
