//
// Created by aleafall on 17-3-26.
//

#include "PauseLayer.h"
#include "MazeStartScene.h"
#include "MainLayer.h"
#include "StartLayer.h"

using namespace ui;

bool PauseLayer::init() {
	if (!Layer::init()) {
		return 0;
	}
	Size size = Director::getInstance()->getVisibleSize();

	mBackground = Sprite::create("buttons/top.jpg");
	mBackground->setOpacity(125);
//	addChild(mBackground);
	mBackground->setPosition(Vec2(size.width / 2, size.height / 2));

	mResume = Button::create("buttons/resume.png");
	mResume->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
//			CCLOG("resume");
			Director::getInstance()->popScene();
			/*this->setVisible(0);
			MainLayer *layer = static_cast<MainLayer *>(this->getParent());
			layer->setMIsPausing(0);*/
//			Director::getInstance()->resume();
		}
	});
	mResume->setPosition(Vec2(size.width * .7f, size.height * .5f));
	addChild(mResume);

	mBegin = Button::create("buttons/back.png");
	mBegin->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			CCLOG("toBegin");
			auto scene = StartLayer::createScene();
			Director::getInstance()->popScene();
			/*if (Director::getInstance()->isPaused()) {
				Director::getInstance()->resume();
			}*/
			auto rs = TransitionFadeDown::create(1.5f, scene);
			Director::getInstance()->replaceScene(rs);
		}
	});
	mBegin->setPosition(Vec2(size.width * .3f, size.height * .5f));
	addChild(mBegin);

	return 1;
}

Scene *PauseLayer::createScene(const std::string &filePath) {
	auto scene = Scene::create();
	auto layer = PauseLayer::create();
	Size size = Director::getInstance()->getVisibleSize();
	Sprite *background = Sprite::create(filePath);
	background->setPosition(Vec2(size.width / 2, size.height / 2));
	background->setScale(size.height / background->getTextureRect().getMaxY());
	background->setColor(Color3B::GRAY);
	scene->addChild(background);

	scene->addChild(layer, 1);
	return scene;
}
