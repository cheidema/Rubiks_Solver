#include "Rubiks3.h"

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


Rubiks3::Rubiks3()
{

	for (int i = 0;i < 6;i++) {
		sid[i] = 0;
		dic[i] = '_';
	}
	pfro = &sid[0];
	plef = &sid[1];
	pbac = &sid[2];
	prig = &sid[3];
	ptop = &sid[4];
	pbot = &sid[5];
}

void Rubiks3::Fro() {
	int temp = *plef & (sec | thi | fou);
	Rot(pfro);
	*plef = (*plef & (zer | fir | fif | six | sev | eig)) | ((*pbot & (zer | fir | sec)) >> (2 * dCu));
	*pbot = (*pbot & (thi | fou | fif | six | sev | eig)) | ((*prig & zer) >> (2 * dCu)) | ((*prig & (six | sev)) << (6 * dCu));
	*prig = (*prig & (fir | sec | thi | fou | fif | eig)) | ((*ptop & six) << (6 * dCu)) | ((*ptop & (fou | fif)) >> (2 * dCu));
	*ptop = (*ptop & (zer | fir | sec | thi | sev | eig)) | (temp >> (2 * dCu));
}

void Rubiks3::IFro() {
	int temp = *plef & (sec | thi | fou);
	IRot(pfro);
	*plef = (*plef & (zer | fir | fif | six | sev | eig)) | ((*ptop & (fou | fif | six)) << (2 * dCu));
	*ptop = (*ptop & (zer | fir | sec | thi | sev | eig)) | ((*prig & zer) >> (6 * dCu)) | ((*prig & (six | sev)) << (2 * dCu));
	*prig = (*prig & (fir | sec | thi | fou | fif | eig)) | ((*pbot & sec) << (2 * dCu)) | ((*pbot & (zer | fir)) >> (6 * dCu));
	*pbot = (*pbot & (thi | fou | fif | six | sev | eig)) | (temp << (2 * dCu));
}

void Rubiks3::Lef() {
	int temp = *pfro & (zer | six | sev);
	Rot(plef);
	*pfro = (*pfro & (fir | sec | thi | fou | fif | eig)) | (*ptop & (zer | six | sev));
	*ptop = (*ptop & (fir | sec | thi | fou | fif | eig)) | ((*pbac & fou) << (4 * dCu)) | ((*pbac & (sec | thi)) >> (4 * dCu));
	*pbac = (*pbac & (zer | fir | fif | six | sev | eig)) | ((*pbot & zer) >> (4 * dCu)) | ((*pbot & (six | sev)) << (4 * dCu));
	*pbot = (*pbot & (fir | sec | thi | fou | fif | eig)) | temp;
}

void Rubiks3::ILef() {
	int temp = *pfro & (zer | six | sev);
	IRot(plef);
	*pfro = (*pfro & (fir | sec | thi | fou | fif | eig)) | (*pbot & (zer | six | sev));
	*pbot = (*pbot & (fir | sec | thi | fou | fif | eig)) | ((*pbac & fou) << (4 * dCu)) | ((*pbac & (sec | thi)) >> (4 * dCu));
	*pbac = (*pbac & (zer | fir | fif | six | sev | eig)) | ((*ptop & zer) >> (4 * dCu)) | ((*ptop & (six | sev)) << (4 * dCu));
	*ptop = (*ptop & (fir | sec | thi | fou | fif | eig)) | temp;
}

void Rubiks3::Bac() {
	int temp = *plef&(zer | six | sev);
	Rot(pbac);
	*plef = (*plef & (fir | sec | thi | fou | fif | eig)) | ((*ptop & sec) << (2 * dCu)) | ((*ptop & (zer | fir)) >> (6 * dCu));
	*ptop = (*ptop & (thi | fou | fif | six | sev | eig)) | ((*prig & (sec | thi | fou)) << (2 * dCu));
	*prig = (*prig & (zer | fir | fif | six | sev | eig)) | ((*pbot & (fou | fif | six)) << (2 * dCu));
	*pbot = (*pbot & (zer | fir | sec | thi | sev | eig)) | ((temp&zer) >> (6 * dCu)) | ((temp&(six | sev)) << (2 * dCu));
}

