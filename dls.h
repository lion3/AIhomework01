#pragma once
#ifndef DLS_H
#define DLS_H
#include "support.h"


Node* RDLS(Node* node, Node* goal, int limit);
Node* DLS(Node* init, Node* goal, int limit);
Node * IDS(Node * init, Node * goal);
#endif // !DLS_H
