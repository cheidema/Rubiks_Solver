#include"RubiksNode.h"

RNode::RNode(uint value) {
	data = value;
	next = NULL;
	prev = NULL;

}

RNode::RNode()
{
	next = NULL;
}
