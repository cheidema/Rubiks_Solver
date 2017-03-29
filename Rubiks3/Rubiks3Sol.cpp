#include "Rubiks3Sol.h"

const uint zer = 0xE0000000;
const uint fir = 0x1C000000;
const uint sec = 0x03800000;
const uint thi = 0x00700000;
const uint fou = 0x000E0000;
const uint fif = 0x0001C000;
const uint six = 0x00003800;
const uint sev = 0x00000700;
const uint eig = 0x000000E0;
const uint own = 0xFFFFFFE0;

const uint fr = 0;
const uint le = 1;
const uint ba = 2;
const uint ri = 3;
const uint to = 4;
const uint bo = 5;

const uint dCu = 3;
const uint dMo = 4;





void Rubiks3Sol::PrintSol()
{
	sol.PrintMoves();
	return;
}

void Rubiks3Sol::AudioSol()
{
	sol.AudioMoves();
	return;
}

Rubiks3Sol::Rubiks3Sol(Rubiks3 my_Rubiks)
{
	data[0] = 0x12345600;
	data[1] = 0x789ABC00;
	for (int i = 0;i < 6;i++)
	{
		dic[i] = my_Rubiks.Getdic(i);
	}
	pfro = &sid[fr];
	plef = &sid[le];
	pbac = &sid[ba];
	prig = &sid[ri];
	ptop = &sid[to];
	pbot = &sid[bo];
	sid[fr] = *my_Rubiks.Getpfro();
	sid[le] = *my_Rubiks.Getplef();
	sid[ba] = *my_Rubiks.Getpbac();
	sid[ri] = *my_Rubiks.Getprig();
	sid[to] = *my_Rubiks.Getptop();
	sid[bo] = *my_Rubiks.Getpbot();

	Alg();
}

void Rubiks3Sol::Fro() {
	int temp = *plef & (sec | thi | fou);
	Rot(pfro);
	*plef = (*plef & (zer | fir | fif | six | sev | eig)) | ((*pbot & (zer | fir | sec)) >> (2 * dCu));
	*pbot = (*pbot & (thi | fou | fif | six | sev | eig)) | ((*prig & zer) >> (2 * dCu)) | ((*prig & (six | sev)) << (6 * dCu));
	*prig = (*prig & (fir | sec | thi | fou | fif | eig)) | ((*ptop & six) << (6 * dCu)) | ((*ptop & (fou | fif)) >> (2 * dCu));
	*ptop = (*ptop & (zer | fir | sec | thi | sev | eig)) | (temp >> (2 * dCu));
	sol.AddNode((data[0]>>(7*dMo))&15);
}

void Rubiks3Sol::IFro() {
	int temp = *plef & (sec | thi | fou);
	IRot(pfro);
	*plef = (*plef & (zer | fir | fif | six | sev | eig)) | ((*ptop & (fou | fif | six)) << (2 * dCu));
	*ptop = (*ptop & (zer | fir | sec | thi | sev | eig)) | ((*prig & zer) >> (6 * dCu)) | ((*prig & (six | sev)) << (2 * dCu));
	*prig = (*prig & (fir | sec | thi | fou | fif | eig)) | ((*pbot & sec) << (2 * dCu)) | ((*pbot & (zer | fir)) >> (6 * dCu));
	*pbot = (*pbot & (thi | fou | fif | six | sev | eig)) | (temp << (2 * dCu));
	sol.AddNode((data[0] >> (6 * dMo)) & 15);
}

void Rubiks3Sol::Lef() {
	int temp = *pfro & (zer | six | sev);
	Rot(plef);
	*pfro = (*pfro & (fir | sec | thi | fou | fif | eig)) | (*ptop & (zer | six | sev));
	*ptop = (*ptop & (fir | sec | thi | fou | fif | eig)) | ((*pbac & fou) << (4 * dCu)) | ((*pbac & (sec | thi)) >> (4 * dCu));
	*pbac = (*pbac & (zer | fir | fif | six | sev | eig)) | ((*pbot & zer) >> (4 * dCu)) | ((*pbot & (six | sev)) << (4 * dCu));
	*pbot = (*pbot & (fir | sec | thi | fou | fif | eig)) | temp;
	sol.AddNode((data[0] >> (5 * dMo)) & 15);
}

void Rubiks3Sol::ILef() {
	int temp = *pfro & (zer | six | sev);
	IRot(plef);
	*pfro = (*pfro & (fir | sec | thi | fou | fif | eig)) | (*pbot & (zer | six | sev));
	*pbot = (*pbot & (fir | sec | thi | fou | fif | eig)) | ((*pbac & fou) << (4 * dCu)) | ((*pbac & (sec | thi)) >> (4 * dCu));
	*pbac = (*pbac & (zer | fir | fif | six | sev | eig)) | ((*ptop & zer) >> (4 * dCu)) | ((*ptop & (six | sev)) << (4 * dCu));
	*ptop = (*ptop & (fir | sec | thi | fou | fif | eig)) | temp;
	sol.AddNode((data[0] >> (4 * dMo)) & 15);
}

