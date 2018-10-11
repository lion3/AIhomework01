#pragma once
#ifndef support_H
#define support_H
#include <iostream>
#include <vector>
using namespace std;

#define StateNum 9
int* generateRandomly();

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

