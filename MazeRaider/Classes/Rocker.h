#ifndef ROCKER_H_
#define ROCKER_H_

#include "cocos2d.h"
#include "Constants.h"
#include <ui/UIButton.h>

USING_NS_CC;
using namespace ui;

class Rocker:public Layer
{
public:
	static Rocker *createRocker(const std::string &rockerImageName,const std::string &rockerBGImageName, Point position);


	bool init() override;
	void startRocker(bool isStopOther);

	void stopRocker();

	tagDirecton rocketDirection;
	tagDirecton preDirection;
	bool rocketRun;

	void onClickJumpBtn(Ref*, ui::TouchEventType type);

	CREATE_FUNC(Rocker);
	void update(float delta) override;

protected:
private:
	void rockerInit(const std::string &rockerImageName,const std::string &rockerBGImageName, Point position);
	bool isCanMove;
	float getRad(Point pos1, Point pos2);

	Point rockerBGPosition;
	float rockerBGR;

	//add a jump button
	ui::Button *mJumpBtn;
};
#endif