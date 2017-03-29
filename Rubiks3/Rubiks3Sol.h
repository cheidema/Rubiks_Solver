#ifndef Rubiks3Sol_H
#define Rubiks3Sol_H
#include"Rubiks3LL.h"
#include "Rubiks3.h"
#include<iostream>
#include<string>
/*

Cube patterns work like so on the front
	_____________
	|_0_|_1_|_2_|
	|_7_|_8_|_3_|
	|_6_|_5_|_4_|
	
	Each position is defined in three bits leaving a total of 162 bits.
	To make calculations simpler we put each face into 1 integer making the Rubiks cube 6 integers each contiguously holding the cube patterns.
	This turns things like face rotations of the cube into 2 bitshifts sending lower indexed cubes up and higher indexed cubes lower.


	The linked list of the solution has numbers 1-18 ending in 0. Each of these numbers represent a different move of the cube and the 0 is when the cube is done.

*/

typedef unsigned int	uint;
typedef unsigned int*	puint;
typedef	char*			pchar;

class Rubiks3Sol {
public:
	void PrintSol();
	void AudioSol();
	Rubiks3Sol(Rubiks3 my_Rubiks);
private:
	void Fro();
	void IFro();
	void Lef();
	void ILef();
	void Bac();
	void IBac();
	void Rig();
	void IRig();
	void Top();
	void ITop();
	void Bot();
	void IBot();
	void ShiL();
	void ShiR();
	void ShiT();
	void ShiB();
	void RotL();
	void RotR();
	void InputToCube();
	void PrintRubiks();
	char NumToColour(puint pface, uint num);
	inline void AddToDic(char newent);

	void Alg();

	void Stage1();

	void Stage2();

	void Stage3();

	void Stage4();

	void Stage5();

	void Stage6();

	void Stage7();

	void Stage8();

	inline void Rot(puint face);

	inline void IRot(puint face);

	void DRot(puint face);

	uint Comzer(puint pface);

	uint Comfir(puint pface);

	uint Comsec(puint pface);

	uint Comthi(puint pface);

	uint Comfou(puint pface);

	uint Comfif(puint pface);

	uint Comsix(puint pface);

	uint Comsev(puint pface);

	uint Comeig(puint pface);


	//Properties of class
	Rubiks3LL sol;
	uint data[2];
	char dic[6];
	uint sid[6];
	puint pfro;
	puint plef;
	puint pbac;
	puint prig;
	puint ptop;
	puint pbot;
};

#endif //Rubiks3Sol_H

