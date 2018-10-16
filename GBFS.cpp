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
extern CNode nodes[nodesNum];
struct cmp_cost_small_first {
	bool operator ()(CNode* a, CNode* b) {
		return a->cost > b->cost;//最小值优先
	//	return a->cost+a->step > b->cost+b->step;//最小值优先
	}
};
struct cmp_cost_step_small_first {
	bool operator ()(CNode* a, CNode* b) {
		return a->cost+a->step > b->cost+b->step;//最小值优先
	}
};
int calculate_cost(CNode* n) {
	int cost = 0;
	//cost = NotInPlace(n->sta);
	cost = block_distance(n->sta);
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
int block_distance(int sta[]) {
	int ans = 0;
	for (int i = 0; i < StateNum; i++) {
		int x,y = 0;
		int tx,ty = 0;
		int t = sta[i];
		t = (t - 1) % 8;
		x = i % 3; y = i / 3; 
		tx = t % 3; ty = t / 3;
		ans += abs(tx - x) + abs(ty - y);
	}
	return ans;
}


CNode* GBFS_Failure;
static int index = 0;
CNode* GreedyBestFirstSearch(CNode* initState, CNode* goalState) {
	priority_queue<CNode*,vector<CNode*>, cmp_cost_small_first> frontier;
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
				CNode* child = &nodes[index];
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
