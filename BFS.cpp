#include "BFS.h"
using namespace std;
Node* BFSfailure;
static int index = 0;
extern bool Used[UsedSize];
extern CNode nodes[nodesNum];
Node* BFS(Node* initNode, Node* targetNode) {
	index = 0;
	initUsed(Used);
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
		Used[node->key] = true;
		for (int i = 0; i < 4; i++) {
			if (valid_mov(node->pos, dir[i])) {
				//Node* child = new Node();
				Node* child = &nodes[index];
				index++;
				childNode(*child, *node, dir[i]);
				child->pre = node;
				if (Used[child->key]==false) {
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
