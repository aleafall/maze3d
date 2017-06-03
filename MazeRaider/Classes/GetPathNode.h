#ifndef GETPATH_H_
#define GETPATH_H_

#include "cocos2d.h"

USING_NS_CC;

class GetPathNode :public Node {
public:

	GetPathNode(int size);

	static GetPathNode* createPath(int size);
	bool init() override;
	void initProperties(int size);
	int findFather(int id);

	void unionSet(int id1, int id2);

protected:
private:
	std::vector<int> mFathers;
	int mLen;
};
#endif