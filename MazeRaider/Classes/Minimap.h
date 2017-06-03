#ifndef MINIMAP_H_
#define MINIMAP_H_

#include "cocos2d.h"

USING_NS_CC;

class Minimap:public Layer
{
public:
	static Minimap *createMap();

	bool init() override;


	void showMap();

	void updatePosition(Point pos, float totalLen);

	void rotatePlayer(float rotate);

	Sprite *getPlayer();
	CREATE_FUNC(Minimap);
protected:
private:
	Sprite *mBackground;
	Sprite *mMiniPlayer;
	DrawNode *mDrawMap;
	float mPosXOfMinimap, mPosYOfMinimap;
	float mProportion;
};
#endif