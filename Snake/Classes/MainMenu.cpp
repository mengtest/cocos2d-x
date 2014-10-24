#include "MainMenu.h"
#include "GameScene.h"
#include "HelpScene.h"

USING_NS_CC;
Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto spBackGround0 = Sprite::create("menubackground0.png");
	spBackGround0->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	spBackGround0->setScale(1.5);
	addChild(spBackGround0);
	auto spBackGround1 = Sprite::create("menubackground1.png");
	spBackGround1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	addChild(spBackGround1);

	
	auto menuItemStart = MenuItemFont::create("START", CC_CALLBACK_1(MainMenu::menuCallBack, this));
	menuItemStart->setPosition(Vec2(visibleSize.width - menuItemStart->getContentSize().width, visibleSize.height - menuItemStart->getContentSize().height));
	menuItemStart->setTag(0x11);
	auto menuItemHelp = MenuItemFont::create("HELP", CC_CALLBACK_1(MainMenu::menuCallBack, this));
	menuItemHelp->setPosition(Vec2(visibleSize.width - menuItemStart->getContentSize().width, visibleSize.height - menuItemHelp->getContentSize().height - menuItemStart->getContentSize().height - 10));
	menuItemHelp->setTag(0x12);

	auto menu = Menu::create(menuItemStart,menuItemHelp,nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
	

	return true;
}

void MainMenu::menuCallBack(Ref *object)
{
	auto target = dynamic_cast<Node*>(object);
	Scene *scene=nullptr;
	switch (target->getTag())
	{
	case 0x11:
		scene = GameScene::createScene();
		break;
	case 0x12:
		scene = HelpScene::createScene();
		break;
	default:
		return;
		break;
	}
	Director::getInstance()->replaceScene(scene);
}