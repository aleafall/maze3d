#ifndef MAINLAYER_H_
#define MAINLAYER_H_

#include "cocos2d.h"
#include "Player.h"
#include "Rocker.h"
#include "MazeLayer.h"
#include "MainLayer.h"
#include "PauseLayer.h"


USING_NS_CC;

class MainLayer :public Layer {
public:
	static Scene *createScene();
	bool init() override;
	CREATE_FUNC(MainLayer);

	void setScore();

	void setGameOver();

	void update(float delta) override;

	void setRange(int m, int n,float com);
	void initMaze();
protected:
private:
	void setTime();

	Sprite *mGround;
	Player *mPlayer;
	Sprite3D *mOuter;
	Rocker *mRocker;
	Sprite3D *mMap;
	Camera *mCamera;
	Skybox *skyBox;

	MazeLayer *mMaze;

	Label *mPos;
	Label *mTimeShow;
	int hh,mm,ss;

	float mCountPerFrame;
	Label *mScoreShow;
	int mScores;

	Button *mPause;

	Layer *mCameraLayer;

	bool mGameOver;

	int M, N;
	float complex;
};
#endif