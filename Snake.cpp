#include "Snake.h"


USING_NS_CC;

Snake* Snake::create(){
	Snake* s = new (std::nothrow)Snake();

	if (s && s->init())
	{
		s->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(s);
	}
	return s;
}

bool Snake::init(){

	if (!Node::init()){
		return false;
	}

	// VARIABLES
	initializeVariables();

	// SNAKE PARTS
	initializeSnakeParts();

	// LISTENER
	initializeKeyboardEvents();

	//moveSnake();


	return true;
}

void Snake::initializeSnakeParts(){

	//Snake head
	snakeHead = SnakePart::create(AutoPolygon::generatePolygon(Globals::snakeSprite[Globals::INDEX_SNAKE_HEAD]));
	//snakeHead->setPosition(POSITION_CENTER_LEFT(snakeHead));
	snakeHead->setAnchorPoint(Vec2((float)SNAKE_HEAD_ANCHOR_X / DIVIDER, (float)SNAKE_HEAD_ANCHOR_Y / DIVIDER));
	snakeHead->setRotation(INITIAL_ROTATION);

	this->addChild(snakeHead, Z_INDEX_HEAD);
	snakeBodyParts.pushBack(snakeHead);

	

	for (int i = 1; i < INITIAL_SIZE; i++){
		addSnakeBody();
	}


	
}

void Snake::initializeVariables(){
	isKeyPressed = false;
	isHeadRotating = false;

	isMoving = false;
	isAlive = true;

	moveSpeed = INITIAL_MOVE_SPEED;
	size = 1;
}

void Snake::initializeKeyboardEvents(){
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Snake::onKeyboardPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Snake::onKeyboardReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Snake::rotateSnakeHead(int direction){

	this->direction = direction;
	auto rotate = RotateBy::create((float)ROTATION_SPEED/DIVIDER, (float)MIN_ROTATION_ANGLE/DIVIDER * direction);
	auto end = CallFunc::create(this, CC_CALLFUNC_SELECTOR(Snake::rotateEnd));

	isHeadRotating = true;

snakeHead->runAction(Sequence::create(rotate, end, NULL));

}

void Snake::rotateEnd(){
	isHeadRotating = false;
	if (isKeyPressed){
		rotateSnakeHead(direction);
	}
	else{
		//cocos2d::log("rotation: %f", snakeHead->getRotation());
	}

}

void Snake::onKeyboardPressed(EventKeyboard::KeyCode keyCode, Event* event){
	if (!isHeadRotating){
		isKeyPressed = true;
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			rotateSnakeHead(DIRECTION_LEFT);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			rotateSnakeHead(DIRECTION_RIGHT);
			break;
		default:
			break;
		}
	}



}

void Snake::onKeyboardReleased(EventKeyboard::KeyCode keyCode, Event* event){
	isKeyPressed = false;
}

float sind(float radian){
	return sin(radian*M_PI / 180.0f);
}
float cosd(float radian){
	return cos(radian*M_PI / 180.0f);
}

bool isSnakePartWarping(SnakePart* s1, SnakePart* s2){
	float difX = abs(s1->getPositionX() - s2->getPositionX());
	float difY = abs(s1->getPositionY() - s2->getPositionY());

	//cocos2d::log("distance: %f %f, %f", difX, difY, SCREEN_HEIGHT);

	return s1->getPositionY() > SCREEN_POSITION_TOP + s1->getContentSize().height;


	//return difX >= Snake::BODY_INTERVAL * (float)Snake::WARP_DISTANCE_ALLOWANCE / Snake::DIVIDER
	//	|| difY >= Snake::BODY_INTERVAL * (float)Snake::WARP_DISTANCE_ALLOWANCE / Snake::DIVIDER;

	return false;

}

void Snake::update(float delta){
	checkCollisionBodyParts();
	checkHitWall();
	checkCollisionFood();
}

