#include "MazeLayer.h"
#include "Constants.h"
#include "Player.h"

using namespace std;

int MazeLayer::M=10;
int MazeLayer::N=10;
MazeLayer::MazeLayer(int m, int n, float percent) {
	M = m, N = n, mPercent = percent;
	mBegin = 0, mEnd = m * n - 1;
	mFinished = 0;
}

MazeLayer *MazeLayer::createMaze(int m, int n, float percent) {
	MazeLayer *maze = new MazeLayer(m, n, percent);
	if (maze && maze->init()) {
		maze->autorelease();
		return maze;
	}
	CC_SAFE_DELETE(maze);
	return nullptr;
}

bool MazeLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	mPath = GetPathNode::createPath(M * N);
	mWalls = vector<vector<vector<int>>>(M, vector<vector<int>>(N, vector<int>()));
	mCellLength = 2.0f;        //init
	addChild(mPath);
	initDoor();
	initPath();

	mDoorsOfBlocks = vector<vector<int>>(M, vector<int>(N, 0));
	return true;
}

void MazeLayer::initDoor() {
	int sizeOfDoor = M * (N - 1) + (M - 1) * N;
	int index = 0;
	mDoors.clear();
	mDoors.resize(sizeOfDoor);
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			mMaze[i][j].id = i * N + j;
			mMaze[i][j].visited = 0;
			for (int k = 0; k < 4; ++k) {
				mMaze[i][j].neighbor[k] = -1;
			}
		}
	}
	int idOfDoor = 0;
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N - 1; ++j) {
			mMaze[i][j].neighbor[1] = index + 1;
			mMaze[i][j + 1].neighbor[3] = index;
			mDoors[idOfDoor].cell1 = index;
			mDoors[idOfDoor].cell2 = ++index;
			++idOfDoor;
		}
		++index;
	}
	for (int i = 0; i < M - 1; ++i) {
		for (int j = 0; j < N; ++j) {
			mMaze[i][j].neighbor[2] = (i + 1) * N + j;
			mMaze[i + 1][j].neighbor[0] = i * N + j;
			mDoors[idOfDoor].cell1 = i * N + j;
			mDoors[idOfDoor].cell2 = (i + 1) * N + j;
			++idOfDoor;
		}
	}
}

void MazeLayer::initPath() {
	int sizeOfDoor = static_cast<int>(mDoors.size());
	time_t t;
	srand((unsigned) time(&t));
	while (mPath->findFather(mBegin) != mPath->findFather(mEnd)) {
		int size = static_cast<int>(mDoors.size());
		int randDoor = rand() % size;
		auto iter = mDoors.begin();
		iter += randDoor;
		int id1 = mPath->findFather(iter->cell1);
		int id2 = mPath->findFather(iter->cell2);
		if (id1 != id2) {
			mPath->unionSet(id1, id2);
			mDoors.erase(iter);
		}
	}
	while (1.0f * mDoors.size() / sizeOfDoor > mPercent) {
		auto iter = mDoors.begin();
		int randDoor = static_cast<int>(rand() % mDoors.size());
		iter += randDoor;
		mDoors.erase(iter);
	}
}

void MazeLayer::initCell() {
}

void MazeLayer::do_movement() {
}

void MazeLayer::drawMaze(Vec3 pos) {
	const int rows = 100, cols = 100;
	std::string filePathFront = "map/qiang3.c3b";
	std::string filePathBack = "map/qiang2.c3b";
	std::vector<int> walls[rows][cols];

	for (auto i = 0; i < mDoors.size(); ++i) {
		int id1 = mDoors[i].cell1;
		int id2 = mDoors[i].cell2;
		int x = id1 / N, z = id1 % N;
		if (id1 == id2 - 1) {        //right wall of the cell
			walls[x][z].push_back(2);
			mWalls[x][z].push_back(2);
		} else {                    //side or back wall of the cell
			walls[x][z].push_back(1);
			mWalls[x][z].push_back(1);
		}
	}
	Sprite3D *example = Sprite3D::create(filePathFront);
	float len = example->getContentSize().width;
	mCellLength = len;
	mLen = len * M;
	Vec3 cellPos[rows][cols];
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			cellPos[i][j] = {len * i, 0.0f, -len * j};
		}
	}
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			Sprite3D *wall;
			for (int k = 0; k < walls[i][j].size(); ++k) {
				if (walls[i][j][k] & 1) {
					wall = Sprite3D::create(filePathBack);
					wall->setPosition3D(cellPos[i][j] + Vec3(len, 0, -len / 2));

					mBlock[i][j].pushBack(wall);
					mBlock[i + 1][j].pushBack(wall);
				} else {
					wall = Sprite3D::create(filePathFront);
					wall->setPosition3D(cellPos[i][j] + Vec3(len / 2, 0, -len));

					mBlock[i][j].pushBack(wall);
					mBlock[i][j + 1].pushBack(wall);
				}
				wall->setTexture("map/forge_oven2.tga");

				addChild(wall);
			}
			Sprite3D *frontEdge, *backEdge;

			if (j == 0 ) {
				//front edge
				frontEdge = Sprite3D::create(filePathFront);
				frontEdge->setPosition3D(cellPos[i][j] + Vec3(len / 2, 0, 0));
				frontEdge->setTexture("map/forge_oven2.tga");

				addChild(frontEdge);
				mBlock[i][j].pushBack(frontEdge);
			} else if (j == N - 1 && i != M - 1) {
				//back edge
				frontEdge = Sprite3D::create(filePathFront);
				frontEdge->setPosition3D(cellPos[i][j] + Vec3(len / 2, 0, -len));
				frontEdge->setTexture("map/forge_oven2.tga");
				addChild(frontEdge);
				mBlock[i][j].pushBack(frontEdge);

			}

			if (i == 0) {
				//left edge
				backEdge = Sprite3D::create(filePathBack);
				backEdge->setPosition3D(cellPos[i][j] + Vec3(0, 0, -len / 2));
				backEdge->setTexture("map/forge_oven2.tga");
				addChild(backEdge);
				mBlock[i][j].pushBack(backEdge);
			} else if (i == M - 1) {
				//right edge
				backEdge = Sprite3D::create(filePathBack);
				backEdge->setPosition3D(cellPos[i][j] + Vec3(len, 0, -len / 2));
				backEdge->setTexture("map/forge_oven2.tga");
				addChild(backEdge);
				mBlock[i][j].pushBack(backEdge);
			}
		}
	}
	//door's size of each cell
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			mDoorsOfBlocks[i][j] = (int) mBlock[i][j].size();
		}
	}

	//ground
	Sprite3D *ground = Sprite3D::create(filePathBack);
	ground->setScaleX(3*M);
	ground->setScaleZ(3*M);
	ground->setRotation3D(Vec3(0, 0, 0));
	ground->setPosition3D(Vec3(ground->getContentSize().width * M, -ground->getContentSize().width-3, -ground->getContentSize().width * M));
	ground->setTexture("map/muban.png");
	addChild(ground);
}

