#ifndef __WITH_COLLISION_SCENE_H__
#define __WITH_COLLISION_SCENE_H__

#include "cocos2d.h"
#include "PhysicsCar.h"
#include <vector>

//enum PhysicsmoveOption { brakes = -1, freeMovement, gas };

class WithCollision : public cocos2d::Layer
{
private:
	cocos2d::Sprite *road;
	cocos2d::Sprite *road_upper_part;
	cocos2d::Sprite *user_car;
	cocos2d::Sprite *gasButton;
	cocos2d::Sprite *brakesButton;

	cocos2d::PhysicsWorld *sceneWorld;
	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };

	std::vector <double> accInfo;

	moveOption onTouch = freeMovement;

	int carSpeed = MIN_SPEED;

	int getSpeed() { return carSpeed; }

	void update(float dt);

	void renderBackground();

	void generateNewCar(float dt);

	void removeCarFromLayer(PhysicsCar *current);

	void checkCarsNearWithUpdate(PhysicsCar *current);

	void checkCollisionsWithPlayer(PhysicsCar *currentCar);

	void overtake(PhysicsCar *currentCar);

	bool checkDistanceBetweenPlayerAndCar(PhysicsCar *currentCar);

	double returnAccRatio();

	void changeSpeed();

	void setCarSpeed(int speed) { carSpeed = speed; };
	
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *event);

	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event *event);

	bool onContactBegin(cocos2d::PhysicsContact &contact);

    
    // implement the "static create()" method manually
	CREATE_FUNC(WithCollision);
};

#endif // __WITH_COLLISION_SCENE_H__
