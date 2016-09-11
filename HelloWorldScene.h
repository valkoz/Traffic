#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Car.h"

enum moveOption { brakes = -1, freeMovement, gas };

class HelloWorld : public cocos2d::Layer
{
private:
	cocos2d::Sprite *road;
	cocos2d::Sprite *road_upper_part;
	cocos2d::Sprite *user_car;
//	Car* nCar;

	moveOption onTouch = freeMovement;
	int carSpeed = MIN_SPEED;
	void update(float dt);

	void increaseSpeed(float dt);
	void decreaseSpeed(float dt);

	void generateNewCar(float dt);

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *event);

	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event *event);


    
    // implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
