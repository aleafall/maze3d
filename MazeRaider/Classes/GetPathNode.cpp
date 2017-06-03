#include "GetPathNode.h"


GetPathNode::GetPathNode(int size) {
	mLen = size;
}

void GetPathNode::initProperties(int size) {
	for (int i = 0; i < size; ++i) {
		mFathers.push_back(i);
	}
}

class GetPathNode* GetPathNode::createPath(int size) {
	GetPathNode *path = new GetPathNode(size);
	if (path &&path->init()) {
		path->autorelease();
		return path;
	}
	CC_SAFE_DELETE(path);
	return nullptr;
}

bool GetPathNode::init() {
	if (!Node::init()) {
		return false;
	}
	initProperties(mLen);

	return true;
}

int GetPathNode::findFather(int id) {
	if (mFathers[id] == id) {
		return id;
	}
	int F = findFather(mFathers[id]);
	mFathers[id] = F;
	return F;
}

void GetPathNode::unionSet(int id1, int id2) {
	int f1 = findFather(id1);
	int f2 = findFather(id2);
	if (f1 != f2) {
		mFathers[f2] = f1;
	}
}
