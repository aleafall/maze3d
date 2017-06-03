#include "Minimap.h"
#include "MainLayer.h"

Minimap* Minimap::createMap() {
	Minimap *minimap = new Minimap();
	if (minimap &&minimap->init()) {
		minimap->autorelease();
		return minimap;
	}
	CC_SAFE_DELETE(minimap);
	return nullptr;
}

bool Minimap::init() {
	if (!Layer::init()) {
		return false;
	}
	mProportion = 0.18f;
	mMiniPlayer = Sprite::create("Minimap/miniPlayer.png");
	mMiniPlayer->setScale(.05f);
	addChild(mMiniPlayer);

	return true;
}

void Minimap::showMap() {
	Size size = Director::getInstance()->getVisibleSize();
	mDrawMap = DrawNode::create();
	addChild(mDrawMap);

	//draw lines
	MazeLayer *maze = static_cast<MazeLayer*>(getParent()->getChildByTag(MAZE_TAG));
	auto mazeWalls = maze->getWalls();
	float proportion = 0.18f;
	float lenOfMinimap = size.width*proportion / mazeWalls.size();
	float lenOfBorder = size.width*proportion;
	mPosXOfMinimap= size.width / 2 - size.width / 2 * proportion;
	mPosYOfMinimap= 10.0f;
	mMiniPlayer->setPosition(Point(mPosXOfMinimap, mPosYOfMinimap));
	float lineXEnd, lineYEnd;
	Color4F colorOfLine = Color4F(1.0, 0.0, 0, 1);
	//border
	Point border[4];
	border[0] = Point(mPosXOfMinimap, mPosYOfMinimap);
	border[1] = Point(mPosXOfMinimap + lenOfBorder, mPosYOfMinimap);
	border[2] = Point(mPosXOfMinimap + lenOfBorder, mPosYOfMinimap + lenOfBorder);
	border[3] = Point(mPosXOfMinimap, mPosYOfMinimap + lenOfBorder);

	mDrawMap->drawPolygon(border, 4, Color4F(1, 0, 0, 0), 1.0f, colorOfLine);

	for (auto i = 0; i < mazeWalls.size(); ++i) {
		for (auto j = 0; j < mazeWalls[0].size(); ++j) {
			float offset = (i*mazeWalls[0].size() + j + 1)*lenOfMinimap;
			float lineXBegin = mPosXOfMinimap + (i+1)*lenOfMinimap;
			float lineYBegin = mPosYOfMinimap + (j+1)*lenOfMinimap;
			for (auto k = 0; k < mazeWalls[i][j].size(); ++k) {
				if (mazeWalls[i][j][k] & 1) {
					lineXEnd = lineXBegin;
					lineYEnd = lineYBegin - lenOfMinimap;
				}
				else {
					lineXEnd = lineXBegin - lenOfMinimap;
					lineYEnd = lineYBegin;
				}
				mDrawMap->drawSegment(Point(lineXBegin, lineYBegin), Point(lineXEnd, lineYEnd), 1.0f, colorOfLine);
			}
		}
	}

}

void Minimap::updatePosition(Point pos, float totalLen) {
	Size size = Director::getInstance()->getVisibleSize();
	float x = size.width*mProportion / totalLen;
	mMiniPlayer->setPosition(Point(mPosXOfMinimap, mPosYOfMinimap) + Point(pos.x*x,pos.y*x));
}

void Minimap::rotatePlayer(float rotate) {
	mMiniPlayer->setRotation(rotate);
}

Sprite* Minimap::getPlayer()
{
	return mMiniPlayer;
}
