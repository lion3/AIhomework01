#pragma once
#ifndef support_H
#define support_H
#include <iostream>
#include <vector>
using namespace std;
#define UsedSize 1000000000
#define StateNum 9
#define nodesNum 400000
extern bool Used[UsedSize];
extern int dir[4];
extern Node nodes[nodesNum];

int* generateRandomly();
void initUsed(bool Used[]);
bool check_inverse(int Num[]);
struct Node {
	int sta[StateNum];
	int pos;
	int key;
	Node* pre;
	int step;
};
struct CNode :Node {
	int cost;
	int index;
	CNode() {

	}
	CNode(Node n) {
		step = n.step;
		pre = n.pre;
		pos = n.pos;
		for (int i = 0; i < StateNum; i++) {
			sta[i] = n.sta[i];
		}
		key = n.key;
		cost = 0;
	}
};
bool valid_mov(int pos, int dir);
void childNode(Node& n, Node t, int dir);
bool NodeTest(Node* n, Node* goal);
void initialNode(Node* n, int key, int pos, Node* pre, int step, int initval[]);
void printnd(Node n);
void printnnd(Node n);
void printrt(Node n);
Node* initNodeithVal(int initval[]);

#endif // !support_H

