#include "Food.h"

USING_NS_CC;

Food* Food::create(){
	Food* f = new (std::nothrow)Food();

	if (f&& f->init()){
		f->autorelease();
	}
	else{
		CC_SAFE_DELETE(f);
	}

	return f;

}

bool Food::init(){
	if (!Node::init()){
		return false;
	}

	initializeSprites();
	rotateGlow();

	return true;
}

void Food::initializeSprites(){
	glow = Sprite::create(Globals::foodSprite[Globals::INDEX_FOOD_GLOW]);
	this->addChild(glow, 0);

	sprite = Sprite::create(Globals::foodSprite[Globals::INDEX_FOOD]);
	this->addChild(sprite, 1);

	this->setContentSize(sprite->getContentSize());
	reposition();
}


void Food::rotateGlow(){
	auto rotate = RotateBy::create(GLOW_ROTATE_SPEED / DIVIDER, 360);
	auto end = CallFunc::create(this, CC_CALLFUNC_SELECTOR(Food::rotateGlowLoop));

	glow->runAction(Sequence::create(rotate, end, NULL));
}

void Food::rotateGlowLoop(){
	rotateGlow();
}

void Food::reposition(){
	auto size = this->getContentSize();

	this->setPosition(Vec2(
		random(SCREEN_POSITION_LEFT + size.width, SCREEN_POSITION_RIGHT - size.width),
		random(SCREEN_POSITION_BOTTOM + size.height, SCREEN_POSITION_TOP - size.height)));
}

Sprite* Food::getFoodSprite(){
	return sprite;
}