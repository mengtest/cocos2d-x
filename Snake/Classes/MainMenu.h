#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "cocos2d.h"

class MainMenu :public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	CREATE_FUNC(MainMenu);
	
	void menuCallBack(cocos2d::Ref *object);
};

#endif