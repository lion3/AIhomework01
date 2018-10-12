#include "support.h"
bool Used[UsedSize] = { false };
int dir[4] = { 1,3,-1,-3 };
Node nodes[nodesNum];
void initUsed() {
	for (int i = 0; i < 1000000000; i++) {
		Used[i] = false;
	}
}

void childNode(Node& n, Node t, int dir) {
	n.pos = t.pos + dir;
	for (int i = 0; i < StateNum; i++) {
		n.sta[i] = t.sta[i];
	}
	int temp;
	temp = n.sta[n.pos];
	n.sta[n.pos] = n.sta[t.pos];
	n.sta[t.pos] = temp;
	n.key = 0;
	for (int i = 0; i < StateNum - 1; i++) {
		n.key += n.sta[i];
		n.key *= 10;
	}
	n.key += n.sta[StateNum - 1];
	n.step = t.step + 1;
}
bool NodeTest(Node* n, Node* goal) {
	return n->key == goal->key;
}
bool valid_mov(int pos, int dir) {
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

void initialNode(Node* n, int key, int pos, Node* pre, int step, int initval[]) {
	n->key = 123046758;
	n->pos = 3;
	n->pre = NULL;
	n->step = 0;
	for (int i = 0; i < StateNum; i++) {
		n->sta[i] = initval[i];
	}
}
void printndformat(Node n) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", n.sta[i * 3 + j]);
		}
		printf("\n");
	}
}
void printnd(Node n) {
	printf("node %d %d\n", n.step, n.key);
	printndformat(n);
}
void printnnd(Node n) {
	printf("NEXT %d %d\n", n.step, n.key);
	printndformat(n);
}
void printrt(Node n) {
	int t = n.step;
	Node temp = n;
	while (t >= 0) {
		printf("%d %d\n", t, temp.key);
		printndformat(temp);		
		if (temp.pre != NULL) {
			temp = *temp.pre;
		} 
		t = t - 1;
	}
}
int* generateRandomly() {
	vector<int> initNum = { 1,2,3,4,5,6,7,8,0 };
	int* Num = new int[9];
	int index = -1;
	for (int i = 0; i < 9; i++) {
		index = rand() % initNum.size();
		Num[i] = initNum[index];
		initNum.erase(initNum.begin()+index);
	}
	//for (int i = 0; i < 9; i++) {
	//	printf("%d ", Num[i]);
	//}
	//printf("\n");
	//if (check_inverse(Num)) {
	//	printf("can solve\n");
	//}
	return Num;
}
bool check_inverse(int Num[]) {
	int sum = 0;
	for (int i = 1; i < 9; i++) {
		for (int j = i-1; j >= 0; j--) {
			if (Num[i] == 0 || Num[j] == 0) continue;
			if (Num[j] > Num[i]) sum++;
		}
	}
//	printf("sum is %d\n", sum);
	return (sum % 2 == 0);
}
Node* initNodeithVal(int initval[]) {
	Node* n = new Node();
	n->step = 0;
	n->pre = NULL;
	for (int i = 0; i < StateNum; i++) {
		n->sta[i] = initval[i];
		if (initval[i] == 0) {
			n->pos = i;
		}
	}
	n->key = 0;
	for (int i = 0; i < StateNum - 1; i++) {
		n->key += n->sta[i];
		n->key *= 10;
	}
	n->key += n->sta[StateNum - 1];
	return n;
}