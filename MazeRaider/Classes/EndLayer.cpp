//
// Created by aleafall on 17-3-27.
//

#include "EndLayer.h"
#include "StartLayer.h"

using namespace ui;

bool EndLayer::init() {
	if (!Layer::init()) {
		return 0;
	}
	float fontSize = 25;
	std::string fontFile = "fonts/FZKATJW.ttf";

	Color3B color3B = Color3B::YELLOW;

	Size size = Director::getInstance()->getVisibleSize();
	mBackground->setScale(size.width / mBackground->getContentSize().width);
	mBackground->setPosition(Vec2(size.width / 2, size.height / 2));
	mBackground->setColor(Color3B::GRAY);

	addChild(mBackground);

	mBoard = Sprite::create("end/blankBoard.png");
	mBoard->setPosition(Vec2(size.width / 2, size.height * 5 / 8));
	addChild(mBoard);

	Point posOfBoard(
			mBoard->getPosition() - Vec2(mBoard->getContentSize().width / 2, mBoard->getContentSize().height / 2));
	Size sizeOfBoard = mBoard->getContentSize();

	float proportion = mBoard->getContentSize().height / 6;

	mStatus = Sprite::create("end/vectory.png");
	mStatus->setPosition(posOfBoard + Vec2(sizeOfBoard.width / 2, sizeOfBoard.height * 3 / 4 - 20));
	mStatus->setScale(proportion/mStatus->getContentSize().height);

	mScoreShow = Sprite::create("end/score.png");
	mScoreShow->setPosition(posOfBoard + Vec2(sizeOfBoard.width*3 / 8, sizeOfBoard.height * 4 / 8));
	mScoreShow->setScale(proportion / mScoreShow->getContentSize().height * 0.6f);

	mTimeShow = Sprite::create("end/time.png");
	mTimeShow->setPosition(posOfBoard + Vec2(sizeOfBoard.width *3/8 , sizeOfBoard.height *3  / 8));
	mTimeShow->setScale(proportion / mTimeShow->getContentSize().height * .6f);

	std::string scoreStr = std::to_string(mScore);
	mScoreLabel = Label::createWithTTF(scoreStr, fontFile, fontSize);
	mScoreLabel->setPosition(posOfBoard + Vec2(sizeOfBoard.width * 5 / 8, sizeOfBoard.height * 4 / 8));
	mScoreLabel->setColor(color3B);

	char hh[10], mm[10], ss[10];
	sprintf(hh, "%02d", mTime / 3600);
	sprintf(mm, "%02d", mTime / 60 % 60);
	sprintf(ss, "%02d", mTime % 60);
	std::string timeStr = std::string(hh) + ":" + std::string(mm) + ":" + std::string(ss);

	mTimeLabel = Label::createWithTTF(timeStr, fontFile, fontSize);
	mTimeLabel->setPosition(posOfBoard + Vec2(sizeOfBoard.width * 5 / 8, sizeOfBoard.height * 3 / 8));
	mTimeLabel->setColor(color3B);

	mReplay = Button::create("end/replay.png");
	mReplay->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			CCLOG("replay");
			auto scene = StartLayer::createScene();
			auto rs = TransitionFade::create(1.0f, scene);
			Director::getInstance()->replaceScene(rs);
		}
	});
	mReplay->setPosition(Vec2(size.width / 4, size.height * 0.15f));


	mExit = Button::create("end/exit.png");
	mExit->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			CCLOG("exit");
			Director::getInstance()->end();
		}
	});
	mExit->setPosition(Vec2(size.width * 3 / 4, size.height * 0.15f));

	addChild(mStatus);
	addChild(mScoreShow,1);
	addChild(mScoreLabel);
	addChild(mTimeShow);
	addChild(mTimeLabel);
	addChild(mReplay);
	addChild(mExit);

	return 1;
}

Scene *EndLayer::createScene(int score,int timeCount,const std::string &filePath) {
	auto scene = Scene::create();
	auto layer = EndLayer::create(score,timeCount,filePath);
	scene->addChild(layer);
	return scene;
}

EndLayer::EndLayer(int score, int timeCount, const std::string &filePath) : mScore(score), mTime(timeCount) {
	mBackground = Sprite::create(filePath);
}

EndLayer *EndLayer::create(int score, int timeCount, const std::string &filePath) {
	EndLayer *layer = new EndLayer(score, timeCount, filePath);
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}