void Rubiks3Sol::Bac() {
	int temp = *plef&(zer | six | sev);
	Rot(pbac);
	*plef = (*plef & (fir | sec | thi | fou | fif | eig)) | ((*ptop & sec) << (2 * dCu)) | ((*ptop & (zer | fir)) >> (6 * dCu));
	*ptop = (*ptop & (thi | fou | fif | six | sev | eig)) | ((*prig & (sec | thi | fou)) << (2 * dCu));
	*prig = (*prig & (zer | fir | fif | six | sev | eig)) | ((*pbot & (fou | fif | six)) << (2 * dCu));
	*pbot = (*pbot & (zer | fir | sec | thi | sev | eig)) | ((temp&zer) >> (6 * dCu)) | ((temp&(six | sev)) << (2 * dCu));
	sol.AddNode((data[0] >> (3 * dMo)) & 15);
}

void Rubiks3Sol::IBac() {
	int temp = *plef&(zer | six | sev);
	IRot(pbac);
	*plef = (*plef & (fir | sec | thi | fou | fif | eig)) | ((*pbot & six) << (6 * dCu)) | ((*pbot & (fou | fif)) >> (2 * dCu));
	*pbot = (*pbot & (zer | fir | sec | thi | sev | eig)) | ((*prig & (sec | thi | fou)) >> (2 * dCu));
	*prig = (*prig & (zer | fir | fif | six | sev | eig)) | ((*ptop & (zer | fir | sec)) >> (2 * dCu));
	*ptop = (*ptop & (thi | fou | fif | six | sev | eig)) | ((temp&zer) >> (2 * dCu)) | ((temp&(six | sev)) << (6 * dCu));
	sol.AddNode((data[0] >> (2 * dMo)) & 15);

}

void Rubiks3Sol::Rig() {
	int temp = *pfro & (sec | thi | fou);
	Rot(prig);
	*pfro = (*pfro & (zer | fir | fif | six | sev | eig)) | (*pbot & (sec | thi | fou));
	*pbot = (*pbot & (zer | fir | fif | six | sev | eig)) | ((*pbac & zer) >> (4 * dCu)) | ((*pbac & (six | sev)) << (4 * dCu));
	*pbac = (*pbac & (fir | sec | thi | fou | fif | eig)) | ((*ptop & fou) << (4 * dCu)) | ((*ptop & (sec | thi)) >> (4 * dCu));
	*ptop = (*ptop & (zer | fir | fif | six | sev | eig)) | temp;
	sol.AddNode((data[1] >> (7 * dMo)) & 15);
}

void Rubiks3Sol::IRig() {
	int temp = *pfro & (sec | thi | fou);
	IRot(prig);
	*pfro = (*pfro & (zer | fir | fif | six | sev | eig)) | (*ptop & (sec | thi |fou));
	*ptop = (*ptop & (zer | fir | fif | six | sev | eig)) | ((*pbac & zer) >> (4 * dCu)) | ((*pbac & (six | sev)) << (4 * dCu));
	*pbac = (*pbac & (fir | sec | thi | fou | fif | eig)) | ((*pbot & fou) << (4 * dCu)) | ((*pbot & (sec | thi)) >> (4 * dCu));
	*pbot = (*pbot & (zer | fir | fif | six | sev | eig)) | temp;
	sol.AddNode((data[1] >> (6 * dMo)) & 15);
}

void Rubiks3Sol::Top() {
	int temp = *pfro&(zer | fir | sec);
	Rot(ptop);
	*pfro = (*pfro & (thi | fou | fif | six | sev | eig)) | (*prig & (zer | fir | sec));
	*prig = (*prig & (thi | fou | fif | six | sev | eig)) | (*pbac & (zer | fir | sec));
	*pbac = (*pbac & (thi | fou | fif | six | sev | eig)) | (*plef & (zer | fir | sec));
	*plef = (*plef & (thi | fou | fif | six | sev | eig)) | temp;
	sol.AddNode((data[1] >> (5 * dMo)) & 15);
}

void Rubiks3Sol::ITop() {
	int temp = *pfro&(zer | fir | sec);
	IRot(ptop);
	*pfro = (*pfro & (thi | fou | fif | six | sev | eig)) | (*plef & (zer | fir | sec));
	*plef = (*plef & (thi | fou | fif | six | sev | eig)) | (*pbac & (zer | fir | sec));
	*pbac = (*pbac & (thi | fou | fif | six | sev | eig)) | (*prig & (zer | fir | sec));
	*prig = (*prig & (thi | fou | fif | six | sev | eig)) | temp;
	sol.AddNode((data[1] >> (4 * dMo)) & 15);
}

void Rubiks3Sol::Bot() {
	int temp = *pfro&(fou | fif | six);
	Rot(pbot);
	*pfro = (*pfro & (zer | fir | sec | thi | sev | eig)) | (*plef & (fou | fif | six));
	*plef = (*plef & (zer | fir | sec | thi | sev | eig)) | (*pbac & (fou | fif | six));
	*pbac = (*pbac & (zer | fir | sec | thi | sev | eig)) | (*prig & (fou | fif | six));
	*prig = (*prig & (zer | fir | sec | thi | sev | eig)) | temp;
	sol.AddNode((data[1] >> (3 * dMo)) & 15);
}

