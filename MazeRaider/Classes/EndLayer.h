//
// Created by aleafall on 17-3-27.
//

#ifndef MAZERAIDER_ENDLAYER_H
#define MAZERAIDER_ENDLAYER_H

#include <ui/UIButton.h>
#include "cocos2d.h"

USING_NS_CC;


class EndLayer : public Layer {
public:
	static Scene *createScene(int score,int timeCount,const std::string &filePath);

	EndLayer(int score, int timeCount, const std::string &filePath);

	static EndLayer *create(int score, int timeCount, const std::string &filePath);

	bool init() override;

private:
	Sprite *mBackground;

	Sprite *mBoard;
	Sprite *mStatus;
	Sprite *mScoreShow;
	Sprite *mTimeShow;
	std::vector<int> mPreTime;

	std::vector<int> mPreScore;

	ui::Button *mReplay,*mExit;

	int mTime, mScore;

	Label *mTimeLabel,*mScoreLabel;

};


#endif //MAZERAIDER_ENDLAYER_H
