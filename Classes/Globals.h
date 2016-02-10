#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define SCREEN_WIDTH Globals::getVisibleSize().width
#define SCREEN_HEIGHT Globals::getVisibleSize().height

#define SCREEN_POSITION_LEFT 0
#define SCREEN_POSITION_RIGHT Globals::getVisibleSize().width
#define SCREEN_POSITION_TOP Globals::getVisibleSize().height
#define SCREEN_POSITION_BOTTOM 0

#define POSITION_CENTER_CENTER Globals::getPositionCenterCenter()
#define POSITION_CENTER_LEFT(item) Globals::getPositionCenterLeft(item)

#include "cocos2d.h"

USING_NS_CC;


class Globals{

public:

	enum indexSnakeSprite{
		INDEX_SNAKE_HEAD = 0,
		INDEX_SNAKE_PART = 1
	};

	enum indexFoodSprite{
		INDEX_FOOD_GLOW = 0,
		INDEX_FOOD = 1
	};

	static char* backgroundImageSource;
	static char* playButtonSource[3];

	static char* snakeSprite[2];
	static char* foodSprite[2];


	static Size getVisibleSize();
	static Vec2 getOrigin();

	static Vec2 getPositionCenterCenter();
	static Vec2 getPositionCenterLeft(Node* item);

};


#endif // _GLOBALS_H_