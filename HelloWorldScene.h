#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Car.h"
#include <vector>

enum moveOption { brakes = -1, freeMovement, gas };

class HelloWorld : public cocos2d::Layer
{
private:
	cocos2d::Sprite *road;
	cocos2d::Sprite *road_upper_part;
	cocos2d::Sprite *user_car;

	std::vector <double> accInfo;

	moveOption onTouch = freeMovement;

	int carSpeed = MIN_SPEED;

	void update(float dt);

	void renderBackground();

	void generateNewCar(float dt);

	void removeCarFromLayer(Car *current);

	void checkCarsNearWithUpdate(Car *current);

	void checkCollisionsWithPlayer(Car *currentCar);

	void overtake(Car *currentCar);

	double returnAccRatio();

	void changeSpeed();

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *event);

	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event *event);


    
    // implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
