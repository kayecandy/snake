#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#define COCOS2D_DEBUG 1

#include "Globals.h"
#include "ui/CocosGUI.h"
#include "Snake.h"
#include "Food.h"


class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	Snake* snake;
	Food* food;
	ui::Button* playButton;

	

};

#endif // __HELLOWORLD_SCENE_H__
