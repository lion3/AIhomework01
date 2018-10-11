#include <iostream>
#include <string>
#include <vector>
#include "support.h"
#include "BFS.h"
#include "dls.h"
using namespace std;
//int initvalue[] = { 1,2,3,0,4,6,7,5,8 };

int initvalue[] = { 6,5,7,1,2,8,0,4,3 };
int main() {
	Node* target = new Node();
	target->key = 123456780;

	Node* init;
	init = initNodeithVal(initvalue);
	//init = new Node();
	//initialNode(init, 123046758, 3, NULL, 0, initvalue);
	printf("BFS \n");
	Node* result = BFS(init, target);
	printrt(*result);
	//printf("\n\n\n\n");
	//printf("DLS \n");
	//int limit = 4;
	//Node* result2 = DLS(init, target, limit);
	//printrt(*result2);
	//printf("\n\n\n\n");
	//printf("IDS \n");
	//Node* result3 = IDS(init, target);
	//printrt(*result3);

	vector<int*> states;
	for (int i = 0; i < 10; i++) {
		int* state = generateRandomly();
		if (check_inverse(state)) {
			states.push_back(state);
		}
	}
	printf("generate %d\n", states.size());
	for (int i = 0; i < states.size(); i++)
	{
		Node* tempinit = initNodeithVal(states[i]);
		printf("BFS %d\n", i);
		Node* result = BFS(tempinit, target);
		if (result == NULL) {
			printnd(*tempinit);
		}
		else {
			printrt(*result);
		}
	}
	

	system("pause");
	return 0;
}
