#ifndef STARTLAYER_H_
#define STARTLAYER_H_

#include "cocos2d.h"
#include <ui/UIButton.h>

USING_NS_CC;

class StartLayer:public Layer
{
public:
	static Scene *createScene();
	bool init() override;
	CREATE_FUNC(StartLayer);
protected:
private:
	Sprite *mTitle;

	ui::Button *mEasy;
	ui::Button *mMedium;
	ui::Button *mExit;

	Sprite *mBackground;
};

#endif // !STARTLAYER_H_
