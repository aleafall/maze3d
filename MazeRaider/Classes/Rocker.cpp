#include "Rocker.h"
#include "MainLayer.h"
#include "Minimap.h"
#include "Player.h"

const double PI = 3.1415;

Point getAngelePosition(float r, float angle) {
	return Vec2((float)(r * cos(angle)), (float)(r * sin(angle)));
}
Rocker* Rocker::createRocker(const std::string &rockerImageName, const std::string &rockerBGImageName, Point position) {
	Rocker *layer = Rocker::create();
	if (layer&&layer->init()) {
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		layer->rocketDirection = ROCKER_CENTER;
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool Rocker::init() {
	if (!Layer::init()) {
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();
	mJumpBtn = ui::Button::create("buttons/jump.png");
	mJumpBtn->setPosition(Point(size.width*.85f, size.height*.2f));
	mJumpBtn->setScale(.5f);
	mJumpBtn->addTouchEventListener(this, toucheventselector(Rocker::onClickJumpBtn));
	addChild(mJumpBtn);
	return true;
}

void Rocker::startRocker(bool isStopOther) {
	Sprite *rocker = static_cast<Sprite*>(this->getChildByTag(ROCKER_TAG));
	rocker->setVisible(true);

	Sprite *rockerBG = static_cast<Sprite*>(this->getChildByTag(ROCKERBG_TAG));
	rockerBG->setVisible(true);

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *touch, Event *event) {
		Point point = touch->getLocation();
		Sprite *r = static_cast<Sprite*>(getChildByTag(ROCKER_TAG));
		if (r->getBoundingBox().containsPoint(point))
			isCanMove = true;
		return true;
	};
	listener->onTouchMoved = [&](Touch *touch, Event *event) {
		if (!isCanMove) {
			return;
		}
		Point point = touch->getLocation();
		Sprite *r = static_cast<Sprite*>(getChildByTag(ROCKER_TAG));
		float angle = getRad(rockerBGPosition, point);
		if (sqrt(pow((rockerBGPosition.x - point.x), 2) + pow((rockerBGPosition.y - point.y), 2)) >= rockerBGR) {

			r->setPosition(getAngelePosition(rockerBGR, angle) + Vec2(rockerBGPosition.x, rockerBGPosition.y));
		} else
			r->setPosition(point);

		auto preDir = rocketDirection;
		Vec3 dir(0, 0, 0);
		float rotateOfMap = 0.0f;
		if (angle >= -PI / 4 && angle < PI / 4) {
			rocketDirection = ROCKER_RIGHT;
			rocketRun = false;
			dir = Vec3(.0f, 90.0f, 0.0f);
			rotateOfMap = 90.0f;
		} else if (angle >= PI / 4 && angle < 3 * PI / 4) {
			rocketDirection = ROCKER_UP;
			dir = Vec3(.0f, 180.0f, 0.0f);
		} else if ((angle >= 3 * PI / 4 && angle <= PI) || (angle >= -PI&&angle < -3 * PI / 4)) {
			rocketDirection = ROCKER_LEFT;
			dir = Vec3(.0f, -90.0f, 0.0f);
			rotateOfMap = -90.0f;
			rocketRun = true;
		} else if (angle >= -3 * PI / 4 && angle < -PI / 4) {
			rocketDirection = ROCKER_DOWN;
			dir = Vec3(.0f, 0.0f, 0.0f);
			rotateOfMap = 180.0f;
		}

		if (preDir != rocketDirection) {
			Player *player = static_cast<Player*>(getParent()->getChildByTag(PLAYER_TAG));
			Minimap *minimap = static_cast<Minimap*>(getParent()->getChildByTag(MINIMAP_TAG));
			player->runAction(RotateTo::create(0.2f, dir));
			minimap->rotatePlayer(rotateOfMap);
		}
		/*if (preDir != rocketDirection)
		{
		camera->stopAllActions();
		camera->runAction(MoveTo::create(.2f, player->getPosition3D() - front + Vec3(0, 60, 0)));
		camera->lookAt(player->getPosition3D(), Vec3(0, 1, 0));
		}
		else
		{
		camera->setPosition3D(player->getPosition3D() - front + Vec3(0, 60, 0));
		camera->lookAt(player->getPosition3D(), Vec3(0, 1, 0));
		}*/
	};
	listener->onTouchEnded = [&](Touch *touch, Event *event) {
		if (!isCanMove) {
			return;
		}
		isCanMove = false;
		rocketDirection = ROCKER_CENTER;
		Sprite *r = static_cast<Sprite*>(getChildByTag(ROCKER_TAG));
		Sprite *rbg = static_cast<Sprite*>(getChildByTag(ROCKERBG_TAG));
		r->stopAllActions();
		r->runAction(MoveTo::create(.08f, rbg->getPosition()));
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Rocker::stopRocker() {

}

void Rocker::update(float delta) {
}

void Rocker::rockerInit(const std::string& rockerImageName, const std::string& rockerBGImageName, Point position) {
	Sprite *spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setPosition(position);
	spRockerBG->setVisible(false);
	addChild(spRockerBG, 0, ROCKERBG_TAG);

	Sprite *spRocker = Sprite::create(rockerImageName);
	spRocker->setPosition(position);
	spRocker->setVisible(false);
	addChild(spRocker, 1, ROCKER_TAG);

	rockerBGPosition = position;
	rockerBGR = (float)(spRockerBG->getContentSize().width * 0.5);//
	rocketDirection = ROCKER_CENTER;
}

float Rocker::getRad(Point pos1, Point pos2) {
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;

	float x = px2 - px1;
	float y = py1 - py2;
	float incline = (float)sqrt(pow(x, 2) + pow(y, 2));
	float cosAngle = x / incline;
	float rad = (float)acos(cosAngle);
	if (py2 < py1) {
		rad = -rad;
	}
	return rad;
}

void Rocker::onClickJumpBtn(Ref*, ui::TouchEventType type) {
	Player *player = static_cast<Player*>(getParent()->getChildByTag(PLAYER_TAG));
	switch (type) {
	case ui::TouchEventType::TOUCH_EVENT_ENDED:
		player->jump();
		break;
	default:break;
	}
}
