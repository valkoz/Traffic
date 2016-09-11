#ifndef __CAR_H__
#define __CAR_H__

#include "cocos2d.h"
USING_NS_CC;

class Car : public cocos2d::Sprite
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int speed;

	Car();
	virtual bool init() { return true; };

	Point definePosition();

	int defineSpeed();
//	void increaseSpeed(float dt);

//	void decreaseSpeed(float dt);

//	void generateNewCar(float dt);

public:
	static Car* create();

	void modifySpeed(int sp);

	int getSpeed();

	virtual ~Car() {};

};

#endif // __CAR_H__
