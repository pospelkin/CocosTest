#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "TestScene.h"

USING_NS_CC;
using namespace ui;

ResolutionInfo resolutions[3] = { ResolutionInfo(1024, 768,0), ResolutionInfo(800,600,1), ResolutionInfo(1334,760,2) };
static ResolutionInfo activeResolution = resolutions[0];

HelloWorld::HelloWorld()
	: mFullScreenCheck(0)
{

}
Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = new HelloWorld();
	layer->autorelease();
	layer->init();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	activateResolution();

    auto visibleSize = Director::getInstance()->getWinSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	CCLabelTTF* buttonText = NULL;

    auto playItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::playCallback,this));
    
	
	buttonText = CCLabelTTF::create("PLAY", "", 22);
	buttonText->setPosition(playItem->getContentSize() * 0.5f);

	playItem->addChild(buttonText);
	playItem->setPosition(ccp(visibleSize.width * 0.5f, visibleSize.height * 0.3f));

	auto applyItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::applyCallback, this));


	buttonText = CCLabelTTF::create("APPLY", "", 22);
	buttonText->setPosition(ccp(applyItem->getContentSize().width * 0.5f, applyItem->getContentSize().height * 0.5f));

	applyItem->addChild(buttonText);
	applyItem->setPosition(ccp(visibleSize.width * 0.75f, visibleSize.height * 0.75f));


	Node* res_node = createResolutionNode();
	res_node->setPosition(ccp(visibleSize.width * 0.1f, visibleSize.height * 0.5f));
	addChild(res_node, 1000);
	auto menu = Menu::create(playItem, applyItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	for (int i = 0; i < check_arr.size(); i++)
	{
		Sprite* check = check_arr[i];
		auto item = MenuItemImage::create(
			"check.png",
			"check.png",
			CC_CALLBACK_1(HelloWorld::checkResolutionCallback, this));

		item->setTag(i);
		item->setPosition(check->getParent()->convertToWorldSpace(check->getPosition()));
		item->setContentSize(check->getContentSize());
		item->getNormalImage()->setOpacity(0);
		item->getSelectedImage()->setOpacity(0);
		menu->addChild(item);
	}

	check_arr[activeResolution.tag]->setVisible(true);

	auto item = MenuItemImage::create(
		"check.png",
		"check.png",
		CC_CALLBACK_1(HelloWorld::checkFullScreenCallback, this));

	item->setPosition(mFullScreenCheck->getParent()->convertToWorldSpace(mFullScreenCheck->getPosition()));
	item->setContentSize(mFullScreenCheck->getContentSize());
	item->getNormalImage()->setOpacity(0);
	item->getSelectedImage()->setOpacity(0);
	menu->addChild(item);
    
    return true;
}

void HelloWorld::activateResolution()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
//	glview->setFrameSize(activeResolution.w, activeResolution.h);

	if((glview->getFrameSize().width != activeResolution.w) && (glview->getFrameSize().height != activeResolution.h))
		glview->setWindowed(activeResolution.w, activeResolution.h);
}
Node* HelloWorld::createResolutionNode()
{
	auto visibleSize = Director::getInstance()->getWinSize();
	Node* node = Node::create();
	node->setContentSize(visibleSize);
	
	Vec2 start_pos = Vec2::ZERO;

	for (int i = 0; i < 3; i++)
	{
		Node* res_node = Node::create();
		res_node->setContentSize(Size(200, 200));
		CCSprite* bg = CCSprite::create("checkbox.png");
	
		CCSprite* check = CCSprite::create("check.png");
		check->setPosition(bg->getContentSize() * 0.5f);
		check->setVisible(false);
		bg->addChild(check);
		bg->setPosition(ccp(res_node->getContentSize().width * 0.f, res_node->getContentSize().height * 0.5f));
		res_node->addChild(bg);

		check_arr.push_back(check);

		ResolutionInfo info = resolutions[i];
		char buff[256];
		sprintf(buff, "%d X %d", info.w, info.h);
		
		auto label = Label::createWithTTF(buff, "fonts/arial.ttf", 22);
		label->setPosition(ccp(res_node->getContentSize().width * 0.5f, res_node->getContentSize().height * 0.5f));
		res_node->addChild(label);

		res_node->setPosition(start_pos);
		node->addChild(res_node);

		start_pos.y -= 25.f;
	}

	CCSprite* bg = CCSprite::create("checkbox.png");

	mFullScreenCheck = CCSprite::create("check.png");
	mFullScreenCheck->setPosition(bg->getContentSize() * 0.5f);
	mFullScreenCheck->setVisible(false);
	bg->addChild(mFullScreenCheck);
	bg->setPosition(ccp(node->getContentSize().width * 0.45f, node->getContentSize().height * 0));
	node->addChild(bg);


	auto label = Label::createWithTTF("FULL SCREEN \n MODE", "fonts/arial.ttf", 18);
	label->setPosition(ccp(node->getContentSize().width * 0.6f, node->getContentSize().height * 0));
	node->addChild(label);

	return node;
}
void HelloWorld::playCallback(Ref* sender)
{
	Director::getInstance()->replaceScene(TestScene::scene());
}

void HelloWorld::checkResolutionCallback(Ref* sender)
{
	Node* node = dynamic_cast<Node*>(sender);
	int tag = node->getTag();

	activeResolution = resolutions[tag];

	for (int i = 0; i < check_arr.size(); i++)
	{
		check_arr[i]->setVisible(i == tag);
	}

}

void HelloWorld::checkFullScreenCallback(Ref* sender)
{
	mFullScreenCheck->setVisible(!mFullScreenCheck->isVisible());
}

void HelloWorld::applyCallback(Ref* sender)
{
	if(!mFullScreenCheck->isVisible())
		activateResolution();
	else
	{
		auto director = Director::getInstance();
		auto glview = director->getOpenGLView();
		glview->setFullscreen();
	}
}
