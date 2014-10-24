#include "GameScene.h"
#include "MainMenu.h"
#include <sstream>
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
USING_NS_CC;
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	srand(time(nullptr));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	m_score = 0;

	auto spBackGround0 = Sprite::create("menubackground0.png");
	spBackGround0->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	spBackGround0->setScale(1.5);
	addChild(spBackGround0);

	auto draw = DrawNode::create();
	draw->setAnchorPoint(Vec2::ZERO);
	draw->setPosition(Vec2::ZERO);
	for (int i = 0; i <= 20; i++)
	{
		draw->drawSegment(Vec2(i * 20, 0), Vec2(i * 20, 400), 1, Color4F(0.5, 0.5, 0.5, 1));
	}
	for (int i = 0; i <= 20; i++)
	{
		draw->drawSegment(Vec2(0, i * 20), Vec2(400, i * 20), 1, Color4F(0.5, 0.5, 0.5, 1));
	}
	addChild(draw);

	auto labelScore = Label::create("SCORE 0","Î¢ÈíÑÅºÚ",25);
	auto menuItemBack = MenuItemFont::create("BACK", CC_CALLBACK_1(GameScene::menuCallBack, this));
	labelScore->setTag(0x11);
	labelScore->setPosition(Vec2(visibleSize.width - menuItemBack->getContentSize().width, visibleSize.height - labelScore->getContentSize().height));
	addChild(labelScore);

	menuItemBack->setPosition(Vec2(visibleSize.width - menuItemBack->getContentSize().width, visibleSize.height - menuItemBack->getContentSize().height-labelScore->getContentSize().height-10));

	auto menu = Menu::create(menuItemBack, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	spHead = SnakeNode::create(SnakeNode::NODE_TYPE::TYPE_HEAD);
	spFood = SnakeNode::create(SnakeNode::NODE_TYPE::TYPE_FOOD);
	//spHead->setAnchorPoint(Vec2::ZERO);
	//spFood->setAnchorPoint(Vec2::ZERO);
	spHead->setPosition(Vec2(rand() % 20, rand() % 20) * 20);
	spFood->setPosition(Vec2(rand() % 20, rand() % 20) * 20);
	addChild(spHead);
	addChild(spFood);

	schedule(schedule_selector(GameScene::gameLogic),0.5);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool GameScene::collision()
{
	for (auto m : vBody)
	{
		if (spHead->getPosition() == m->getPosition())
		{
			return true;
		}
	}
	return false;
}

void GameScene::menuCallBack(Ref *object)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool SnakeNode::init(NODE_TYPE type)
{
	if (!Sprite::init())
	{
		return false;
	}
	
	switch (type)
	{
		Sprite *node;
	case NODE_TYPE::TYPE_HEAD:
		node = Sprite::create("head.png");
		//node->setAnchorPoint(Vec2::ZERO);
		addChild(node);
		m_dir = NODE_DIR::DIR_RIGHT;
		break;
	case NODE_TYPE::TYPE_BODY:
		node = Sprite::create("body.png");
		//node->setAnchorPoint(Vec2::ZERO);
		addChild(node);
		m_dir = NODE_DIR::DIR_STOP;
		break;
	case NODE_TYPE::TYPE_FOOD:
		node = Sprite::create("food.png");
		//node->setAnchorPoint(Vec2::ZERO);
		addChild(node);
		m_dir = NODE_DIR::DIR_STOP;
		break;
	default:
		break;
	}
	return true;
}

SnakeNode *SnakeNode::create(NODE_TYPE type)
{
	SnakeNode *pRet = new SnakeNode();
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void GameScene::gameLogic(float t)
{
	
	switch (spHead->m_dir)
	{
	case SnakeNode::NODE_DIR::DIR_UP:
		spHead->runAction(MoveBy::create(0.1, Vec2(0, 20)));
		break;
	case SnakeNode::NODE_DIR::DIR_DOWN:
		spHead->runAction(MoveBy::create(0.1, Vec2(0, -20)));
		break;
	case SnakeNode::NODE_DIR::DIR_LEFT:
		spHead->runAction(MoveBy::create(0.1, Vec2(-20, 0)));
		break;
	case SnakeNode::NODE_DIR::DIR_RIGHT:
		spHead->runAction(MoveBy::create(0.1, Vec2(20, 0)));
		break;
	default:
		break;
	}
	if (collision())
	{
		Director::getInstance()->replaceScene(createScene());
	}
	moveBody();
	if (spHead->getPosition() == spFood->getPosition())
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/eat.mp3");
		m_score+=10;
		std::ostringstream ss;
		ss << "SCORE " << m_score;
		dynamic_cast<Label*>(getChildByTag(0x11))->setString(ss.str());
		newBody();
		spFood->setPosition(Vec2(rand() % 20, rand() % 20) * 20);
	}
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	SnakeNode::NODE_DIR dirTo;
	if (abs(touch->getLocation().x - spHead->getPositionX())>abs(touch->getLocation().y - spHead->getPositionY()))
	{
		if (touch->getLocation().x<spHead->getPositionX())
		{
			dirTo = SnakeNode::NODE_DIR::DIR_LEFT;
		}
		else
		{
			dirTo = SnakeNode::NODE_DIR::DIR_RIGHT;
		}
	}
	else
	{
		if (touch->getLocation().y<spHead->getPositionY())
		{
			dirTo = SnakeNode::NODE_DIR::DIR_DOWN;
		}
		else
		{
			dirTo = SnakeNode::NODE_DIR::DIR_UP;
		}
	}
	spHead->turnDir(dirTo);
	return true;
}

void SnakeNode::turnDir(NODE_DIR dir)
{
	switch (m_dir)
	{
	case NODE_DIR::DIR_UP:
		switch (dir)
		{
		case NODE_DIR::DIR_LEFT:
			m_dir = dir;
			runAction(RotateBy::create(0.1,-90));
			break;
		case NODE_DIR::DIR_RIGHT:
			m_dir = dir;
			runAction(RotateBy::create(0.1, 90));
			break;
		default:
			break;
		}
		break;
	case NODE_DIR::DIR_LEFT:
		switch (dir)
		{
		case NODE_DIR::DIR_UP:
			m_dir = dir;
			runAction(RotateBy::create(0.1, 90));
			break;
		case NODE_DIR::DIR_DOWN:
			m_dir = dir;
			runAction(RotateBy::create(0.1, -90));
			break;
		default:
			break;
		}
		break;
	case NODE_DIR::DIR_DOWN:
		switch (dir)
		{
		case NODE_DIR::DIR_LEFT:
			m_dir = dir;
			runAction(RotateBy::create(0.1, 90));
			break;
		case NODE_DIR::DIR_RIGHT:
			m_dir = dir;
			runAction(RotateBy::create(0.1, -90));
			break;
		default:
			break;
		}
		break;
	case NODE_DIR::DIR_RIGHT:
		switch (dir)
		{
		case NODE_DIR::DIR_UP:
			m_dir = dir;
			runAction(RotateBy::create(0.1, -90));
			break;
		case NODE_DIR::DIR_DOWN:
			m_dir = dir;
			runAction(RotateBy::create(0.1, 90));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{

}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void GameScene::newBody()
{
	auto bodyNode = SnakeNode::create(SnakeNode::NODE_TYPE::TYPE_BODY);
	SnakeNode *lastBody = vBody.empty() ? spHead : vBody.back();
	bodyNode->m_dir = lastBody->m_dir;
	bodyNode->setPosition(lastBody->getPosition());
	vBody.pushBack(bodyNode);
	addChild(bodyNode);
}
void GameScene::moveBody()
{
	if (vBody.empty())
	{
		return;
	}
	for (auto m : vBody)
	{
		switch (m->m_dir)
		{
		case SnakeNode::NODE_DIR::DIR_UP:
			m->runAction(MoveBy::create(0.1, Vec2(0, 20)));
			break;
		case SnakeNode::NODE_DIR::DIR_DOWN:
			m->runAction(MoveBy::create(0.1, Vec2(0, -20)));
			break;
		case SnakeNode::NODE_DIR::DIR_LEFT:
			m->runAction(MoveBy::create(0.1, Vec2(-20, 0)));
			break;
		case SnakeNode::NODE_DIR::DIR_RIGHT:
			m->runAction(MoveBy::create(0.1, Vec2(20, 0)));
			break;
		default:
			break;
		}
	}
	for (int i = vBody.size() - 1; i > 0; i--)
	{
		vBody.at(i)->m_dir = vBody.at(i - 1)->m_dir;
	}
	vBody.at(0)->m_dir = spHead->m_dir;
}