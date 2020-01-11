#include <iostream>
#include <string>
#include <fstream>
#include <sstream>



#include "struktury.h"
#include "wczytywanie_pliku.h"
#include "pokaz_obecna_generacje.h"
#include "wspolczynnik.h"
#include "eugenika.h"

/* 
void usunZleDopasowane(Osobnik *& osoba, double w) {
	while (osoba && osoba->wspolczynnik_Naturalny < w)
	{
		auto os = osoba->pNext;
		delete osoba;
		osoba = os;
	}
	if (!osoba)
	{
		return;
	}
	for (Osobnik * p = osoba; p->pNext != nullptr; )
	{
		if (p->pNext->wspolczynnik_Naturalny < w)
		{
			Osobnik * nowy = p->pNext->pNext;
			delete p->pNext;
			p->pNext = nowy;
		}
		else
		{
			p = p->pNext;
		}
	}
} */


int main()
{
	double wspolczynnik_rozmanrzania = 0.75;
	double wspolczynnik_wymierania = 0.25;
	int wspolczynnik_k = 3;

	std::string nazwa_pliku = "Homo Sovieticus - generacja 0.txt";
	Osobnik *osoba = nullptr;
	Chromosomy *chromek = nullptr;
	int ilosc_osobnikow = wczytajGeneracje(osoba, chromek, nazwa_pliku);
	
	mierzenieDopasowania(osoba);
	
	doborOsobnikow(wspolczynnik_k, ilosc_osobnikow, osoba);
	wyswietlPopulacje(osoba);
	std::cout << std::endl;
	usunZleDopasowane(osoba, wspolczynnik_wymierania);
	std::cout << std::endl;
	wyswietlPopulacje(osoba);
}

/*

Spis funkcji algorytmu
void opcje()
{
	int N = 20;

	for (int i = 0; i < N + 3; i++)
	{
		if (i == 0)std::cout << std::setw(1) << "+";
		std::cout << std::setw(1) << "==";
		if (i == (M / 2))std::cout << std::setw(1) << " Spis funkcji ";
		if (i == (N - 1))std::cout << std::endl;
	}
	std::cout << std::setw(1) << "| - 'i' plik wejsciowy z populacja" << std::endl;
	std::cout << std::setw(1) << "| - 'o' plik wyjsciowy z populacja" << std::endl;
	std::cout << std::setw(1) << "| - 'w' wspolczynnik wymierania w E [0, 1]" << std::endl;
	std::cout << std::setw(1) << "| - 'r' wspolczynnik rozmnazania r E [0, 1]" << std::endl;
	std::cout << std::setw(1) << "| - 'p' liczba pokolen p" << std::endl;
	std::cout << std::setw(1) << "| - 'k' liczba k par osobnikow losowanych do krzyzowania" << std::endl;
	for (int i = 0; i < 4 * (N / 3) + 4; i++)
	{
		if (i == 0)std::cout << std::setw(1) << "+";
		std::cout << std::setw(1) << "==";
	}
	std::cout << std::endl;
}
//wybieranie opcji
void menu()
{
	char przelacznik;
	bool Q = true;
	do
	{
	opcje();
	switch (przelacznik)
	{
	case 'i':

	default:
		break;
	}
	while (Q);


void klonowanie(BadanaGrupa *grup, OpisOsobnika *& opis, double wspolczynnikRozmnazania, double wspolczynikWymierania)
{
	auto opis_gen_old = opis;
	auto g = grup;
	BadanaGrupa grupa;
	grup = grup->pNext;
	int ilosc_osobnikow = 0;
	while (true)
	{

		BadanaGrupa *generacja = new BadanaGrupa;

		if (opis->wspoczynnikNaturalny < wspolczynikWymierania && opis->wspoczynnikNaturalny > wspolczynnikRozmnazania)
		{
			auto opis_gen_New = opis;
			while (opis->pNextOsobnik)
			{
				opis = opis->pNextOsobnik;
			}
			opis->pNextOsobnik = new OpisOsobnika;
			opis_gen_New->iloscGenow;
			opis_gen_New->liczba_porzadkowa;
			opis_gen_New->wspoczynnikNaturalny = 0;
			opis_gen_New->lCh = nullptr;
			grupa.lOs = opis_gen_New->pNextOsobnik;
			ilosc_osobnikow++;
		}
		opis = opis->pNextOsobnik;
		grupa.liczba_osobnikow = ilosc_osobnikow;
	}
}


*/
