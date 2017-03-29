#include "Rubiks3Sol.h"

void main()
{
	for (int i = 0;i < 100;i++) {
		Rubiks3 my_Rubiks;
		my_Rubiks.InputToCube();
		my_Rubiks.PrintRubiks();
		my_Rubiks.Shuffle100();
		my_Rubiks.PrintRubiks();
		Rubiks3Sol sol(my_Rubiks);
		sol.PrintSol();
	}
}