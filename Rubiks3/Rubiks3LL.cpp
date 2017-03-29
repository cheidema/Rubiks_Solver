#include "Rubiks3LL.h"


Rubiks3LL::Rubiks3LL()
{
	phead = NULL;
	ptail = NULL;
}

Rubiks3LL::~Rubiks3LL()
{
	pRNode ptemp;
	if (phead == NULL) {
		return;
	}
	else {
		ptemp = phead;
	}
	while (ptemp->next != ptail) {
		ptemp = ptemp->next;
		delete ptemp->prev;
		ptemp->prev = NULL;
	}
	ptail = NULL;
	delete ptemp->next;
	delete ptemp;
}




void Rubiks3LL::AddNode(uint data)
{
	if (phead == NULL) {
		phead = new RNode(data);
		ptail = phead;
	}
	else {
		pRNode ptemp = new RNode(data);
		ptemp->prev = ptail;
		ptail->next = ptemp;
		ptail = ptemp;
	}
}

void Rubiks3LL::PrintMoves(void)
{
	Condense();
	pRNode ptemp = phead;
	while (ptemp != ptail) {
		PrintKey(ptemp->data);
		ptemp = ptemp->next;
	}
	PrintKey(ptemp->data);

}

void Rubiks3LL::AudioMoves(void) {
	Condense();
	pRNode ptemp = phead;
	while (ptemp != ptail) {
		AudioKey(ptemp->data);
		ptemp = ptemp->next;
	}
	AudioKey(ptemp->data);
}

