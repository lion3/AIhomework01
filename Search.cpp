
#include "Search.h"
void GreedySearch::SearchResult(SNode* initNode, SNode* targetNode) {
	SNode* result;
	int index = 0;
	printf("\nGreedySearch Result:\n");
	//
	priority_queue<SNode*, vector<SNode*>, cmp_cost> frontier;
	frontier.push(initNode);
	nodes[index] = *initNode;
	initUsed();
	usedmap.clear();
	usedmap.insert(map<int, int>::value_type(initNode->key, index));
	index++;
	while (true) {
		if (frontier.empty()) {
			printf("search failure\n");
			result = Failure;
			break;
		}
		SNode* node = frontier.top();
		frontier.pop();
		if (equal(node, targetNode)) {
			printf("find goal\n");
			result = node;
			break;
		}
		used[usedmap.find(node->key)->second] = true;
		for (int i = 0; i < 4; i++) {
			if (valid_move(node, dir[i])) {
				SNode* child = &nodes[index];
				index++;
				childNode(child, node, dir[i]);
				usedmap.insert(map<int, int>::value_type(child->key, index - 1));
				child->cost = calculate_cost(child, block_distance);
				if (used[usedmap.find(child->key)->second] == false) {
					//not in frontier?
					frontier.push(child);
				}
			}
		}
	}
	resultNode = result;
}

void AstarSearch::SearchResult(SNode* initNode, SNode* targetNode) {
	SNode* result;
	int index = 0;
	printf("\nAstarSearch Result:\n");
	//
	priority_queue<SNode*, vector<SNode*>, cmp_cost> frontier;
	frontier.push(initNode);
	nodes[index] = *initNode;
	initUsed();
	usedmap.clear();
	usedmap.insert(map<int, int>::value_type(initNode->key, index));
	index++;
	while (true) {
		if (frontier.empty()) {
			printf("search failure\n");
			result = Failure;
			break;
		}
		SNode* node = frontier.top();
		frontier.pop();
		if (equal(node, targetNode)) {
			printf("find goal\n");
			result = node;
			break;
		}
		used[usedmap.find(node->key)->second] = true;
		for (int i = 0; i < 4; i++) {
			if (valid_move(node, dir[i])) {
				SNode* child = &nodes[index];
				index++;
				childNode(child, node, dir[i]);
				usedmap.insert(map<int, int>::value_type(child->key, index-1));
				child->cost = calculate_cost(child, block_distance);
				if (used[usedmap.find(child->key)->second]== false) {
					//not in frontier?
					frontier.push(child);
				}
			}
		}
	}
	resultNode = result;
}



int Search::calculate_cost(SNode * n, int(*cost_func)(SNode *n))
{
	int cost = 0;
	cost = cost_func(n);
	return cost;
}

void Search::initUsed()
{
	for (int i = 0; i < nodesNum; i++) {
		used[i] = false;
	}
}

void Search::printndformat(SNode n)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", n.sta[i * 3 + j]);
		}
		printf("\n");
	}
}

void Search::print_result()
{
	SNode n = *resultNode;
	int t = n.step;
	SNode temp = n;
	while (t >= 0) {
		printf("%d\n", t);
		printndformat(temp);
		if (temp.pre != NULL) {
			temp = *temp.pre;
		}
		t = t - 1;
	}
}

int Search::NotInPlace(SNode * n)
{
	int ans = 0;
	for (int i = 0; i < StateNum; i++) {
		if (n->sta[i] != i + 1) {
			ans++;
		}
	}
	return ans;
}

int Search::block_distance(SNode * n)
{
	int ans = 0;
	for (int i = 0; i < StateNum; i++) {
		int x, y = 0;
		int tx, ty = 0;
		int t = n->sta[i];
		t = (t - 1) % 8;
		x = i % 3; y = i / 3;
		tx = t % 3; ty = t / 3;
		ans += abs(tx - x) + abs(ty - y);
	}
	return ans;
}

int Search::find_pos(int sta[])
{
	int pos = -1;
	for (int i = 0; i < StateNum; i++) {
		if (sta[i] == 0) {
			pos = i;
			break;
		}
	}
	return pos;
}

void Search::childNode(SNode* n, SNode* t, int dir)
{
	int tpos = find_pos(t->sta);
	int npos = find_pos(n->sta);
	npos = tpos + dir;
	for (int i = 0; i < StateNum; i++) {
		n->sta[i] = t->sta[i];
	}
	int temp;
	temp = n->sta[npos];
	n->sta[npos] = n->sta[tpos];
	n->sta[tpos] = temp;
	n->step = t->step + 1;
	n->pre = t;
	n->key = 0;
	for (int i = 0; i < StateNum - 1; i++) {
		n->key += n->sta[i];
		n->key *= 10;
	}
	n->key += n->sta[StateNum - 1];
}

bool Search::valid_move(SNode * a, int dir)
{
	int pos = find_pos(a->sta);
	bool res = true;
	if ((pos < 3) && (dir == -3) ||
		(pos > 5) && (dir == 3) ||
		((pos + 1) % 3 == 0) && (dir == 1) ||
		(pos % 3 == 0) && (dir == -1)
		) {
		res = false;
	}
	return res;
}

bool Search::equal(SNode * a, SNode * b)
{
	bool res = true;
	for (int i = 0; i < StateNum; i++) {
		if (a->sta[i] != b->sta[i]) {
			res = false;
			break;
		}
	}
	return res;
}

SNode * initSNode(int state[])
{
	
		SNode* node = new SNode();
		for (int i = 0; i < StateNum; i++) {
			node->sta[i] = state[i];
		}
		node->key = 0;
		for (int i = 0; i < StateNum - 1; i++) {
			node->key += node->sta[i];
			node->key *= 10;
		}
		node->key += node->sta[StateNum - 1];
		return node;
	
}



void IterativeDepthSearch::SearchResult(SNode * initNode, SNode * targetNode)
{
	{
		printf("\nIterativeDepthSearch Result:\n");
		int depth = 0;
		index = 0;
		while (depth >= 0) {
			SNode* result = DLS(initNode, targetNode, depth);
			if (!equal(result, Cutoff)) {
				resultNode = result;
				break;
			}
			depth++;
		}
	}
}
