#ifndef Rubiks3_H
#define Rubiks3_H
#include<iostream>
#include<string>
#include<time.h>
/*

Cube patterns work like so on the front
_____________
|_0_|_1_|_2_|
|_7_|_8_|_3_|
|_6_|_5_|_4_|

Each position is defined in three bits leaving a total of 162 bits.
To make calculations simpler we put each face into 1 integer making the Rubiks cube 6 integers each contiguously holding the cube patterns.
This turns things like face rotations of the cube into 2 bitshifts sending lower indexed cubes up and higher indexed cubes lower.

*/

typedef unsigned int	uint;
typedef unsigned int*	puint;
typedef	char*			pchar;

class Rubiks3 {
public:
	Rubiks3();
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


	void Shuffle100();

	//Necessary Accessor-Mutators
	char Getdic(int index);
	puint Getpfro() {
		return pfro;
	}
	puint Getplef() {
		return plef;
	}
	puint Getpbac() {
		return pbac;
	}
	puint Getprig() {
		return prig;
	}
	puint Getptop() {
		return ptop;
	}
	puint Getpbot() {
		return pbot;
	}


private:
	char NumToColour(puint pface, uint num);

	inline void AddToDic(char newent);

	inline void Rot(puint face);

	inline void IRot(puint face);

	void DRot(puint face);

	char dic[6];
	uint sid[6];
	puint pfro;
	puint plef;
	puint pbac;
	puint prig;
	puint ptop;
	puint pbot;
};

#endif //Rubiks3_H