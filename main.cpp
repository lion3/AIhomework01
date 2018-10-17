#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "support.h"
#include "BFS.h"
#include "dls.h"
#include "GBFS.h"
#include "Search.h"
using namespace std;
//int initvalue[] = { 1,2,3,0,4,6,7,5,8 };


struct A {
	int val;
	int cost;
	bool operator < (const A &a) const {
		return cost > a.cost;//最小值优先
	}
};
struct cmp_small_first1{
	bool operator ()(A *a, A *b) {
		return a->cost > b->cost;//最小值优先
	}
};
void test_pri_q() {
	int vlist[10] = {3,7,8,9,2,1,4,5,6,0};
	int clist[10] = {0,1,2,2,4,5,6,6,6,9};
	A a[10];
	priority_queue<A> q;
	priority_queue<A*, vector<A*>, cmp_small_first1> q1;
	for (int i = 0; i < 10; i++) {
		a[i].cost = clist[i];
		a[i].val = vlist[i];
		q.push(a[i]);
		q1.push(&a[i]);
	}
	printf("q:\n");
	while (!q.empty()) {
		A t = q.top();
		q.pop();
		printf("val %d cost %d\n", t.val, t.cost);
	}
	printf("q1:\n");
	while (!q1.empty()) {
		A* t = q1.top();
		q1.pop();
		printf("val %d cost %d\n", t->val, t->cost);
	}
}
//int initvalue[] = { 6,5,7,1,2,8,0,4,3 };
int initvalue[] = { 1,2,3,
					4,0,6,
					7,5,8 };
int targetvalue[] = { 1,2,3,
					  4,5,6,
					  7,8,0 };
int failurenum[] = { -1,-1,-1,-1,-1,-1,-1,-1,-1 };
int cutoffnum[] = { 0,0,0,0,0,0,0,0,0 };
SNode* Search::nodes = new SNode[nodesNum];
SNode* Search::Failure = initSNode(failurenum);
SNode* Search::Cutoff = initSNode(cutoffnum);
int Search::dir[4] = { 1,3,-1,-3 };
bool Search::used[nodesNum] = { false };
int main() {
	AstarSearch astar_search;
	GreedySearch greedy_search;
	IterativeDepthSearch ids_search;
	SNode* target;
	target = initSNode(targetvalue);

	vector<int*> states;
	for (int i = 0; i < 20; i++) {
		int* state = generateRandomly();
		if (check_inverse(state)) {
			states.push_back(state);
		}
	}
	int statesize = states.size();
	printf("generate %d\n", states.size());
	double t_Astar = 0, t_greedy = 0, t_ids = 0, dur = 0;
	clock_t start, end;
	for (int i = 0; i < states.size(); i++)
	{
		printf("test %d\n",i);
		SNode* tempinit = initSNode(states[i]);
		start = clock();
		astar_search.SearchResult(tempinit,target);
		end = clock();
		dur = (double)(end - start);
		t_Astar += dur;
		//printf("%lf\n", dur);
		//astar_search.print_result();
		start = clock();
		greedy_search.SearchResult(tempinit, target);
		end = clock();
		dur = (double)(end - start);
		t_greedy += dur;
		//printf("%lf\n", dur);
		//greedy_search.print_result();
		start = clock();
		ids_search.SearchResult(tempinit, target);
		//ids_search.print_result();
		end = clock();
		dur = (double)(end - start);
		t_ids += dur;
		//printf("%lf\n", dur);
	}

	printf("Average Time\nAstar:%lf\nGreedy:%lf\nIDS:%lf\n", t_Astar/statesize / CLOCKS_PER_SEC,t_greedy/statesize / CLOCKS_PER_SEC,t_ids/statesize / CLOCKS_PER_SEC);

	system("pause");
	return 0;
}
