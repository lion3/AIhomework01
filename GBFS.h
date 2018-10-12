#pragma once
#ifndef GBFS_H
#define GBFS_H
#include "support.h"


CNode* GreedyBestFirstSearch(CNode* initState, CNode* goalState);
int mapkey(Node* n);
void initUsed(bool used[]);

int NotInPlace(int sta[]);
int calculate_cost(CNode* n);
#endif // !GBFS_H

