#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"

class SnakeNode:public cocos2d::Sprite
{
public:
	enum class NODE_DIR{ DIR_UP, DIR_LEFT, DIR_DOWN , DIR_RIGHT, DIR_STOP };
	enum class NODE_TYPE{ TYPE_HEAD, TYPE_BODY, TYPE_FOOD };
	NODE_DIR m_dir;
	virtual bool init(NODE_TYPE type);
	NODE_TYPE m_type;
	static SnakeNode*create(NODE_TYPE type);
	void turnDir(NODE_DIR dir);
};

class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	void menuCallBack(cocos2d::Ref *object);
	void gameLogic(float t);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void newBody();
	void moveBody();
	bool collision();
private:
	SnakeNode *spHead;
	SnakeNode *spFood;
	cocos2d::Vector<SnakeNode*> vBody;
	int m_score;
};

#endif