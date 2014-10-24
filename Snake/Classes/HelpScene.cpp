#include "HelpScene.h"
#include "MainMenu.h"
USING_NS_CC;
Scene* HelpScene::createScene()
{
	auto scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);
	return scene;
}

bool HelpScene::init()
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
	spBackGround0->setOpacity(222);
	addChild(spBackGround0);

	auto labelScore = Label::create("HELP INFORMATION", "Î¢ÈíÑÅºÚ", 25);
	labelScore->setPosition(Vec2(visibleSize.width - labelScore->getContentSize().width, visibleSize.height - labelScore->getContentSize().height));

	auto menuItemBack = MenuItemFont::create("BACK", CC_CALLBACK_1(HelpScene::menuCallBack, this));
	menuItemBack->setPosition(Vec2(visibleSize.width - menuItemBack->getContentSize().width, visibleSize.height - menuItemBack->getContentSize().height));

	auto menu = Menu::create(menuItemBack, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
}

void HelpScene::menuCallBack(Ref *object)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}