void Rubiks3Sol::IBot() {
	int temp = *pfro&(fou | fif | six);
	IRot(pbot);
	*pfro = (*pfro & (zer | fir | sec | thi | sev | eig)) | (*prig & (fou | fif | six));
	*prig = (*prig & (zer | fir | sec | thi | sev | eig)) | (*pbac & (fou | fif | six));
	*pbac = (*pbac & (zer | fir | sec | thi | sev | eig)) | (*plef & (fou | fif | six));
	*plef = (*plef & (zer | fir | sec | thi | sev | eig)) | temp;
	sol.AddNode((data[1] >> (2 * dMo)) & 15);
}

void Rubiks3Sol::ShiL() {
	IRot(ptop);
	Rot(pbot);
	puint ptemp = pfro;
	pfro = plef;
	plef = pbac;
	pbac = prig;
	prig = ptemp;
	uint tdata = data[0];
	data[0] = ((data[0] & 0x00FFFF00) << (2 * dMo)) | ((data[1] & 0xFF000000) >> (4 * dMo));
	data[1] = (tdata & 0xFF000000) | (data[1] & 0x00FFFF00);
}

void Rubiks3Sol::ShiR() {
	Rot(ptop);
	IRot(pbot);
	puint ptemp = pfro;
	pfro = prig;
	prig = pbac;
	pbac = plef;
	plef = ptemp;
	uint tdata = data[0];
	data[0] = ((data[0] & 0xFFFF0000) >> (2 * dMo)) | ((data[1] & 0xFF000000));
	data[1] = ((tdata & 0x0000FF00) << (4 * dMo)) | ((data[1] & 0x00FFFF00));
}

void Rubiks3Sol::ShiT() {
	Rot(plef);
	IRot(prig);
	DRot(pbot);
	DRot(pbac);
	puint ptemp = pfro;
	pfro = ptop;
	ptop = pbac;
	pbac = pbot;
	pbot = ptemp;
	uint tdata = data[0];
	data[0] = (data[0] & 0x00FF0000) | ((data[1] & 0x00FF0000) << (2 * dMo)) | (data[1] & 0x0000FF00);
	data[1] = (data[1] & 0xFF000000) | ((tdata & 0xFF000000) >> (4 * dMo)) | ((tdata & 0x0000FF00) << (2 * dMo));
}

void Rubiks3Sol::ShiB() {
	IRot(plef);
	Rot(prig);
	DRot(ptop);
	DRot(pbac);
	puint ptemp = pfro;
	pfro = pbot;
	pbot = pbac;
	pbac = ptop;
	ptop = ptemp;
	uint tdata = data[0];
	data[0] = (data[0] & 0x00FF0000) | ((data[1] & 0x0000FF00) << (4 * dMo)) | ((data[1] & 0x00FF0000) >> (2 * dMo));
	data[1] = (data[1] & 0xFF000000) | ((tdata & 0xFF000000) >> (2 * dMo)) | (tdata & 0x0000FF00);
}

void Rubiks3Sol::RotL() {
	Rot(pbac);
	IRot(pfro);
	IRot(ptop);
	IRot(plef);
	IRot(pbot);
	IRot(prig);
	puint ptemp = plef;
	plef = ptop;
	ptop = prig;
	prig = pbot;
	pbot = ptemp;
	uint tdata = data[0];
	data[0] = (data[0] & 0xFF00FF00) | (data[1] & 0x00FF0000);
	data[1] = ((data[1] & 0xFF000000) >> (2 * dMo)) | ((tdata & 0x00FF0000) >> (2 * dMo)) | ((data[1] & 0x0000FF00) << (4 * dMo));
}

void Rubiks3Sol::RotR() {
	IRot(pbac);
	Rot(pfro);
	Rot(ptop);
	Rot(plef);
	Rot(pbot);
	Rot(prig);
	puint ptemp = plef;
	plef = pbot;
	pbot = prig;
	prig = ptop;
	ptop = ptemp;
	uint tdata = data[0];
	data[0] = (data[0] & 0xFF00FF00) | ((data[1] & 0x0000FF00) << (2 * dMo));
	data[1] = ((data[1] & 0xFF000000) >> (4 * dMo)) | (tdata & 0x00FF0000) | ((data[1] & 0x00FF0000) << (2 * dMo));
}

void Rubiks3Sol::InputToCube()
{
	std::string rawinput;
	char input[54];

	std::cin >> rawinput;

	for (int i = 0;i < 54;i++) {
		AddToDic(rawinput[i]);
	}
	if (dic[5] == '_') {
		std::cout << "Too few different inputs";
		exit(0);
	}
	for (int i = 0;i < 6;i++)
		sid[i] = 0;
	for (int i = 0;i < 6;i++) {
		for (int j = 0;j < 9;j++) {
			if (rawinput[9 * i + j] == dic[0])
				sid[i] = (0b000 << 29 - 3 * j) + sid[i];
			else if (rawinput[9 * i + j] == dic[1])
				sid[i] = (0b001 << 29 - 3 * j) + sid[i];
			else if (rawinput[9 * i + j] == dic[2])
				sid[i] = (0b010 << (29 - 3 * j)) + sid[i];
			else if (rawinput[9 * i + j] == dic[3])
				sid[i] = (0b011 << (29 - 3 * j)) + sid[i];
			else if (rawinput[9 * i + j] == dic[4])
				sid[i] = (0b100 << 29 - 3 * j) + sid[i];
			else if (rawinput[9 * i + j] == dic[5])
				sid[i] = (0b101 << 29 - 3 * j) + sid[i];
		}
	}
	return;
}

