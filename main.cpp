#include <iostream>
#include <string>
#include <vector>
#include "support.h"
#include "BFS.h"
#include "dls.h"
#include "GBFS.h"
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
int initvalue[] = { 6,5,7,1,2,8,0,4,3 };
int main() {
	//test_pri_q();
	CNode* target = new CNode();
	target->key = 123456780;

	CNode* init;
	init = &CNode(*initNodeithVal(initvalue));
	CNode* result = GreedyBestFirstSearch(init, target);
	printrt(*result);
	////init = new Node();
	////initialNode(init, 123046758, 3, NULL, 0, initvalue);

	//printf("BFS \n");
	//Node* result = BFS(init, target);
	//printrt(*result);

	//printf("\n\n\n\n");
	//printf("DLS \n");
	//int limit = 4;
	//Node* result2 = DLS(init, target, limit);
	//printrt(*result2);
	//printf("\n\n\n\n");
	//printf("IDS \n");
	//Node* result3 = IDS(init, target);
	//printrt(*result3);

	//vector<int*> states;
	//for (int i = 0; i < 10; i++) {
	//	int* state = generateRandomly();
	//	if (check_inverse(state)) {
	//		states.push_back(state);
	//	}
	//}
	//printf("generate %d\n", states.size());
	//for (int i = 0; i < states.size(); i++)
	//{
	//	Node* tempinit = initNodeithVal(states[i]);
	//	printf("BFS %d\n", i);
	//	Node* result = BFS(tempinit, target);
	//	if (result == NULL) {
	//		printnd(*tempinit);
	//	}
	//	else {
	//		printrt(*result);
	//	}
	//}
	//

	system("pause");
	return 0;
}
