#include <iostream>
#include <random>
#include <cassert>
#include <algorithm>

#include "struktury.h"
#include "wspolczynnik.h"
#include "eugenika.h"


int losowanie(int a, int b)
{
	std::random_device generator;
	std::uniform_int_distribution<int> los(a, b);
	int wynik = los(generator);
	//debug(wynik);
	return wynik;
}

Osobnik * szukanieOsobnika(typ os, Osobnik * o)
{
	while (true)
	{
		if (o == nullptr || o->liczba_porzadkowa == os)
			break;
		o = o->pNext;
	}
	return o;
}

Chromosomy * znajdz_enty_chromosom(int n, Chromosomy *chromek)
{
	while (chromek&&n>(-1))
	{
		if (n == 0)
			return chromek;
		else
		{
			chromek = chromek->pNextChromosom;
			if (chromek == nullptr)
				break;
			n--;
		}
	}
}

int pekniecie_genu(int osA, Osobnik *&opis)
{
	auto o = opis->pNext;
	int i = 1;
	//debug(o);
	o = szukanieOsobnika(osA, opis);
	int pekniecie_genu_rodzica = losowanie(2, (o->ilosc_genu)-1);
	return pekniecie_genu_rodzica;
}

void krzyzowanie_genow(int pekniecie1, int osA, int pekniecie2, int osB, Osobnik *& osoba)
{
	auto o1 = osoba;
	//debug(o1);
	auto chromek1 = o1->lista_Chromosomow;
	//debug(o1->lista_Chromosomow);
	while (o1)
	{
		if (o1->liczba_porzadkowa == osA)
			break;
		chromek1 = o1->lista_Chromosomow;
		o1 = o1->pNext;
	}
	//debug(o1);
	auto ch1 = znajdz_enty_chromosom(pekniecie1, chromek1);
	auto o2 = osoba;
	auto chromek2 = o2->lista_Chromosomow;
	while (o2)
	{
		if (o2->liczba_porzadkowa == osA)
			break;
		chromek2 = o2->lista_Chromosomow;
		o2 = o2->pNext;
		//debug(chromek2);
	}

	//auto ch1 = znajdz_enty_chromosom(pekniecie1, chromek1);
	auto ch2 = znajdz_enty_chromosom(pekniecie2, chromek2);

	std::swap(ch1->pNextChromosom, ch2->pNextChromosom); // zamiana miejscami
	
}


void doborOsobnikow(int ile_par, int ile_osobnikow, Osobnik *& osoba)
{
	int osA, osB, pekniecie_genu_osobnika_A, pekniecie_genu_osobnika_B;

	while (ile_par != 0 )
	{
		osA = losowanie(1, ile_osobnikow);
		do
		{
			osB = losowanie(1, ile_osobnikow);
		} while (osA == osB);
		ile_par--;

		pekniecie_genu_osobnika_A = pekniecie_genu(osA, osoba);
		pekniecie_genu_osobnika_B = pekniecie_genu(osB, osoba);

		krzyzowanie_genow(pekniecie_genu_osobnika_A, osA, pekniecie_genu_osobnika_B, osB, osoba);
	}

	mierzenieDopasowania(osoba);
	std::cout << "Zakonczono noc Beytein" << std::endl;
}

void usunZleDopasowane(Osobnik *& osoba, Stado *& grup, double w)
{
	while (osoba && osoba->wspolczynnik_Naturalny < w)
	{
		auto os = osoba->pNext;
		if (osoba == grup->pierwszy_w_generacji)
		{
			grup->pierwszy_w_generacji = os;
			grup->ilosc_osobnikow_w_grupie--;
		}
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
			if (osoba == grup->pierwszy_w_generacji)
			{
				grup->pierwszy_w_generacji = p;
				grup->ilosc_osobnikow_w_grupie--;
			}
		}
		else
		{
			p = p->pNext;
		}
	}
	std::cout << "Nastaly mrozy, Zima nadeszla" << std::endl;
}

void klonowanie(Stado *& grup, Osobnik *& opis, double wspolczynnikRozmnazania, double wspolczynikWymierania)
{
	auto ile_pozostalo_osobnikow = grup->ilosc_osobnikow_w_grupie;
	Stado *generacja = new Stado{0, nullptr, nullptr};
	int ilosc_osobnikow = 0, liczba_porzadkowa=1;

	while (ile_pozostalo_osobnikow)
	{
		if (opis->wspolczynnik_Naturalny > wspolczynikWymierania && opis->wspolczynnik_Naturalny < wspolczynnikRozmnazania)
		{
			auto opis_gen_New = opis;
			while (opis->pNext)
			{
				opis = opis->pNext;
			}
			opis->pNext = new Osobnik;
			opis_gen_New->ilosc_genu=opis->ilosc_genu;
			opis_gen_New->liczba_porzadkowa = liczba_porzadkowa;
			opis_gen_New->wspolczynnik_Naturalny = 0;
			opis_gen_New->lista_Chromosomow = opis->lista_Chromosomow;
			if (liczba_porzadkowa == 1)
			{
				generacja->pierwszy_w_generacji = opis;
				//debug(generacja->pierwszy_w_generacji);
			}
			ilosc_osobnikow++;
			liczba_porzadkowa++;
		}
 		opis = opis->pNext;
		generacja->ilosc_osobnikow_w_grupie = ilosc_osobnikow;
		
		ile_pozostalo_osobnikow--;
	}
	std::cout << "Przeminelo Yule, przetrwali najlepsi" << std::endl;
}


void narodziny(Stado *& grup, Osobnik *& opis, double wspolczynnikRozmnazania, double wspolczynikWymierania)
{
	auto ile_pozostalo_osobnikow = grup->ilosc_osobnikow_w_grupie;
	int ilosc_osobnikow = grup->ilosc_osobnikow_w_grupie, liczba_porzadkowa = grup->ilosc_osobnikow_w_grupie;

	while (ile_pozostalo_osobnikow)
	{
		if (opis->wspolczynnik_Naturalny > wspolczynnikRozmnazania)
		{
			for (int i = 0; i < 2; i++)
			{
				auto opis_gen_New = opis;
				while (opis->pNext)
				{
					opis = opis->pNext;
				}
				opis->pNext = new Osobnik;
				opis_gen_New->ilosc_genu = opis->ilosc_genu;
				opis_gen_New->liczba_porzadkowa = liczba_porzadkowa;
				opis_gen_New->wspolczynnik_Naturalny = 0;
				opis_gen_New->lista_Chromosomow = opis->lista_Chromosomow;
				ilosc_osobnikow++;
				liczba_porzadkowa++;
			}
			opis = opis->pNext;
			grup->ilosc_osobnikow_w_grupie = ilosc_osobnikow;

		}
		ile_pozostalo_osobnikow--;
	}
	std::cout << "Nastala Ostara" << std::endl;
}
