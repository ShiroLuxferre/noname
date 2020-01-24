/** @file */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "struktury.h"
#include "wspolczynnik.h"
#include "wczytywanie_pliku.h"


int wczytajGeneracje(Osobnik*& pOsoba, Chromosomy*& pChromek, Generacja*& pPokolenie, const std::string & nazwa_pliku)
{
	int ilosc_osobnikow = 0, gen = 0, ilosc_genu;
	std::string caly_chromosom;
	std::ifstream plik(nazwa_pliku);

	if (!plik)
		std::cout << "Blad pliku" << std::endl;
	while (true)
	{

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
			if (ilosc_genu == 1) {
				pChromek = new Chromosomy{ gen, nullptr };
			}
			else {
				auto ch = pChromek;
				while (ch->pNextChromosom)
					ch = ch->pNextChromosom;
				ch->pNextChromosom = new Chromosomy{ gen, nullptr };
			}
		}

		if (not pOsoba)
		{
			pOsoba = new Osobnik{ ilosc_genu, fukncja_oceny(pChromek),pChromek, nullptr };
			pPokolenie = new Generacja{ pOsoba, nullptr };
		}
		else {
			auto o = pOsoba;
			while (o->pNext)
				o = o->pNext;
			o->pNext = new Osobnik{ ilosc_genu, fukncja_oceny(pChromek),pChromek, nullptr };
		}
	}

	plik.close();
	std::cout << "Wczytano grupe badawcza" << std::endl;
	return ilosc_osobnikow;
}