void Rubiks3Sol::PrintRubiks()
{
#define NTC	NumToColour
	std::cout << "   " << NTC(ptop, zer) << NTC(ptop, fir) << NTC(ptop, sec) << std::endl\
			  << "   " << NTC(ptop, sev) << NTC(ptop, eig) << NTC(ptop, thi) << std::endl\
			  << "   " << NTC(ptop, six) << NTC(ptop, fif) << NTC(ptop, fou) << std::endl;

	std::cout << NTC(plef, zer) << NTC(plef, fir) << NTC(plef, sec)\
			  << NTC(pfro, zer) << NTC(pfro, fir) << NTC(pfro, sec)\
			  << NTC(prig, zer) << NTC(prig, fir) << NTC(prig, sec)\
			  << NTC(pbac, zer) << NTC(pbac, fir) << NTC(pbac, sec) << std::endl;

	std::cout << NTC(plef, sev) << NTC(plef, eig) << NTC(plef, thi)\
			  << NTC(pfro, sev) << NTC(pfro, eig) << NTC(pfro, thi)\
			  << NTC(prig, sev) << NTC(prig, eig) << NTC(prig, thi)\
			  << NTC(pbac, sev) << NTC(pbac, eig) << NTC(pbac, thi) << std::endl;

	std::cout << NTC(plef, six) << NTC(plef, fif) << NTC(plef, fou)\
			  << NTC(pfro, six) << NTC(pfro, fif) << NTC(pfro, fou)\
			  << NTC(prig, six) << NTC(prig, fif) << NTC(prig, fou)\
			  << NTC(pbac, six) << NTC(pbac, fif) << NTC(pbac, fou) << std::endl;

	std::cout << "   " << NTC(pbot, zer) << NTC(pbot, fir) << NTC(pbot, sec) << std::endl\
			  << "   " << NTC(pbot, sev) << NTC(pbot, eig) << NTC(pbot, thi) << std::endl\
			  << "   " << NTC(pbot, six) << NTC(pbot, fif) << NTC(pbot, fou) << std::endl;
#undef NTC
}

char Rubiks3Sol::NumToColour(puint pface, uint pos) {
	int shift = 0;
	if (pos == zer)
		shift = 29;
	else if (pos == fir)
		shift = 26;
	else if (pos == sec)
		shift = 23;
	else if (pos == thi)
		shift = 20;
	else if (pos == fou)
		shift = 17;
	else if (pos == fif)
		shift = 14;
	else if (pos == six)
		shift = 11;
	else if (pos == sev)
		shift = 8;
	else if (pos = eig)
		shift = 5;

	if (((*pface >>shift) & 7) == 0)
		return dic[0];
	else if (((*pface >> shift) & 7) == 1)
		return dic[1];
	else if (((*pface >> shift) & 7) == 2)
		return dic[2];
	else if (((*pface >> shift) & 7) == 3)
		return dic[3];
	else if (((*pface >> shift) & 7) == 4)
		return dic[4];
	else if (((*pface >> shift) & 7) == 5)
		return dic[5];
}

inline void Rubiks3Sol::AddToDic(char newent)
{
	for (int i = 0;i < 6;i++) {
		if (newent == dic[i])
			return;
	}
	int choice = 0;
	while (dic[choice] != '_') {
		choice++;
		if (choice == 6) {
			std::cout << std::endl << "Too many Entries seen." << std::endl;
			exit(0);
		}
	}
	dic[choice] = newent;
}



void Rubiks3Sol::Alg()
{
	Stage1();
	Stage2();
	Stage3();
	Stage4();
	Stage5();
	Stage6();
	Stage7();
	Stage8();
	PrintRubiks();
}

//Test Cubes
//bobgybgowgoybrrwybgrogryywyorygrbbogwwogwwryrwworgbbyo
//wywwywoyrggbrywwwgbgrgooogogbwrbbrbbyoorrorywgobyybgry
//ywrbowrbyyrbowoggbwrowyobywyyobwywrgggbrboowogbggrgryr
//byrgbobwboyyrwgbbrowwrygroggogywbwwogbygyrrbwrwoogroyy
//gobbogyrogrogggrybywwoyrworyggbrybrgrbrwowwywoywbbwboy
//bgyoywobbworwyyoywrbgrwyowgbygrbbgwyoowbrrwgoggrrygbor
//yoggyrwbbobgyrowgyyygrgoorgwybwwgrywyoorowrwrbbbwbgrbo
//yrbowoggbwrowyobywyyobwywrgywrbowrbybrboowggorygbggrgr
//ywygwowgrwboobwrygygbrwrowobogobygrbryrbrrgwwoyobybggy
//ygwyyoyyowbgboowrgywrbrrwrrbyogoorrbgbggowroybgbygwbww
//bgobgwogwwoyywryooyrrwgbwgyggbwrbrorgworworybbbyybroyg
//rrrrrrrrrggyyyybyyooyoobwwowgyoowwwwogbwgggygbbbbgowbb  special cube
//rrrrrrrrrbwyyyygoyoowyogyoowywwowwwwobgggggggbbbbboybb  special cube
//grybyoyybrwrgobwwwrrgooobgggowwowryywgbgoyybobbbrwygrr
//yobbbgbrwrgbyrbgyooryowowyyowgbgwrwrggyrwgowbyyworborg
//worgwyobrgwbygbgrbbgryoybwoyborogrwgyrywbbroywggowoyrw
//rggwrrooowgbywowygybrrobwyrorbgroygbgyobyryoybwgwbwgbw Cube tried on real cube and worked from first to last move
//bwbbwwrywboybgrwobooowogboywyggorrrgyyyrrbrbrygggwygwo
//ogrgryryyoybgwrbwoowgrrobowbywbyoywrybgbwrwrggogwogybb//used cube and solved fully


