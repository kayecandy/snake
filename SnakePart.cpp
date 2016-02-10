#include "SnakePart.h"

USING_NS_CC;

SnakePart* SnakePart::create(PolygonInfo &polygon){
	SnakePart* s = new (std::nothrow) SnakePart();

	if (s && s->initWithPolygon(polygon))
	{
		s->autorelease();
		return s;
	}
	CC_SAFE_DELETE(s);
	return nullptr;
}

bool SnakePart::init(){
	if (!Sprite::init()){
		return false;
	}

	return true;

}


void SnakePart::warp(){
	if (this->getPositionX() < SCREEN_POSITION_LEFT){
		this->setPositionX(SCREEN_POSITION_RIGHT);
	}
	else if (this->getPositionX() > SCREEN_POSITION_RIGHT){
		this->setPositionX(SCREEN_POSITION_LEFT);
	}

	if (this->getPositionY() < SCREEN_POSITION_BOTTOM){
		this->setPositionY(SCREEN_POSITION_TOP);
	}
	else if (this->getPositionY() > SCREEN_POSITION_TOP){
		this->setPositionY(SCREEN_POSITION_BOTTOM);
	}
}