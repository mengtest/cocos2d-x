#ifndef _HELPSCENE_H_
#define _HELPSCENE_H_

#include "cocos2d.h"

class HelpScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);

	void menuCallBack(cocos2d::Ref *object);
};

#endif