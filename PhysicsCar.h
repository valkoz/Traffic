#ifndef __PHYSICS_CAR_H__
#define __PHYSICS_CAR_H__

#include "cocos2d.h"
#include "Definitions.h"
USING_NS_CC;

//enum PhisicsCarType {Ambulance, Black_viper, Orange_car, Mini_truck, Mini_van, Police, Taxi, Truck};

class PhysicsMoveOption {
private:
	bool isFront;
	bool isLeft;
	bool isRight;
public:
	PhysicsMoveOption(bool f, bool l, bool r) : isFront(f), isLeft(l), isRight(r) {};
	void setIsFront(bool f) { isFront = f; };
	void setIsLeft(bool l) { isLeft = l; };
	void setIsRight(bool r) { isRight = r; };
	bool getIsFront() { return isFront; };
	bool getIsLeft() { return isLeft; };
	bool getIsRight() { return isRight; };

};

class PhysicsCar : public cocos2d::Sprite
{
private:

	PhysicsMoveOption *moveOption = nullptr;

	int speed;

	int defaultSpeed;

	int currentLine;

	CarType type;

	PhysicsCar();

	virtual bool init() { return true; };

	int setSpeed(int minSpeed, int deltaSpeed);

	void define(CarType type);

public:

	static PhysicsCar* create();

	void modifySpeed(int sp);

	int getSpeed();

	int getType();

	int getDefaultSpeed();

	int getCurrentLine() { return currentLine; };

	void decreaseSpeed(int carSpeed);

	void increaseSpeed(int carSpeed);

	void moveToLeftLine(int carSpeed);

	void moveToRightLine(int carSpeed);


	void setMoveOption(bool f, bool l, bool r);

	bool getIsFront() { if (this->moveOption) return moveOption->getIsFront(); return false; };
	bool getIsLeft() { if (this->moveOption) return moveOption->getIsLeft(); return false; };
	bool getIsRight() { if (this->moveOption) return moveOption->getIsRight(); return false; };

	virtual ~PhysicsCar() {};

};

#endif // __PHYSICS_CAR_H__
