#ifndef Rubiks3LL_H
#define Rubiks3LL_H
#include<iostream>
#include "RubiksNode.h"
#include <Windows.h>
#include <MMSystem.h>
typedef unsigned int uint;
typedef unsigned int* puint;


struct Rubiks3LL {
public:
	Rubiks3LL();
	~Rubiks3LL();
	void AddNode(uint pdata);
	void PrintMoves(void);

	void AudioMoves(void);

private:
	pRNode phead;
	pRNode ptail;
	void Condense();

	uint ThreesComp(uint data);

	void PrintKey(uint data);
	void AudioKey(uint data);
	pRNode ScrBac(pRNode ptemp);
	uint Shift(uint data);
};

#endif //Rubiks3LL_H
