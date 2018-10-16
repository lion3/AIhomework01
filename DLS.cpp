#include "dls.h"
extern CNode nodes[nodesNum];
Node* cutoff;
Node* failure;
Node* RDLS(Node* node, Node* goal, int limit) {
	//printnd(*node);
	static int index = 0;
	if (NodeTest(node, goal)) {
		return node;
	}
	else if (limit == 0) {
		return cutoff;
	}
	else {
		bool cutoff_occurred = false;
		for (int i = 0; i < 4; i++) {
			if (valid_mov(node->pos, dir[i])) {
				//Node* child = new Node();
				Node* child = &nodes[index];
				index++;
				childNode(*child, *node, dir[i]);
				child->pre = node;
				Node* result = RDLS(child, goal, limit - 1);
				if (NodeTest(result, cutoff)) {
					cutoff_occurred = true;
				}
				else if (!NodeTest(result, failure)) {
					return result;
				}
			}
		}
		if (cutoff_occurred) {
			return cutoff;
		}
		else {
			return failure;
		}
	}
}
Node* DLS(Node* init, Node* goal,int limit) {
	cutoff = new Node();
	cutoff->key = 0;
	failure = new Node();
	failure->key = -1;
	return RDLS(init, goal, limit);
}
Node* IDS(Node* init, Node* goal) {
	int depth = 0;
	while (depth >= 0) {
		Node* result = DLS(init, goal, depth);
		if (!NodeTest(result, cutoff)) {
			return result;
		}
		depth++;
	}
}