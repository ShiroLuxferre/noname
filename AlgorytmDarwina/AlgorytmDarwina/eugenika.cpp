#include <iostream>
#include <random>
#include <cassert>
#include <algorithm>

#include "struktury.h"
#include "eugenika.h"


int losowanie(int a)
{
	std::random_device generator;
	std::uniform_int_distribution<int> los(1, a);
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
	if (n == 0)
		return chromek;
	else
	{
		n--;
		chromek = chromek->pNextChromosom;
		return znajdz_enty_chromosom(n, chromek);
	}
}

int pekniecie_genu(int osA, Osobnik *&opis)
{
	auto o = opis->pNext;
	int i = 1;
	//debug(o);
	o = szukanieOsobnika(osA, opis);
	int pekniecie_genu_rodzica = losowanie(o->ilosc_genu);
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

	while (ile_par != 0)
	{
		osA = losowanie(ile_osobnikow);
		do
		{
			osB = losowanie(ile_osobnikow);
		} while (osA == osB);
		ile_par--;

		pekniecie_genu_osobnika_A = pekniecie_genu(osA, osoba);
		pekniecie_genu_osobnika_B = pekniecie_genu(osB, osoba);

		krzyzowanie_genow(pekniecie_genu_osobnika_A, osA, pekniecie_genu_osobnika_B, osB, osoba);
	}
	std::cout << "Zakonczono noc Beytein" << std::endl;
}

void usunZleDopasowane(Osobnik *& oss, double w) {
	while (oss && oss->wspolczynnik_Naturalny < w)
	{
		auto os = oss->pNext;
		delete os;
		os = os;
	}
	if (!oss)
	{
		return;
	}
	for (Osobnik * p = oss; p->pNext != nullptr; )
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
}