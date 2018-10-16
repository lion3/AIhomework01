#pragma once
#ifndef Search_H
#define Search_H
#include "Support.h"
struct SNode {
	int sta[StateNum];
	bool used;
	SNode* pre;
	SNode() {
		used = false;
		pre = NULL;
	}
};
class Search {
public:
	SNode* nodes;
	SNode* initNode;
	SNode* targetNode;
	SNode* resultNode;
	void SearchResult(SNode* initNode, SNode* targetNode);
};
class GraphSearch :public Search {
public:
	void SearchResult(SNode* initNode, SNode* targetNode);
};
#endif // !Search_H

