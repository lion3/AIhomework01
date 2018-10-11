#pragma once
#ifndef GBFS_H
#define GBFS_H
#include "support.h"
Node* GreedyBestFirstSearch(Node* initState, Node* goalState);
int mapkey(Node* n);
void initUsed();
bool NodeTest(Node* n, Node* a);
bool valid_move(Node* n, int dir);
void childNode(Node* n, Node* a, int dir);
int calculate_cost(Node* n);
#endif // !GBFS_H

