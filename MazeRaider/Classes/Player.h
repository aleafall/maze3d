#ifndef PALYER_H_
#define PALYER_H_

#include "cocos2d.h"
#include "Rocker.h"

USING_NS_CC;

class Player : public Sprite3D {
public:
	static Player *createPlayer(const std::string &filePath);

	bool init() override;

	CREATE_FUNC(Player);

	Rocker *getRocker() const {
		return mRocker;
	}

	void setRocker(Rocker *rocker) {
		mRocker = rocker;
	}

	void jump();

	void updatePos();

	void setHeight(float height);
	float getHeight() const;
protected:
private:
	bool mIsJumping;
	Rocker *mRocker;
	float mSpeed;
	float mJumpHeight;
};

#endif