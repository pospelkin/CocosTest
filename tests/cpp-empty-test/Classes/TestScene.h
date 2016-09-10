#ifndef __TestScene_SCENE_H__
#define __TestScene_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"


class TestScene : public cocos2d::Layer
{
public:
	virtual bool init() override;
	static cocos2d::Scene* scene();

	CREATE_FUNC(TestScene);
	// a selector callback
	void backCallback(Ref* sender);
};

#endif // __TestScene_SCENE_H__