void Rubiks3Sol::Stage1() {
	while ((*ptop&eig) != 0) {
		ShiT();
		if ((*ptop&eig) == 0)
			break;
		RotL();
	}
}

void Rubiks3Sol::Stage2() {
#define op	for (int i=0;i<4;i++){
#define cl	ShiL();}

	while (Comfir(ptop) || (Comfir(pbac) != Comeig(pbac))\
		|| Comthi(ptop) || (Comfir(prig) != Comeig(prig))\
		|| Comfif(ptop) || (Comfir(pfro) != Comeig(pfro))\
		|| Comsev(ptop) || (Comfir(plef) != Comeig(plef))) {
		PrintRubiks();
		op
			if (!Comfif(ptop) && (Comfir(pfro) != Comeig(pfro))) {
				while (!(Comfir(pbot))) {
					Bot();
				}
				Fro();
				Fro();
			}
		cl
		op
			if (!Comfir(pbot)) {
				while (Comfif(pfro) != Comeig(pfro)) {
					Bot();
					ShiR();
				}
				Fro();
				Fro();
			}
		cl
		//No cube on bottom face should be 0 after this
		op
			if (!Comfir(pfro)&&(Comfif(ptop)==Comeig(pfro))) {
				Fro();
				IRig();
				IBot();
				Rig();
				Fro();
				Fro();
			}
		cl
		//next set again ensures bottom isn't 0
		op
			if (!Comfir(pbot)) {
				while (Comfif(pfro) != Comeig(pfro)) {
					Bot();
					ShiR();
				}
				Fro();
				Fro();
			}
		cl
		op
			if (!(Comthi(pfro))) {
				while (!Comthi(pbot)) {
					Bot();
				}
				IRig();
			}
		if (!(Comsev(pfro))) {
			while (!Comsev(pbot)) {
				Bot();
			}
			Lef();
		}
		cl
		//next set again ensures bottom isn't 0
		op
			if (!Comfir(pbot)) {
				while (Comfif(pfro) != Comeig(pfro)) {
					Bot();
					ShiR();
				}
				Fro();
				Fro();
			}
		cl
		op
			if (!Comfif(pfro)) {
				while (Comeig(prig) != Comfir(pbot)) {
					Bot();
					ShiR();
				}
				IFro();
				Rig();
				Fro();
			}
			cl
				//next set again ensures bottom isn't 0
				op
				if (!Comfir(pbot)) {
					while (Comfif(pfro) != Comeig(pfro)) {
						Bot();
						ShiR();
					}
					Fro();
					Fro();
				}
			cl
	}
#undef op
#undef cl
}

