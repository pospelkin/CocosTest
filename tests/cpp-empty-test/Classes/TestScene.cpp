#include "TestScene.h"
#include "AppMacros.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* TestScene::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	TestScene *layer = new TestScene();
	layer->autorelease();
	layer->init();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getWinSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	CCLabelTTF* buttonText = NULL;

	auto backItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(TestScene::backCallback, this));


	buttonText = CCLabelTTF::create("BACK", "", 22);
	buttonText->setPosition(backItem->getContentSize() * 0.5f);

	backItem->addChild(buttonText);
	backItem->setPosition(ccp(visibleSize.width * 0.5f, visibleSize.height * 0.3f));

	auto menu = Menu::create(backItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	return true;
}


void TestScene::backCallback(Ref* sender)
{
	Director::getInstance()->replaceScene(HelloWorld::scene());
}