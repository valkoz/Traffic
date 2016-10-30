#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#define MIN_SPEED 20
#define DELTA_SPEED 160
#define LEFT_CAR_POSITION 120
#define ROAD_LINE_WIDTH 160
#define RESOLUTION_Y 1280
#define MAX_SPEED 250

enum CarType { Ambulance, Black_viper, Orange_car, Mini_truck, Mini_van, Police, Taxi, Truck };

enum moveOption { brakes = -1, freeMovement, gas };

class MoveOption {
private:
	bool isFront;
	bool isLeft;
	bool isRight;
public:
	MoveOption(bool f, bool l, bool r) : isFront(f), isLeft(l), isRight(r) {};
	void setIsFront(bool f) { isFront = f; };
	void setIsLeft(bool l) { isLeft = l; };
	void setIsRight(bool r) { isRight = r; };
	bool getIsFront() { return isFront; };
	bool getIsLeft() { return isLeft; };
	bool getIsRight() { return isRight; };

};


#endif // __DEFINITIONS_H__