void Rubiks3Sol::Stage3() {
#define op	for (int i=0;i<4;i++){
#define cl	ShiL();}
	while (Comzer(ptop) || Comzer(plef) != Comeig(plef) || Comsec(pbac) != Comeig(pbac)\
		|| Comsec(ptop) || Comzer(pbac) != Comeig(pbac) || Comsec(prig) != Comeig(prig)\
		|| Comfou(ptop) || Comzer(prig) != Comeig(prig) || Comsec(pfro) != Comeig(pfro)\
		|| Comsix(ptop) || Comzer(pfro) != Comeig(pfro) || Comsec(plef) != Comeig(plef)) {
		op
			if (!(Comfou(ptop)) && (Comsec(pfro) != Comeig(pfro))) {
				while (!Comfou(pfro) || !Comsix(prig)) {
					Bot();
				}
				IRig();
				IBot();
				Rig();
			}
		cl
			//all improper corner cubes are not on facing top anymore (they may point on side of top corners however)
		op
			op
				if (!(Comzer(pfro))) {
					IFro();
					IBot();
					Fro();
					if (Comsix(pbot) == Comeig(pfro)) {
						Bot();
						Bot();
						Lef();
						IBot();
						ILef();
					}
					else if (Comsix(pbot) == Comeig(plef)) {//
						Bot();
						Bac();
						IBot();
						IBac();
					}
					else if (Comsix(pbot) == Comeig(pbac)) {
						Rig();
						IBot();
						IRig();
					}
					else if (Comsix(pbot) == Comeig(prig)) {
						IBot();
						Fro();
						IBot();
						IFro();
					}
				}
				if (!(Comsec(pfro))) {
					Fro();
					Bot();
					IFro();
					if (Comfou(pbot) == Comeig(pfro)) {
						IBot();
						IBot();
						IRig();
						Bot();
						Rig();
					}
					else if (Comfou(pbot) == Comeig(plef)) {
						Bot();
						IFro();
						Bot();
						Fro();
					}
					else if (Comfou(pbot) == Comeig(pbac)) {
						ILef();
						Bot();
						Lef();
					}
					else if (Comfou(pbot) == Comeig(prig)) {//yes
						IBot();
						IBac();
						Bot();
						Bac();
					}
				}
			cl
		cl//doing this a lot of times gets all upper corner cubes in correct positions
		op//12 combinations to add to this block which may need 3 op/cl to work every time but then stage 3 is done
			op
				op
					if (!Comsec(pbot)) {
						if (Comfou(pfro) == Comeig(pfro)) {
							IRig();
							Bot();
							Rig();
							Bot();
							Bot();
							Lef();
							IBot();
							ILef();
						}
						if (Comfou(pfro) == Comeig(plef)) {
							IRig();
							Bot();
							Rig();
							Bot();
							Bac();
							IBot();
							IBac();
						}
						if (Comfou(pfro) == Comeig(pbac)) {
							IRig();
							Bot();
							Rig();
							Rig();
							IBot();
							IRig();
						}
						if (Comfou(pfro) == Comeig(prig)) {
							IRig();
							Bot();
							Rig();
							IBot();
							Fro();
							IBot();
							IFro();
						}
					}
					if (!Comfou(pfro)) {
						if (Comsix(prig) == Comeig(pfro)) {
							IBot();
							IBot();
							IFro();
							Bot();
							Fro();
						}
						if (Comsix(prig) == Comeig(plef)) {
							ILef();
							Bot();
							Bot();
							Lef();
						}
						if (Comsix(prig) == Comeig(pbac)) {
							IBac();
							Bot();
							Bac();
						}
						if (Comsix(prig) == Comeig(prig)) {
							IBot();
							IRig();
							Bot();
							Rig();
						}
					}
					if (!(Comsix(prig))) {
						if (Comfou(pfro) == Comeig(pfro)) {
							Bot();
							Fro();
							IBot();
							IFro();
						}
						if (Comfou(pfro) == Comeig(plef)) {
							Lef();
							IBot();
							ILef();
						}
						if (Comfou(pfro) == Comeig(pbac)) {
							Bac();
							IBot();
							IBot();
							IBac();
						}
						if (Comfou(pfro) == Comeig(prig)) {
							Bot();
							Bot();
							Rig();
							IBot();
							IRig();//check this one
						}
					}
				cl
			cl
		cl
	}
#undef op
#undef cl
}

void Rubiks3Sol::Stage4() {
#define op	for (int i=0;i<4;i++){
#define cl	ShiL();}
#define spop for (int i=0;i<4;i++){
#define spcl Top();}
	ShiT();
	ShiT();
	while (Comthi(pfro) != Comeig(pfro) || Comsev(pfro) != Comeig(pfro)\
		|| Comthi(plef) != Comeig(plef) || Comsev(plef) != Comeig(plef)\
		|| Comthi(pbac) != Comeig(pbac) || Comsev(pbac) != Comeig(pbac)\
		|| Comthi(prig) != Comeig(prig) || Comsev(prig) != Comeig(prig)) {
		op
			op
				spop
					if (Comfir(pfro) == Comeig(pfro) && Comfif(ptop) == Comeig(prig)) {
						Top();
						Rig();
						ITop();
						IRig();
						ITop();
						IFro();
						Top();
						Fro();
					}
					if (Comfir(pfro) == Comeig(pfro) && Comfif(ptop) == Comeig(plef)) {
						ITop();
						ILef();
						Top();
						Lef();
						Top();
						Fro();
						ITop();
						IFro();
					}
				spcl
			cl//Confirmed no top cubes fit properly into firthi or firsev
			op
				spop
					if ((Comthi(pfro) != Comeig(ptop) && Comsev(prig) != Comeig(ptop))\
					 && (Comthi(pfro) != Comeig(pfro) || Comsev(prig) != Comeig(prig))\
					 && (Comfir(pfro) == Comeig(ptop) || Comfif(ptop)==Comeig(ptop))){
						Top();
						Rig();
						ITop();
						IRig();
						ITop();
						IFro();
						Top();
						Fro();
					}
					if ((Comfif(pfro) != Comeig(ptop) && Comthi(plef) != Comeig(ptop))\
					 && (Comfif(pfro) != Comeig(pfro) || Comthi(plef) != Comeig(plef))\
					 && (Comfir(pfro) == Comeig(ptop) || Comfif(ptop) == Comeig(ptop))) {
						ITop();
						ILef();
						Top();
						Lef();
						Top();
						Fro();
						ITop();
						IFro();
					}
				spcl
			cl
		cl
	}
#undef op
#undef cl
#undef spop for (int i=0;i<4;i++){
#undef spcl Top();}
}

