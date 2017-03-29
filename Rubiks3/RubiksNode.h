#ifndef RUBIKSNODE_H
#define RUBIKSNODE_H

#include<iostream>
typedef unsigned int uint;

struct RNode {
public:
	uint data;
	RNode* next;
	RNode* prev;
	RNode(uint value);
	RNode();
private:

};

typedef RNode* pRNode;
#endif //RUBIKSNODE_H