#include "BFS.h"
using namespace std;
int d[] = { 1,3,-1,-3 };
bool used[1000000000] = { false };
Node* BFSfailure;
Node BFSstates[400000];
static int index = 0;
void initused() {
	for (int i = 0; i < 1000000000; i++) {
		used[i] = false;
	}
}
Node* BFS(Node* initNode, Node* targetNode) {
	index = 0;
	initused();
	if (NodeTest(initNode, targetNode)) {
		return initNode;
	}
	Node* node;
	queue<Node*> q;
	q.push(initNode);
	while (true) {
		if (q.empty()) {
			printf("BFS failure");
			return BFSfailure;
		}
		node = q.front();
		q.pop();
		used[node->key] = true;
		for (int i = 0; i < 4; i++) {
			if (valid_mov(node->pos, d[i])) {
				//Node* child = new Node();
				Node* child = &BFSstates[index];
				index++;
				childNode(*child, *node, d[i]);
				child->pre = node;
				if (used[child->key]==false) {
					if (NodeTest(child, targetNode)) {
						printf("find target");
						return child;
					}
					q.push(child);
				}
			}
		}
	}
	
}