void Rubiks3Sol::Stage5() {
#define spop for (int i=0;i<4;i++){
#define spcl Top();}
	if (Comfir(ptop) != Comeig(ptop) || Comthi(ptop) != Comeig(ptop) || Comfif(ptop) != Comeig(ptop) || Comsev(ptop) != Comeig(ptop)) {
		spop
			if (Comfir(ptop) == Comeig(ptop) && Comsev(ptop) == Comeig(ptop)) {
				Fro();
				Rig();
				Top();
				IRig();
				ITop();
				Rig();
				Top();
				IRig();
				ITop();
				IFro();
				break;//break may cause issue later on and i could just check before if statement if its already solved on top
			}
		spcl
	}
	if (Comfir(ptop) != Comeig(ptop) || Comthi(ptop) != Comeig(ptop) || Comfif(ptop) != Comeig(ptop) || Comsev(ptop) != Comeig(ptop)) {
		spop
			if (Comthi(ptop) == Comeig(ptop) && Comsev(ptop) == Comeig(ptop)) {
				Fro();
				Rig();
				Top();
				IRig();
				ITop();
				IFro();
				break;
			}
		spcl
	}
	if (Comfir(ptop) != Comeig(ptop) || Comthi(ptop) != Comeig(ptop) || Comfif(ptop) != Comeig(ptop) || Comsev(ptop) != Comeig(ptop)) {
			Fro();
			Rig();
			Top();
			IRig();
			ITop();
			IFro();
			ShiL();
			ShiL();
			Fro();
			Rig();
			Top();
			IRig();
			ITop();
			Rig();
			Top();
			IRig();
			ITop();
			IFro();
	}
#undef spop for (int i=0;i<4;i++){
#undef spcl Top();}
}

void Rubiks3Sol::Stage6() {
#define op	for (int i=0;i<4;i++){
#define cl	ShiL();}
#define spop for (int i=0;i<4;i++){
#define spcl Top();}
	while (Comfir(pfro) != Comeig(pfro) || Comfir(plef) != Comeig(plef)\
		|| Comfir(pbac) != Comeig(pbac) || Comfir(prig) != Comeig(prig)) {
		spop
			if (Comfir(pfro) == Comeig(pfro) && Comfir(plef) == Comeig(plef)\
				&& Comfir(pbac) == Comeig(pbac) && Comfir(prig) == Comeig(prig)) {
				break;
			}
		spcl
			if (Comfir(pfro) == Comeig(pfro) && Comfir(plef) == Comeig(plef)\
				&& Comfir(pbac) == Comeig(pbac) && Comfir(prig) == Comeig(prig)) {
				break;
			}//after this if still in loop then four cubes aren't lined up as wanted yet
		op
			spop
			if (Comfir(prig) == Comeig(prig) && Comfir(pbac) == Comeig(pbac)) {
				Rig();
				Top();
				IRig();
				Top();
				Rig();
				Top();
				Top();
				IRig();
				Top();
				break;
			}
		spcl
			if (Comfir(pfro) == Comeig(pfro) && Comfir(plef) == Comeig(plef)\
				&& Comfir(pbac) == Comeig(pbac) && Comfir(prig) == Comeig(prig)) {
				break;
			}
		cl//takes care of final case
			if (Comfir(pfro) == Comeig(pfro) && Comfir(plef) == Comeig(plef)\
				&& Comfir(pbac) == Comeig(pbac) && Comfir(prig) == Comeig(prig)) {
				break;//this affects block below as well
			}
		op
			spop
				if (Comfir(pfro) == Comeig(pfro) && Comfir(pbac) == Comeig(pbac)) {
					Rig();
					Top();
					IRig();
					Top();
					Rig();
					Top();
					Top();
					IRig();
					ShiL();
					Rig();
					Top();
					IRig();
					Top();
					Rig();
					Top();
					Top();
					IRig();
					Top();
					break;
				}
			spcl
			if (Comfir(pfro) == Comeig(pfro) && Comfir(plef) == Comeig(plef)\
				&& Comfir(pbac) == Comeig(pbac) && Comfir(prig) == Comeig(prig)) {
				break;//this affects block below as well
			}
		cl
	}
#undef op
#undef cl
#undef spop for (int i=0;i<4;i++){
#undef spcl Top();}
}

