#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"


struct ResolutionInfo
{
	ResolutionInfo()
	{
		w = 0;
		h = 0;
		tag = 0;
	}
	ResolutionInfo(int a, int b, int t)
	{
		w = a;
		h = b;
		tag = t;
	}

	int w;
	int h;
	int tag;
};



class HelloWorld : public cocos2d::Layer
{
public:
    virtual bool init() override;
	HelloWorld();
    static cocos2d::Scene* scene();

    // a selector callback
    void playCallback(Ref* sender);
	void checkResolutionCallback(Ref* sender);
	void checkFullScreenCallback(Ref* sender);
	void applyCallback(Ref* sender);
    // implement the "static create()" method manually

	void activateResolution();
	Node* createResolutionNode();
	
	std::vector<cocos2d::Sprite*> check_arr;
	cocos2d::Sprite* mFullScreenCheck;
};

#endif // __HELLOWORLD_SCENE_H__
