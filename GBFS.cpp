#include <iostream>
#include <queue>
#include "GBFS.h"
using namespace std;
//
//struct Node {
//	int sta[StateNum];
//	Node* pre;
//	int step;
//	int cost; //启发函数代价
//};
Node nodes[nodesNum];
struct cmp_small_first {
	bool operator ()(CNode* a, CNode* b) {
		return a->cost > b->cost;//最小值优先
	}
};
int calculate_cost(CNode* n) {
	int cost = 0;
	cost = NotInPlace(n->sta);
	return cost;
}

int NotInPlace(int sta[]) {
	int ans = 0;
	for (int i = 0; i < StateNum; i++) {
		if (sta[i] != i + 1) {
			ans++;
		}
	}
	return ans;
}

CNode cnodes[nodesNum];

CNode* GBFS_Failure;
static int index = 0;
CNode* GreedyBestFirstSearch(CNode* initState, CNode* goalState) {
	priority_queue<CNode*,vector<CNode*>, cmp_small_first> frontier;
	frontier.push(initState);
	initUsed(Used);
	while (true) {
		if (frontier.empty()) {
			printf("GBFS failure\n");
			return GBFS_Failure;
		}
		CNode* node = frontier.top();
		frontier.pop();
		if (NodeTest(node, goalState)) {
			printf("find goal\n");
			return node;
		}
		Used[mapkey(node)] = true;
		for (int i = 0; i < 4; i++) {
			if (valid_mov(node->pos, dir[i])) {
				CNode* child = &cnodes[index];
				index++;
				childNode(*child, *node, dir[i]);
				child->pre = node;
				child->cost = calculate_cost(child);
				if (Used[mapkey(child)] == false) {
					//not in frontier?
					frontier.push(child);
				}
			}
		}
	}
}

int mapkey(Node * n)
{
	int key = 0;
	for (int i = 0; i < StateNum - 1; i++) {
		key += n->sta[i];
		key *= 10;
	}
	key += n->sta[StateNum - 1];
	return key;
}

void initUsed(bool used[])
{
	for (int i = 0; i < UsedSize; i++) {
		used[i] = false;
	}
}