void Rubiks3Sol::Stage7() {//doesn't work yet
#define op	for (int i=0;i<4;i++){
#define cl	ShiL();}
	while (!((Comfou(ptop) == Comeig(ptop)  ||  Comfou(ptop) == Comeig(pfro)  \
		  || Comfou(ptop)  == Comeig(prig)) && (Comsec(pfro) == Comeig(pfro)  \
		  || Comsec(pfro)  == Comeig(ptop)  ||  Comsec(pfro) == Comeig(prig)) \
		  &&(Comzer(prig)  == Comeig(pfro)  ||  Comzer(prig) == Comeig(ptop)  \
		  || Comzer(prig)  == Comeig(prig)) && (Comsix(ptop) == Comeig(ptop)  \
		  || Comsix(ptop)  == Comeig(pfro)  ||  Comsix(ptop) == Comeig(plef)) \
		  &&(Comsec(plef)  == Comeig(plef)  ||  Comsec(plef) == Comeig(ptop)  \
		  || Comsec(plef)  == Comeig(pfro)) && (Comzer(pfro) == Comeig(pfro)  \
		  || Comzer(pfro)  == Comeig(ptop)  ||  Comzer(pfro) == Comeig(plef)))) {
		op //case where one cube is in right position wrong orientation
			if (( Comfou(ptop) == Comeig(ptop)  ||  Comfou(ptop) == Comeig(pfro)  \
			  ||  Comfou(ptop) == Comeig(prig)) && (Comsec(pfro) == Comeig(pfro)  \
			  ||  Comsec(pfro) == Comeig(ptop)  ||  Comsec(pfro) == Comeig(prig)) \
			  && (Comzer(prig) == Comeig(ptop)  ||  Comzer(prig) == Comeig(pfro)  \
			  ||  Comzer(prig) == Comeig(prig)))								     {
				while (!((Comsix(ptop) == Comeig(ptop)  ||  Comsix(ptop) == Comeig(pfro)  \
					   || Comsix(ptop) == Comeig(plef)) && (Comsec(plef) == Comeig(pfro)  \
					   || Comsec(plef) == Comeig(ptop)  ||  Comsec(plef) == Comeig(plef)) \
					   &&(Comzer(pfro) == Comeig(pfro)  ||  Comzer(pfro) == Comeig(ptop)  \
					   || Comzer(pfro) == Comeig(plef))))								  {
					Top();
					Rig();
					ITop();
					ILef();
					Top();
					IRig();
					ITop();
					Lef();
				}
				break;
			}
		cl
			if ((Comfou(ptop) == Comeig(ptop) ||  Comfou(ptop) == Comeig(pfro) \
			  || Comfou(ptop) == Comeig(prig))&& (Comsec(pfro) == Comeig(pfro) \
			  || Comsec(pfro) == Comeig(ptop) ||  Comsec(pfro) == Comeig(prig))\
			  &&(Comzer(prig) == Comeig(pfro) ||  Comzer(prig) == Comeig(ptop) \
			  || Comzer(prig) == Comeig(prig))&& (Comsix(ptop) == Comeig(ptop) \
			  || Comsix(ptop) == Comeig(pfro) ||  Comsix(ptop) == Comeig(plef))\
			  &&(Comsec(plef) == Comeig(plef) ||  Comsec(plef) == Comeig(ptop) \
			  || Comsec(plef) == Comeig(pfro))&& (Comzer(pfro) == Comeig(pfro) \
			  || Comzer(pfro) == Comeig(ptop) ||  Comzer(pfro) == Comeig(plef))) {
				break;
			}
		op //ensures 1 cube is in correct position for next round
			while (!((Comsix(ptop) == Comeig(ptop)  ||  Comsix(ptop) == Comeig(pfro) \
				  ||  Comsix(ptop) == Comeig(plef)) && (Comsec(plef) == Comeig(pfro) \
				  ||  Comsec(plef) == Comeig(ptop)  ||  Comsec(plef) == Comeig(plef))\
				  && (Comzer(pfro) == Comeig(pfro)  ||  Comzer(pfro) == Comeig(ptop) \
				  ||  Comzer(pfro) == Comeig(plef))))								 {
				Top();
				Rig();
				ITop();
				ILef();
				Top();
				IRig();
				ITop();
				Lef();
			}
			ShiL();
			break;
		cl
	}
#undef op
#undef cl
}

void Rubiks3Sol::Stage8() {
#define spop for (int i=0;i<4;i++){
#define spcl Top();}
	spop//reliant on stage7
		while (Comfou(ptop) != Comeig(ptop)) {
			IRig();
			IBot();
			Rig();
			Bot();
		}
	spcl
#undef spop for (int i=0;i<4;i++){
#undef spcl Top();}
}

inline void Rubiks3Sol::Rot(puint pface) {
	*pface = (((*pface&(zer | fir | sec | thi | fou | fif)) >> (2 * dCu)) | ((*pface&(six | sev)) << (6 * dCu)) | (*pface&eig));
}

inline void Rubiks3Sol::IRot(puint pface) {
	*pface = (((*pface&(sec | thi | fou | fif | six | sev)) << (2 * dCu)) | ((*pface&(zer | fir)) >> (6 * dCu)) | (*pface&eig));
}

inline void Rubiks3Sol::DRot(puint pface) {
	*pface = (((*pface&(zer | fir | sec | thi)) >> (4 * dCu)) | ((*pface&(fou | fif | six | sev)) << (4 * dCu)) | (*pface&eig));
}

inline uint Rubiks3Sol::Comzer(puint pface) {
	return ((*pface&zer) >> (8 * dCu));
}

inline uint Rubiks3Sol::Comfir(puint pface) {
	return ((*pface&fir) >> (7 * dCu));
}

inline uint Rubiks3Sol::Comsec(puint pface) {
	return ((*pface&sec) >> (6 * dCu));
}

inline uint Rubiks3Sol::Comthi(puint pface) {
	return ((*pface&thi) >> (5 * dCu));
}

inline uint Rubiks3Sol::Comfou(puint pface) {
	return ((*pface&fou) >> (4 * dCu));
}

inline uint Rubiks3Sol::Comfif(puint pface) {
	return ((*pface&fif) >> (3 * dCu));
}

inline uint Rubiks3Sol::Comsix(puint pface) {
	return ((*pface&six) >> (2 * dCu));
}

inline uint Rubiks3Sol::Comsev(puint pface) {
	return ((*pface&sev) >> (1 * dCu));
}

inline uint Rubiks3Sol::Comeig(puint pface) {
	return (*pface&eig);
}
