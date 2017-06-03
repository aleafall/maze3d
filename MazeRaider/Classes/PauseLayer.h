//
// Created by aleafall on 17-3-26.
//

#ifndef MAZERAIDER_PAUSELAYER_H
#define MAZERAIDER_PAUSELAYER_H

#include <ui/UIButton.h>
#include "cocos2d.h"

USING_NS_CC;


class PauseLayer : public Layer {
private:
	Sprite *mBackground;
	ui::Button *mResume;
	ui::Button *mBegin;
public:
	static Scene *createScene(const std::string &filePath);

	bool init() override;

	CREATE_FUNC(PauseLayer);
};


#endif //MAZERAIDER_PAUSELAYER_H
