#include <iostream>
#include <queue>
#include "GBFS.h"
using namespace std;
#define StateNum 9
#define nodesNum 400000
#define UsedSize 100000000
struct Node {
	int sta[StateNum];
	Node* pre;
	int step;
	int cost; //启发函数代价
};
int calculate_cost(Node* n) {
	int cost = 0;
	return cost;
}
bool Used[UsedSize];
Node nodes[nodesNum];
int dir[4] = { 1,3,-1,-3 };
static int index = 0;
Node* GreedyBestFirstSearch(Node* initState, Node* goalState) {
	priority_queue<Node*> frontier;
	frontier.push(initState);
	initUsed();
	while (true) {
		if (frontier.empty()) {
			Node* GBFS_Failure;
			return GBFS_Failure;
		}
		Node* node = frontier.top();
		frontier.pop();
		if (NodeTest(node, goalState)) {
			return node;
		}
		Used[mapkey(node)] = true;
		for (int i = 0; i < 4; i++) {
			if (valid_move(node, dir[i])) {
				Node* child = &nodes[index];
				index++;
				childNode(child, node, dir[i]);
				if (Used[mapkey(child)] == false) {
					//not in frontier?
					frontier.push(child);
				}
			}
		}
	}
}