void Rubiks3LL::Condense(){
#define nextx2	next->next
#define nextx3	next->next->next
#define nextx4	next->next->next->next
#define nextx5	next->next->next->next->next
#define nextd	next->data
#define nextx2d	next->next->data
#define nextx3d	next->next->next->data
#define nextx4d	next->next->next->next->data
#define nextx5d	next->next->next->next->next->data
	pRNode ptemp;
	if (phead != NULL) {
		ptemp = phead;
	}
	else {
		return;
	}
	for (;;) {
		//4's
		if (ptemp == phead && ptemp->next != NULL && ptemp->nextx2 != NULL && ptemp->nextx3 != NULL \
			&& ptemp->data == ptemp->nextd && ptemp->data == ptemp->nextx2d && ptemp->data == ptemp->nextx3d\
			&& ptemp->nextx3 == ptail) {
			phead = NULL;
			ptail = NULL;
			delete ptemp->nextx3;
			delete ptemp->nextx2;
			delete ptemp->next;
			delete ptemp;
		}//if only four nodes correct!
		else if (ptemp == phead && ptemp->next != NULL && ptemp->nextx2 != NULL && ptemp->nextx3 != NULL \
			&& ptemp->data == ptemp->nextd && ptemp->data == ptemp->nextx2d && ptemp->data == ptemp->nextx3d\
			&& ptemp->nextx3 != ptail) {
			phead = ptemp->nextx4;
			phead->prev = NULL;
			delete ptemp->nextx3;
			delete ptemp->nextx2;
			delete ptemp->next;
			delete ptemp;
		}//if first four and there's more than four nodes correct!
		else if (ptemp->next != NULL && ptemp->nextx2 != NULL && ptemp->nextx3 != NULL \
			&& ptemp->data == ptemp->nextd && ptemp->data == ptemp->nextx2d && ptemp->data == ptemp->nextx3d\
			&& ptemp->nextx3 == ptail) {
			ptail = ptemp->prev;
			ptail->next = NULL;
			pRNode ptempDel = ptemp;
			ptemp=ScrBac(ptemp);
			delete ptempDel->nextx3;
			delete ptempDel->nextx2;
			delete ptempDel->next;
			delete ptempDel;
		}//if last four nodes to be deleted correct!
		else if (ptemp->next != NULL && ptemp->nextx2 != NULL && ptemp->nextx3 != NULL \
			&& ptemp->data == ptemp->nextd && ptemp->data == ptemp->nextx2d && ptemp->data == ptemp->nextx3d) {
			ptemp->prev->next = ptemp->nextx4;
			ptemp->nextx4->prev = ptemp->prev;
			pRNode ptempDel = ptemp;
			ptemp=ScrBac(ptemp);
			delete ptempDel->nextx3;
			delete ptempDel->nextx2;
			delete ptempDel->next;
			delete ptempDel;
		}//if four general consecutive nodes need to be deleted correct!
		 //end 4's

		 //3's
		else if (phead == ptemp && ptemp->next != NULL && ptemp->nextx2 != NULL \
			&& ptemp->data == ptemp->nextd && ptemp->data == ptemp->nextx2d      \
			&& ptemp->nextx2 == ptail) {
			ptail = ptemp;
			delete ptemp->nextx2;
			delete ptemp->next;
			phead->next = NULL;
			ptail->prev = NULL;
			phead->data = ThreesComp(phead->data);
		}//if only three nodes	correct!
		else if (phead == ptemp && ptemp->next != NULL && ptemp->nextx2 != NULL \
			&& ptemp->data == ptemp->nextd && ptemp->data == ptemp->nextx2d) {
			pRNode pstake = ptemp->nextx3;
			delete ptemp->nextx2;
			delete ptemp->next;
			ptemp->data = ThreesComp(ptemp->data);
			ptemp->next = pstake;
			pstake->prev = ptemp;
		}//if first 3 nodes correct!
		else if (ptemp->next != NULL && ptemp->nextx2 != NULL && ptemp->nextx2 == ptail \
			&& ptemp->data == ptemp->nextd && ptemp->data == ptemp->nextx2d) {
			ptail = ptemp;
			delete ptemp->nextx2;
			delete ptemp->next;
			ptail->next = NULL;
			ptemp->data = ThreesComp(ptemp->data);
			ptemp = ScrBac(ptemp);
		}//if 3 last nodes correct!
		else if (ptemp->next != NULL && ptemp->nextx2 != NULL \
			&& ptemp->data == ptemp->nextd && ptemp->data == ptemp->nextx2d) {
			pRNode pstake = ptemp->nextx3;
			delete ptemp->nextx2;
			delete ptemp->next;
			ptemp->next = pstake;
			pstake->prev = ptemp;;
			ptemp->data = ThreesComp(ptemp->data);
			ptemp=ScrBac(ptemp);
		}//if 3 general nodes correct!
		 //end 3's

		 //2's
		else if (ptemp->next != NULL && ((((ptemp->data) & 1) && ptemp->data == ((ptemp->nextd) + 1)) \
			|| (!((ptemp->data) & 1) && ptemp->data == ((ptemp->nextd) - 1))) \
			&& ptemp == phead && ptemp->next == ptail){
			phead = NULL;
			ptail = NULL;
			delete ptemp->next;
			delete ptemp;
		}//Fro IFro or Rig IRig or ShiftLeft ShiftRight are examples only 2 nodes correct!

		else if (ptemp->next != NULL && ((((ptemp->data) & 1) && ptemp->data == ((ptemp->nextd) + 1))\
			|| (!((ptemp->data) & 1) && ptemp->data == ((ptemp->nextd) - 1)))\
			&& ptemp == phead){
			phead = phead->nextx2;
			phead->prev = NULL;
			delete ptemp->next;
			delete ptemp;
		}//Fro IFro or Rig IRig or ShiftLeft ShiftRight are examples first 2 nodes correct!

		else if (ptemp->next != NULL && ((((ptemp->data) & 1) && ptemp->data == ((ptemp->nextd) + 1))
			|| (!((ptemp->data) & 1) && ptemp->data == ((ptemp->nextd) - 1)))\
			&&ptemp->next == ptail){
			ptail = ptemp->prev;
			ptail->next = NULL;
			pRNode ptempDel = ptemp;
			ptemp = ScrBac(ptemp);
			delete ptempDel->next;
			delete ptempDel;
		}//Fro IFro or Rig IRig or ShiftLeft ShiftRight are examples last 2 nodes correct!

		else if (ptemp->next != NULL && ((!((ptemp->data) & 1) && ptemp->data == ((ptemp->nextd) + 1))
			|| (((ptemp->data) & 1) && ptemp->data == ((ptemp->nextd) - 1)))) {
			ptemp->prev->next = ptemp->nextx2;
			ptemp->nextx2->prev = ptemp->prev;
			pRNode ptempDel = ptemp;
			ptemp = ScrBac(ptemp);
			delete ptempDel->next;
			delete ptempDel;
		}//Fro IFro or Rig IRig or ShiftLeft ShiftRight are examples middle 2 nodes correct!
		 //end 2's

		else {
			if (ptemp->next == NULL) {
				return;
			}
			else {
				ptemp = ptemp->next;
			}
		}
	}
#undef nextx2
#undef nextx3
#undef nextx4
#undef nextx5
#undef nextd	
#undef nextx2d	
#undef nextx3d
#undef nextx4d
#undef nextx5d
}

