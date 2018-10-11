#pragma once
#ifndef GBFS_H
#define GBFS_H
#include "support.h"
#define StateNum 9
#define nodesNum 400000
#define UsedSize 100000000
CNode* GreedyBestFirstSearch(CNode* initState, CNode* goalState);
int mapkey(Node* n);
void initUsed(bool used[]);

int NotInPlace(int sta[]);
int calculate_cost(CNode* n);
#endif // !GBFS_H

