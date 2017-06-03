#include "MainLayer.h"
#include "Minimap.h"
#include "EndLayer.h"


Scene *MainLayer::createScene() {
	auto scene = Scene::create();
	auto layer = MainLayer::create();
	scene->addChild(layer);
	return scene;
}

bool MainLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	mGameOver = 0;
	complex = 0.8;


	Size size = Director::getInstance()->getVisibleSize();

	std::string skyPath = "skybox/";
	TextureCube *texture = TextureCube::create(skyPath + "left.jpg", skyPath + "right.jpg", skyPath + "top.jpg",
	                                           skyPath + "bottom.jpg", skyPath + "front.jpg", skyPath + "back.jpg");
	skyBox = Skybox::create();
	skyBox->setTexture(texture);
	addChild(skyBox);

	mPlayer = Player::createPlayer("Players/zhanshi.c3b");
	mPlayer->setPosition3D(Vec3(5, 0, -5.0f));
	mPlayer->setScale(1.0f);
	mPlayer->setRotation3D(Vec3(0.0f, 180.0f, 0.0f));
	addChild(mPlayer, 1, PLAYER_TAG);

	


	Animation3D *animation3d = Animation3D::create("Players/zhanshi.c3b");
	Animate3D *animate = Animate3D::create(animation3d);
	mPlayer->runAction(RepeatForever::create(animate));

	mMap = Sprite3D::create("map/ttt.c3b");

	mMap->setPosition3D(mPlayer->getPosition3D() + Vec3(80, 0, 0));
	mMap->setScale(5.0f);
	mMap->setVisible(false);
	addChild(mMap, 0, MAP_TAG);

	

	mMaze = MazeLayer::createMaze(MazeLayer::M, MazeLayer::N, complex);
	addChild(mMaze, 0, MAZE_TAG);
	mMaze->drawMaze();
//	mMaze->initProp();		


	mCamera = Camera::createPerspective(60.0f, (GLfloat) size.width / (GLfloat) size.height, 1.0f, 1000.0f);
	mCamera->setCameraFlag(CameraFlag::USER1);
	mCamera->setPosition3D(mPlayer->getPosition3D() + Vec3(0.0f, cameraY, cameraZ));
	mCamera->lookAt(mPlayer->getPosition3D(), Vec3(0, 1, 0));
	mCameraLayer = Layer::create();
	addChild(mCamera, 0, CAMERA_TAG);

	this->setCameraMask((unsigned short) CameraFlag::USER1);

	mRocker = Rocker::createRocker("buttons/Direction_bt.png", "buttons/Direction_bc.png",
	                               Point(size.width * .15f, size.height * .2f));
	mRocker->startRocker(true);
	addChild(mRocker);
	
	mPlayer->setRocker(mRocker);

	int x = mPlayer->getPosition3D().x, y = mPlayer->getPosition3D().y, z = mPlayer->getPosition3D().z;

	std::string pos =
			"pos " + StringUtils::toString(x) + " " + StringUtils::toString(y) + " " + StringUtils::toString(z);
	mPos = Label::create(pos, "Arial", 20);
	mPos->setPosition(Point(size.width * .1f, size.height * .8f));
	mPos->setColor(Color3B(0, 255, 0));
	addChild(mPos, 0, POS_TAG);
	mPos->setVisible(false);

	


	

	//minimap
	Minimap *minimap = Minimap::createMap();
	addChild(minimap, 0, MINIMAP_TAG);
	minimap->showMap();
	

	ss = 0, mm = 0, hh = 0;
	mScores = 0;

	mTimeShow = Label::createWithSystemFont("00:00:00", "Arial", 24);
	mTimeShow->setPosition(Vec2(size.width * 0.8f, size.height * 0.9f));
	mTimeShow->setColor(Color3B(0, 255, 0));
	addChild(mTimeShow);

	mScoreShow = Label::createWithSystemFont("00", "Arial", 24);
	mScoreShow->setPosition(Vec2(size.width * 0.2f, size.height * 0.9f));
	mScoreShow->setColor(Color3B(0, 255, 0));
	addChild(mScoreShow);

	mPause = Button::create("buttons/pause_1.png", "buttons/pause_2.png");
	mPause->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// switch to pauseLayer
//			CCLOG("switch");

			auto func = [](bool succeed, const std::string &filePath) {
				if (succeed) {
					auto pauseScene = PauseLayer::createScene(filePath);
					Director::getInstance()->pushScene(pauseScene);
				}
			};
			utils::captureScreen(func, "ScreenShot.png");
			/*mIsPausing = 1;
			mPauseLayer->setVisible(1);*/
		}
	});
	mPause->setPosition(Vec2(size.width * 0.05f, size.height * 0.9f));
	addChild(mPause);

	mCountPerFrame = 0;


	scheduleUpdate();
	return true;
}

void MainLayer::update(float delta) {
	/*if (mIsPausing) {
		*//*if (!Director::getInstance()->isPaused()) {
			Director::getInstance()->pause();
		}*//*
		return;
	}*/
	mPlayer->updatePos();
	mCountPerFrame += delta;
	if (mCountPerFrame >= 1.0f) {
		mCountPerFrame = 0;
		setTime();
	}
}

void MainLayer::setScore() {

}

void MainLayer::setTime() {
	ss += 1;
	if (ss >= 60) {
		ss = 0;
		++mm;
	}
	if (mm >= 60) {
		mm = 0;
		++hh;
	}
	char HH[5], MM[5], SS[5];
	sprintf(HH, "%02d", hh);
	sprintf(MM, "%02d", mm);
	sprintf(SS, "%02d", ss);
	std::string str = std::string(HH) + ":" + std::string(MM) + ":" + std::string(SS);
	mTimeShow->setString(str);
}

void MainLayer::setGameOver() {
	mGameOver = 1;
	auto func = [=](bool succeed, const std::string &filePath) {
		if (succeed) {
			int timeCount = (hh * 3600 + mm * 60 + ss)%(24*3600);
			auto endScene = EndLayer::createScene(mScores, timeCount, filePath);
			auto rs = TransitionMoveInL::create(1.0f, endScene);
			Director::getInstance()->replaceScene(rs);
		}
	};
	utils::captureScreen(func, "ScreenShot.png");
}

void MainLayer::setRange(int m, int n,float com)
{
	this->M = m;
	this->N = n;
	this->complex = com;
}
void MainLayer::initMaze()
{
	
}
