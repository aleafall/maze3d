#include "StartLayer.h"
#include "MainLayer.h"
#include "MazeLayer.h"

using namespace ui;

Scene *StartLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = StartLayer::create();
	scene->addChild(layer);
	return scene;
}
bool StartLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();

	std::string filePath = "begin/";
	mBackground = Sprite::create(filePath+"bg-02.jpg");
	mBackground->setPosition(Point(size.width / 2, size.height / 2));
	addChild(mBackground);

	mEasy = Button::create(filePath+"easy.png");
	mMedium = Button::create(filePath+"medium.png");
	mExit = Button::create(filePath+"exit.png");

	mTitle = Sprite::create(filePath+"title.png");

	mEasy->setPosition(Point(size.width / 4, size.height / 4));
	mMedium->setPosition(Point(size.width / 2, size.height / 4));
	mExit->setPosition(Point(size.width * 3 / 4, size.height / 4));

	mEasy->setScale(0.3f);
	mMedium->setScale(0.3f);
	mExit->setScale(0.3f);

	mTitle->setScale(0.5f);

	mTitle->setPosition(Point(size.width / 2, size.height * 3 / 4));

	mEasy->addTouchEventListener([](Ref *sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			MazeLayer::M = 10;
			MazeLayer::N = 10;
			CCLOG("easy");
			auto mainLayer = MainLayer::createScene();
			auto rs = TransitionCrossFade::create(1.0f, mainLayer);
			Director::getInstance()->replaceScene(rs);
		}

	});

	mMedium->addTouchEventListener([](Ref *sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			MazeLayer::M = 20;
			MazeLayer::N = 20;
			CCLOG("medium");
			auto mainLayer = MainLayer::createScene();
			auto rs = TransitionCrossFade::create(1.0f, mainLayer);
			Director::getInstance()->replaceScene(rs);
		}

	});

	mExit->addTouchEventListener([](Ref *sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->end();
		}

	});


	addChild(mEasy);
	addChild(mMedium);
	addChild(mExit);

	addChild(mTitle);

	return true;

}