/** @file */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "struktury.h"
#include "wspolczynnik.h"
#include "wczytywanie_pliku.h"

void addGen(Generacja*& pPokolenie, int p)
{
	for (int i = 0; i < p; i++)
	{
		pPokolenie = new Generacja{ nullptr, nullptr };
	}
}

int wczytajGeneracje(Generacja*& pPokolenie, const std::string & nazwa_pliku)
{
	int ilosc_osobnikow = 0, gen = 0, ilosc_genu;
	std::string caly_chromosom;
	std::ifstream plik(nazwa_pliku);
	
	if (!plik)
		std::cout << "Blad pliku" << std::endl;
	while (true)
	{
		auto pOsoba = pPokolenie->pNaPoczatekGenercji;
		Chromosomy *pChromosom = nullptr;
		/* 
		wczytywanie chromosomu do zmiennej typu string, nastepnie  dzielenie jej na pojedyncze geny 
		*/
		if (!getline(plik, caly_chromosom))
		{
			break;
		}
		ilosc_osobnikow++;
		ilosc_genu = 0;
		std::istringstream iss(caly_chromosom);
		while (true) {
			if (!(iss >> gen))
			{
				break;
			}
			ilosc_genu++;
			if (ilosc_genu == 1) 
			{
				pChromosom = new Chromosomy{ gen, nullptr };
			}
			else {
				auto ch = pChromosom;
				while (ch->pNextChromosom)
					ch = ch->pNextChromosom;
				ch->pNextChromosom = new Chromosomy{ gen, nullptr };
			}
		}

		if (not pOsoba)
		{
			pOsoba = new Osobnik{ ilosc_genu, ilosc_osobnikow, fukncja_oceny(pChromosom),pChromosom, nullptr };
			pPokolenie = new Generacja{ pOsoba, nullptr };
		}
		else {
			auto o = pOsoba;
			while (o->pNext)
				o = o->pNext;
			o->pNext = new Osobnik{ ilosc_genu, ilosc_osobnikow, fukncja_oceny(pChromosom),pChromosom, nullptr };
		}
	}

	plik.close();
	std::cout << "Wczytano grupe badawcza" << std::endl;
	return ilosc_osobnikow;
}