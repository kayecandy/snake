#include "Globals.h"

char* Globals::backgroundImageSource = "background.jpg";
char* Globals::playButtonSource[3] = {
	"play_button.png", 
	"play_button_hover.png", 
	""
};

char* Globals::snakeSprite[2] = {
	"snake/snake_head.png",
	"snake/snake_part.png"
};

char* Globals::foodSprite[2] = {
	"glow.png",
	"apple.png"
};

Size Globals::getVisibleSize(){
	return cocos2d::Director::getInstance()->getVisibleSize();
}

Vec2 Globals::getOrigin(){
	return cocos2d::Director::getInstance()->getVisibleOrigin();
}

Vec2 Globals::getPositionCenterCenter(){
	Size visibleSize = getVisibleSize();
	Vec2 origin = getOrigin();

	return Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
}

Vec2 Globals::getPositionCenterLeft(Node* item){
	Size visibleSize = getVisibleSize();
	Vec2 origin = getOrigin();

	return Vec2(origin.x + item->getContentSize().width/2, origin.y + visibleSize.height / 2);
}
