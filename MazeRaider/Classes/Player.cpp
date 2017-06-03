#include "Player.h"
#include "MainLayer.h"
#include "Minimap.h"

Player *Player::createPlayer(const std::string &filePath) {
	Player *player = new Player();
	if (player->init() && player->initWithFile(filePath)) {
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

bool Player::init() {
	if (!Sprite3D::init()) {
		return false;
	}
	mIsJumping = 0;
	mJumpHeight = 25;
	return true;
}

void Player::updatePos() {
	if (mIsJumping) {
		return;
	}
	float x = 0, z = 0;
	Rocker *rocker = getRocker();

	switch (rocker->rocketDirection) {
		case ROCKER_CENTER:
			return;
		case ROCKER_UP:
			z = -1;
			break;
		case ROCKER_DOWN:
			z = 1;
			break;
		case ROCKER_LEFT:
			x = -1;
			break;
		case ROCKER_RIGHT:
			x = 1;
			break;
		default:
			break;
	}
//	Layer *cameraLayer = static_cast<Layer*>(getParent()->getChildByTag(CAMERA_TAG));
//	Camera *camera = (Camera *) cameraLayer->getChildByTag(CAMERA_TAG);
	Camera *camera = static_cast<Camera *>(getParent()->getChildByTag(CAMERA_TAG));
	Sprite3D *map = static_cast<Sprite3D *>(getParent()->getChildByTag(MAP_TAG));
	Label *posLabel = static_cast<Label *>(getParent()->getChildByTag(POS_TAG));
	MazeLayer *maze = static_cast<MazeLayer *>(getParent()->getChildByTag(MAZE_TAG));
	Minimap *minimap = static_cast<Minimap *>(getParent()->getChildByTag(MINIMAP_TAG));

	Vec3 newPos = this->getPosition3D() + Vec3(x / 2, 0, z / 2);
	if (maze->isCanPass(this, newPos)) {
		this->setPosition3D(newPos);
		minimap->updatePosition(Point(newPos.x, -newPos.z), maze->getLength());
//		CCLOG("player's position %.1f %.1f %.1f", getPosition3D().x, getPosition3D().y, getPosition3D().z);
		camera->setPosition3D(this->getPosition3D() + Vec3(0, cameraY, cameraZ));

		int x = getPosition3D().x, y = getPosition3D().y, z = getPosition3D().z;

		std::string pos =
				"pos " + StringUtils::toString(x) + " " + StringUtils::toString(y) + " " + StringUtils::toString(z);
		posLabel->setString(pos);

		//prop 

	}
	/*if ((!this->getAABB().intersects(map->getAABB()) && (!this->getAABB().intersects(outer->getAABB())))) {
		this->setPosition3D(Vec3(this->getPosition3D()+Vec3(x,0,z)));
		camera->setPosition3D(this->getPosition3D() + Vec3(0, 20, 20));
		}*/

	//check if enter the final block
	float mCellLength = maze->getLength() / maze->getRows();
	int cellX = static_cast<int>(newPos.x / mCellLength), cellZ = -static_cast<int>(newPos.z / mCellLength);
	if (cellX == maze->getRows() - 1 && cellZ == maze->getRows() - 1) {
		MainLayer *mainLayer = static_cast<MainLayer *>(getParent());
//		mainLayer->setGameOver();
	}
}

void Player::jump() {
	if (mIsJumping) {
		return;
	}

/*
	Vec3 pos = getPosition3D();
	if (pos.y < 100) {
		setPosition3D(pos + Vec3(0, 30, 0));
	} else {
		setPosition3D(Vec3(pos.x, 0, pos.z));
	}*/

	Camera *camera = static_cast<Camera *>(getParent()->getChildByTag(CAMERA_TAG));
//	Layer *cameraLayer = static_cast<Layer*>(getParent()->getChildByTag(CAMERA_TAG));
//	Camera *camera = (Camera *) cameraLayer->getChildByTag(CAMERA_TAG);
//	camera->setPosition3D(this->getPosition3D() + Vec3(0, cameraY, cameraZ));
	mIsJumping = 1;
	auto act1 = JumpBy::create(2.0f, Point::ZERO, mJumpHeight, 1);
	auto func = CallFunc::create([&]() {
		mIsJumping = 0;
	});
	auto jumpAction = Sequence::create(act1, func, NULL);
	auto act2 = act1->clone();
	runAction(jumpAction);
	camera->runAction(act2);
}

void Player::setHeight(float height)
{
	if (height<100)
	{
		this->mJumpHeight = height;
	}
}
float Player::getHeight() const
{
	return mJumpHeight;
}
