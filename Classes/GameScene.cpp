#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto background = Sprite::create(Globals::backgroundImageSource);
	background->setPosition(POSITION_CENTER_CENTER);

	this->addChild(background, 0);

	playButton = ui::Button::create(Globals::playButtonSource[0], Globals::playButtonSource[1], Globals::playButtonSource[1]);
	playButton->setPosition(POSITION_CENTER_CENTER);

	this->addChild(playButton, 1);

	snake = Snake::create();
	//snake->setPosition(Vec2(Globals::getVisibleSize().width/2 -300, Globals::getVisibleSize().height/2+50));

	this->addChild(snake, 3);

	food = Food::create();
	//this->addChild(food, 2);

	snake->currentFood = food;

	playButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			snake->moveSnake();
			snake->scheduleUpdate();
			this->addChild(food, 2);
			this->removeChild(playButton);

			break;
		default:
			break;
		}
	});

	return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