uint Rubiks3LL::ThreesComp(uint data) {
	if (data & 1 == 0) {
		return data -1;
	}
	else {
		return data + 1;
	}
}

inline void Rubiks3LL::PrintKey(uint data)
{
	if (data == 0) {
		std::cout << "Finished" << "  ";
	}
	else if (data == 1) {
		std::cout << "Front" << "  ";
	}
	else if (data == 2) {
		std::cout << "Inverted Front" << "  ";
	}
	else if (data == 3) {
		std::cout << "Left" << "  ";
	}
	else if (data == 4) {
		std::cout << "Inverted Left" << "  ";
	}
	else if (data == 5) {
		std::cout << "Back" << "  ";
	}
	else if (data == 6) {
		std::cout << "Inverted Back" << "  ";
	}
	else if (data == 7) {
		std::cout << "Right" << "  ";
	}
	else if (data == 8) {
		std::cout << "Inverted Right" << "  ";
	}
	else if (data == 9) {
		std::cout << "Top" << "  ";
	}
	else if (data == 10) {
		std::cout << "Inverted Top" << "  ";
	}
	else if (data == 11) {
		std::cout << "Bottom" << "  ";
	}
	else if (data == 12) {
		std::cout << "Inverted Bottom" << "  ";
	}
	else if (data == 13) {
		std::cout << "Shift Left" << "  ";
	}
	else if (data == 14) {
		std::cout << "Shift Right" << "  ";
	}
	else if (data == 15) {
		std::cout << "Shift Top" << "  ";
	}
	else if (data == 16) {
		std::cout << "Shift Bottom" << "  ";
	}
	else if (data == 17) {
		std::cout << "Rotate Left" << "  ";
	}
	else if (data == 18) {
		std::cout << "Rotate Right" << "  ";
	}
}

inline void Rubiks3LL::AudioKey(uint data) {
	if (data == 1) {
		PlaySound(TEXT("Front.wav"), NULL, SND_SYNC);
	}
	else if (data == 2) {
		PlaySound(TEXT("Inverted_Front.wav"), NULL, SND_SYNC);
	}
	else if (data == 3) {
		PlaySound(TEXT("Left.wav"), NULL, SND_SYNC);
	}
	else if (data == 4) {
		PlaySound(TEXT("Inverted_Left.wav"), NULL, SND_SYNC);
	}
	else if (data == 5) {
		PlaySound(TEXT("Back.wav"), NULL, SND_SYNC);
	}
	else if (data == 6) {
		PlaySound(TEXT("Inverted_Back.wav"), NULL, SND_SYNC);
	}
	else if (data == 7) {
		PlaySound(TEXT("Right.wav"), NULL, SND_SYNC);
	}
	else if (data == 8) {
		PlaySound(TEXT("Inverted_Right.wav"), NULL, SND_SYNC);
	}
	else if (data == 9) {
		PlaySound(TEXT("Top.wav"), NULL, SND_SYNC);
	}
	else if (data == 10) {
		PlaySound(TEXT("Inverted_Top.wav"), NULL, SND_SYNC);
	}
	else if (data == 11) {
		PlaySound(TEXT("Bottom.wav"), NULL, SND_SYNC);
	}
	else if (data == 12) {
		PlaySound(TEXT("Inverted_Bottom.wav"), NULL, SND_SYNC);
	}
}

inline pRNode Rubiks3LL::ScrBac(pRNode ptemp) {
	for (uint i = 0;i < 3;i++)
	if (ptemp->prev != NULL) {
		ptemp = ptemp->prev;
	}
	return ptemp;
}

uint Rubiks3LL::Shift(uint data) {
	if (data == 1 || data == 3 || data == 5 || data == 7 || data == 9 || data == 11) {
		return data + 1;
	}
	else if (data == 2 || data == 4 || data == 6 || data == 8 || data == 10 || data == 12) {
		return data - 1;
	}
}