void Rubiks3::IBac() {
	int temp = *plef&(zer | six | sev);
	IRot(pbac);
	*plef = (*plef & (fir | sec | thi | fou | fif | eig)) | ((*pbot & six) << (6 * dCu)) | ((*pbot & (fou | fif)) >> (2 * dCu));
	*pbot = (*pbot & (zer | fir | sec | thi | sev | eig)) | ((*prig & (sec | thi | fou)) >> (2 * dCu));
	*prig = (*prig & (zer | fir | fif | six | sev | eig)) | ((*ptop & (zer | fir | sec)) >> (2 * dCu));
	*ptop = (*ptop & (thi | fou | fif | six | sev | eig)) | ((temp&zer) >> (2 * dCu)) | ((temp&(six | sev)) << (6 * dCu));
}

void Rubiks3::Rig() {
	int temp = *pfro & (sec | thi | fou);
	Rot(prig);
	*pfro = (*pfro & (zer | fir | fif | six | sev | eig)) | (*pbot & (sec | thi | fou));
	*pbot = (*pbot & (zer | fir | fif | six | sev | eig)) | ((*pbac & zer) >> (4 * dCu)) | ((*pbac & (six | sev)) << (4 * dCu));
	*pbac = (*pbac & (fir | sec | thi | fou | fif | eig)) | ((*ptop & fou) << (4 * dCu)) | ((*ptop & (sec | thi)) >> (4 * dCu));
	*ptop = (*ptop & (zer | fir | fif | six | sev | eig)) | temp;
}

void Rubiks3::IRig() {
	int temp = *pfro & (sec | thi | fou);
	IRot(prig);
	*pfro = (*pfro & (zer | fir | fif | six | sev | eig)) | (*ptop & (sec | thi | fou));
	*ptop = (*ptop & (zer | fir | fif | six | sev | eig)) | ((*pbac & zer) >> (4 * dCu)) | ((*pbac & (six | sev)) << (4 * dCu));
	*pbac = (*pbac & (fir | sec | thi | fou | fif | eig)) | ((*pbot & fou) << (4 * dCu)) | ((*pbot & (sec | thi)) >> (4 * dCu));
	*pbot = (*pbot & (zer | fir | fif | six | sev | eig)) | temp;
}

void Rubiks3::Top() {
	int temp = *pfro&(zer | fir | sec);
	Rot(ptop);
	*pfro = (*pfro & (thi | fou | fif | six | sev | eig)) | (*prig & (zer | fir | sec));
	*prig = (*prig & (thi | fou | fif | six | sev | eig)) | (*pbac & (zer | fir | sec));
	*pbac = (*pbac & (thi | fou | fif | six | sev | eig)) | (*plef & (zer | fir | sec));
	*plef = (*plef & (thi | fou | fif | six | sev | eig)) | temp;
}

void Rubiks3::ITop() {
	int temp = *pfro&(zer | fir | sec);
	IRot(ptop);
	*pfro = (*pfro & (thi | fou | fif | six | sev | eig)) | (*plef & (zer | fir | sec));
	*plef = (*plef & (thi | fou | fif | six | sev | eig)) | (*pbac & (zer | fir | sec));
	*pbac = (*pbac & (thi | fou | fif | six | sev | eig)) | (*prig & (zer | fir | sec));
	*prig = (*prig & (thi | fou | fif | six | sev | eig)) | temp;
}

