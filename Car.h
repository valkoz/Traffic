#ifndef __CAR_H__
#define __CAR_H__

#include "cocos2d.h"
#include "Definitions.h"
USING_NS_CC;

enum CarType {Ambulance, Black_viper, Orange_car, Mini_truck, Mini_van, Police, Taxi, Truck};

class Car : public cocos2d::Sprite
{
private:

	int speed;

	CarType type;

	Car();

	virtual bool init() { return true; };

	Point definePosition();

	int defineSpeed(int minSpeed, int deltaSpeed);

public:
	static Car* create();

	void modifySpeed(int sp);

	int getSpeed();

	virtual ~Car() {};

};

#endif // __CAR_H__
