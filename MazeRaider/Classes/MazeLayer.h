#ifndef MAZELAYER_H_
#define MAZELAYER_H_

#include "cocos2d.h"
#include "GetPathNode.h"

USING_NS_CC;

class MazeLayer : public Layer {
public:

	MazeLayer(int m, int n, float percent);

	static MazeLayer *createMaze(int m, int n, float percent);

	bool init() override;

	struct Cell {
		int id, neighbor[4];
		bool visited;
	};
	struct Door {
		int cell1, cell2;
	};

	static const int WIDTH = 100, HEIGHT = 80;

	void initDoor();

	void initPath();

	void initCell();

	float m_percent() const {
		return mPercent;
	}

	int getRows() const;

	void drawMaze(Vec3 pos = Vec3(0, 0, 0));

	bool isCanPass(Sprite3D *sprite, Vec3 pos);

	std::vector<std::vector<std::vector<int>>> getWalls();

	float getLength();

	std::vector<std::vector<int>> getDoorsOfBlocks();


	void initProp();

	static int M, N;
private:
	Cell mMaze[WIDTH][HEIGHT];
	float mPercent;
	float mCellLength;
	std::vector<Door> mDoors;
	bool mFinished;
	GetPathNode *mPath;

	std::vector<Sprite3D*> mProps;

	Vector<Sprite3D *> mBlock[WIDTH][HEIGHT];    //the doors of a cell
	float mLen;
	int mBegin, mEnd;
	std::vector<std::vector<std::vector<int>>> mWalls;
	std::vector<std::vector<int>> mDoorsOfBlocks;

	void do_movement();
};

#endif