void Rubiks3::Bot() {
	int temp = *pfro&(fou | fif | six);
	Rot(pbot);
	*pfro = (*pfro & (zer | fir | sec | thi | sev | eig)) | (*plef & (fou | fif | six));
	*plef = (*plef & (zer | fir | sec | thi | sev | eig)) | (*pbac & (fou | fif | six));
	*pbac = (*pbac & (zer | fir | sec | thi | sev | eig)) | (*prig & (fou | fif | six));
	*prig = (*prig & (zer | fir | sec | thi | sev | eig)) | temp;
}

void Rubiks3::IBot() {
	int temp = *pfro&(fou | fif | six);
	IRot(pbot);
	*pfro = (*pfro & (zer | fir | sec | thi | sev | eig)) | (*prig & (fou | fif | six));
	*prig = (*prig & (zer | fir | sec | thi | sev | eig)) | (*pbac & (fou | fif | six));
	*pbac = (*pbac & (zer | fir | sec | thi | sev | eig)) | (*plef & (fou | fif | six));
	*plef = (*plef & (zer | fir | sec | thi | sev | eig)) | temp;
}

void Rubiks3::ShiL() {
	IRot(ptop);
	Rot(pbot);
	puint ptemp = pfro;
	pfro = plef;
	plef = pbac;
	pbac = prig;
	prig = ptemp;
}

void Rubiks3::ShiR() {
	Rot(ptop);
	IRot(pbot);
	puint ptemp = pfro;
	pfro = prig;
	prig = pbac;
	pbac = plef;
	plef = ptemp;
}

void Rubiks3::ShiT() {
	Rot(plef);
	IRot(prig);
	DRot(pbot);
	DRot(pbac);
	puint ptemp = pfro;
	pfro = ptop;
	ptop = pbac;
	pbac = pbot;
	pbot = ptemp;

}

void Rubiks3::ShiB() {
	IRot(plef);
	Rot(prig);
	DRot(ptop);
	DRot(pbac);
	puint ptemp = pfro;
	pfro = pbot;
	pbot = pbac;
	pbac = ptop;
	ptop = ptemp;
}

void Rubiks3::RotL() {
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
}

void Rubiks3::RotR() {
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
}

void Rubiks3::InputToCube()
{
	std::string rawinput;

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

void Rubiks3::PrintRubiks()
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

void Rubiks3::Shuffle100()
{
	uint rando=0;
	srand(time(0));
	for (uint i = 0;i < 100;i++) {
		rando = (rand() % 12)+1;
		if (rando == 1) {
			Fro();
		}
		else if (rando == 2) {
			IFro();
		}
		else if (rando == 3) {
			Lef();
		}
		else if (rando == 4) {
			ILef();
		}
		else if (rando == 5) {
			Bac();
		}
		else if (rando == 6) {
			IBac();
		}
		else if (rando == 7) {
			Rig();
		}
		else if (rando == 8) {
			IRig();
		}
		else if (rando == 9) {
			Top();
		}
		else if (rando == 10) {
			ITop();
		}
		else if (rando == 11) {
			Bot();
		}
		else if (rando == 12) {
			IBot();
		}
	}
}

char Rubiks3::Getdic(int index)
{
	return dic[index];
}

char Rubiks3::NumToColour(puint pface, uint pos) {
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

	if (((*pface >> shift) & 7) == 0)
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

inline void Rubiks3::AddToDic(char newent)
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

inline void Rubiks3::Rot(puint pface) {
	*pface = (((*pface&(zer | fir | sec | thi | fou | fif)) >> (2 * dCu)) | ((*pface&(six | sev)) << (6 * dCu)) | (*pface&eig));
}
inline void Rubiks3::IRot(puint pface) {
	*pface = (((*pface&(sec | thi | fou | fif | six | sev)) << (2 * dCu)) | ((*pface&(zer | fir)) >> (6 * dCu)) | (*pface&eig));
}
inline void Rubiks3::DRot(puint pface) {
	*pface = (((*pface&(zer | fir | sec | thi)) >> (4 * dCu)) | ((*pface&(fou | fif | six | sev)) << (4 * dCu)) | (*pface&eig));
}