void Snake::moveSnake(){

	//snakeHead->warp();
	//cocos2d::log("rotation: %f, x: %f, y: %f", snakeHead->getRotation(), BODY_INTERVAL*sind(snakeHead->getRotation()), BODY_INTERVAL*cosd(snakeHead->getRotation()));
	auto move = MoveBy::create((float)moveSpeed / DIVIDER, Vec2(BODY_INTERVAL*sind(snakeHead->getRotation()), BODY_INTERVAL*cosd(snakeHead->getRotation())));
	auto end = CallFunc::create(this, CC_CALLFUNC_SELECTOR(Snake::moveEnd));

	isMoving = true;


	snakeHead->runAction(Sequence::create(move, end, NULL));

	for (int i = 1; i < size; i++){
		//snakeBodyParts.at(i)->warp();

		auto move = MoveTo::create((float)moveSpeed / DIVIDER, snakeBodyParts.at(i - 1)->getPosition());
		snakeBodyParts.at(i)->runAction(move);

		auto rotate = RotateTo::create((float)moveSpeed / DIVIDER, (int)(snakeBodyParts.at(i - 1)->getRotation()) % 360);
		snakeBodyParts.at(i)->runAction(rotate);
	}
}

void Snake::moveEnd(){
	isMoving = false;

	if (isAlive){
		moveSnake();
	}
	else{
		
		auto currentScene = Director::sharedDirector()->getRunningScene();
		Director::sharedDirector()->replaceScene(GameScene::createScene());
		
	}
}

void Snake::checkCollisionFood(){
	if (checkHeadCollision(currentFood)){
		addSnakeBody();
		currentFood->reposition();
		cocos2d::log("hellooo");
	}
	
}

void Snake::checkHitWall(){
	float length = (1 - snakeHead->getAnchorPoint().y) * snakeHead->getContentSize().height;
	float targetX = snakeHead->getPositionX() + sind(snakeHead->getRotation()) * length;
	float targetY = snakeHead->getPositionY() + cosd(snakeHead->getRotation()) * length;

	if (targetX < SCREEN_POSITION_LEFT
		|| targetX > SCREEN_POSITION_RIGHT
		|| targetY < SCREEN_POSITION_BOTTOM
		|| targetY > SCREEN_POSITION_TOP){
		isAlive = false;
	}
}

bool Snake::checkHeadCollision(Node* object){
	float length = (1 - snakeHead->getAnchorPoint().y) * snakeHead->getContentSize().height;
	float targetX = snakeHead->getPositionX() + sind(snakeHead->getRotation()) * length;
	float targetY = snakeHead->getPositionY() + cosd(snakeHead->getRotation()) * length;

	Rect objectRect = CCRectMake(
		object->getPositionX() - object->getContentSize().width * object->getAnchorPoint().x,
		object->getPositionY() - object->getContentSize().height * object->getAnchorPoint().y,
		object->getContentSize().width,
		object->getContentSize().height);

	cocos2d::log("%f %f", object->getPositionX(), object->getPositionY());

	//return objectRect.containsPoint(Vec2(targetX, targetY));
	return objectRect.intersectsCircle(Vec2(targetX, targetY), 25);
}

void Snake::checkCollisionBodyParts(){
	for (int i = 3; i < size; i++){

		if (checkHeadCollision(snakeBodyParts.at(i))){
			cocos2d::log("collided");
			isAlive = false;
			break;
		}
	}
}

void Snake::addSnakeBody(){
	auto body = SnakePart::create(AutoPolygon::generatePolygon(Globals::snakeSprite[Globals::INDEX_SNAKE_PART]));
	auto last = snakeBodyParts.back();
	body->setPosition(Vec2(last->getPositionX() + sind(last->getRotation() + 180)*BODY_INTERVAL, last->getPositionY() + cosd(last->getRotation() + 180)*BODY_INTERVAL));
	body->setRotation(last->getRotation());
	body->setAnchorPoint(Vec2((float)SNAKE_PART_ANCHOR_X / DIVIDER, (float)SNAKE_PART_ANCHOR_Y / DIVIDER));

	this->addChild(body, Z_INDEX_BODY);
	snakeBodyParts.pushBack(body);
	size++;
}
