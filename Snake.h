#include "GameScene.h"

#ifndef __SNAKE_H__
#define __SNAKE_H__


#include "Globals.h"
#include "SnakePart.h"
#include "Food.h"
#include <cmath>

class Snake : public Node{
public:
	enum Direction
	{
		DIRECTION_RIGHT = 1,
		DIRECTION_LEFT = -1
	};

	enum SnakeProperties{
		DIVIDER = 1000,

		Z_INDEX_HEAD = 2,
		Z_INDEX_BODY = 1,

		SNAKE_HEAD_ANCHOR_X = 500,
		SNAKE_HEAD_ANCHOR_Y = 0,
		SNAKE_PART_ANCHOR_X = 500,
		SNAKE_PART_ANCHOR_Y = 0,

		BODY_INTERVAL = 70,

		ROTATION_SPEED = 100,
		MIN_ROTATION_ANGLE = 22500,

		INITIAL_SIZE = 5,
		MAX_SIZE = 100,
		INITIAL_MOVE_SPEED = 300,
		INITIAL_ROTATION = 90,
		MOVE_SPEED_INCREMENT = 50,
		MOVE_LENGTH = 100,

		WARP_DISTANCE_ALLOWANCE = 1500
	};

	static Snake* create();
	virtual bool init();

	void rotateSnakeHead(int dir);

	void onKeyboardPressed(EventKeyboard::KeyCode, Event*);
	void onKeyboardReleased(EventKeyboard::KeyCode, Event*);

	void addSnakeBody();

	void moveSnake();

	Food* currentFood;

	void update(float) override;

private:
	SnakePart* snakeHead;
	Vector<SnakePart*> snakeBodyParts;

	int size;

	int direction;
	bool isKeyPressed;
	bool isHeadRotating;

	int moveSpeed;
	bool isMoving;
	bool isAlive;

	SpriteFrameCache* snakeSpriteCache;

	void initializeSnakeParts();
	void initializeVariables();
	void initializeKeyboardEvents();

	void rotateEnd();
	void moveEnd();

	void checkCollisionBodyParts();
	void checkHitWall();
	void checkCollisionFood();

	bool checkHeadCollision(Node* object);

};



#endif // __SNAKE_H__