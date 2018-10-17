#pragma once
#ifndef Search_H
#define Search_H
#include <queue>
#include <map>
using namespace std;
#include "Support.h"
struct SNode {
	int sta[StateNum];
	SNode* pre;
	int key;
	int step;
	int cost;
	SNode() {
		pre = NULL;
		step = 0;
		cost = 0;
	}
};
SNode* initSNode(int state[]);

class Search {
public:
	static SNode* nodes;
	static SNode* Failure;
	static SNode* Cutoff;
	static int dir[4];
	static bool used[nodesNum];
	map<int, int> usedmap;
	SNode* initNode;
	SNode* targetNode;
	SNode* resultNode;
	static int calculate_cost(SNode* n, int(*cost_func)(SNode* n));
	static void initUsed();
	void printndformat(SNode n);
	void print_result();
	static int NotInPlace(SNode* n);
	static int block_distance(SNode* n);
	static int find_pos(int sta[]);
	void childNode(SNode* childNode, SNode* parentNode, int dir);
	void SearchResult(SNode* initNode, SNode* targetNode);
	static bool valid_move(SNode* a, int dir);
	static bool equal(SNode* a, SNode* b);
};
class GraphSearch :public Search {
public:
	void SearchResult(SNode* initNode, SNode* targetNode);

};
class GreedySearch : public GraphSearch {
public:
	void SearchResult(SNode* initNode, SNode* targetNode);
	struct cmp_cost {
		bool operator ()(SNode* a, SNode* b) {
			return a->cost > b->cost;//最小值优先
		}
	};
};
class AstarSearch : public GraphSearch {
public:
	void SearchResult(SNode* initNode, SNode* targetNode);
	struct cmp_cost {
		bool operator ()(SNode* a, SNode* b) {
			return a->cost + a->step > b->cost + b->step;//最小值优先
		}
	};
};
class IterativeDepthSearch :public Search {
public:
	int index;
	void SearchResult(SNode* initNode, SNode* targetNode);
	SNode* DLS(SNode* init, SNode* goal, int limit) {
		index = 0;
		initUsed();
		nodes[index] = *init;
		index++;
		usedmap.clear();
		usedmap.insert(map<int, int>::value_type(init->key, index));
		return RDLS(init, goal, limit);
	}
	SNode* RDLS(SNode* node, SNode* goal, int limit) {
		if (equal(node, goal)) {
			printf("find goal\n");
			return node;
		}
		else if (limit == 0) {
			return Cutoff;
		}
		else {
			used[usedmap.find(node->key)->second] = true;
			bool cutoff_occurred = false;
			for (int i = 0; i < 4; i++) {
				if (valid_move(node, dir[i])) {
					SNode* child = &nodes[index];
					index++;
					childNode(child, node, dir[i]);
					usedmap.insert(map<int, int>::value_type(child->key, index - 1));
					if (used[usedmap.find(child->key)->second] == false) {
						SNode* result = RDLS(child, goal, limit - 1);
						if (equal(result, Cutoff)) {
							cutoff_occurred = true;
						}
						else if (!equal(result, Failure)) {
							return result;
						}
					}
				}
			}
			if (cutoff_occurred) {
				return Cutoff;
			}
			else {
				return Failure;
			}
		}
	}

};
#endif // !Search_H