bool MazeLayer::isCanPass(Sprite3D *sprite, Vec3 pos) {
	int cellX = static_cast<int>(pos.x / mCellLength), cellZ = -static_cast<int>(pos.z / mCellLength);
	if (cellX < 0 || cellX >= M || cellZ < 0 || cellZ >= N) {
		return true;
	}
	Vec3 minVec = sprite->getAABB()._min;
	Vec3 maxVec = sprite->getAABB()._max;
	Vec3 nowPos = (maxVec + minVec) / 2;
	minVec += pos - nowPos;
	maxVec += pos - nowPos;

	minVec.y = sprite->getAABB()._min.y;
	maxVec.y = sprite->getAABB()._max.y;

	AABB aabb = AABB(minVec, maxVec);
	OBB obb = OBB(aabb);
	for (auto door : mBlock[cellX][cellZ]) {
		/*if (door&&door->getAABB().containPoint(pos)) {
			return false;
		}*/
		/*if (door && door->getAABB().intersects(aabb)) {
			return false;
		}*/
		if (door) {
			OBB obb1 = OBB(door->getAABB());
			if (obb.intersects(obb1)) {
				return 0;
			}
		}
	}

	//prop
	for (int i = 0; i < mProps.size();++i)
	{
		if (mProps[i]->getTag()!=100&& mProps[i]->getAABB().intersects(aabb))
		{
			mProps[i]->setVisible(false);
			mProps[i]->setTag(100);
			Player *player = static_cast<Player*>(this->getParent()->getChildByTag(PLAYER_TAG));
			player->setHeight(player->getHeight() + 10);
			player->jump();
		}
	}
	return true;
}

std::vector<std::vector<std::vector<int>>> MazeLayer::getWalls() {
	return mWalls;
}

float MazeLayer::getLength() {
	return mLen;
}

std::vector<std::vector<int>> MazeLayer::getDoorsOfBlocks() {
	return mDoorsOfBlocks;
}

int MazeLayer::getRows() const {
	return M;
}


void MazeLayer::initProp()
{
	const int num = 3;
	const int tt = 405;
	int hashTable[tt] = { 0 };
	int len = getLength() / M;
	srand((unsigned)time(NULL));
	for (int i = 0; i < num;++i)
	{
		int index = (int)rand() % (M*N);
		while (hashTable[index])
		{
			index = (int)rand() % tt;
		}
		hashTable[index] = 1;
		Vec3 pos(index / M*len + len*0.5, 3, -index%M*len - len*0.5); 
		PropType type = (PropType)(rand() % 2);
		std::string filePath = "prop/prop" + std::to_string((int)type) + "/prop" + std::to_string((int)type);

		Sprite3D *prop = Sprite3D::create(filePath+".c3b");
		prop->setTexture(filePath + ".png");
		prop->setTag(type);
		prop->setPosition3D(pos);
		if (type!=GOLD_COIN)
		{
			prop->setScale(10.0f);
		}
		else
		{
			prop->setScale(0.1f);
			prop->setRotation3D(Vec3(0, 0, 90));
		}
		addChild(prop);

		mProps.push_back(prop);

	}
	Sprite3D *jiangbei = Sprite3D::create("jiangbei(1).c3b");
	jiangbei->setTexture("gold.jpg");
	jiangbei->setPosition3D(Vec3((M-1)*len+len*0.5f, 5, -(M-1)*len-len*0.5f));
	jiangbei->setScale(1);
	addChild(jiangbei);
}