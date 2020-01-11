#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "struktury.h"
#include "wczytywanie_pliku.h"


int wczytajGeneracje(Osobnik*& osoba, Chromosomy*&chromek, const std::string & nazwa_pliku)
{
	int ilosc_osobnikow = 0, gen = 0, ilosc_genu;
	std::string caly_chromosom;
	std::ifstream plik(nazwa_pliku);

	if (!plik)
		std::cout << "Blad pliku" << std::endl;
	while (true)
	{

		/* wczytywanie chromosomu do zmiennej typu string, nastepnie  dzielenie jej na pojedyncze geny */
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
				chromek = new Chromosomy{ gen, nullptr };
			}
			else {
				auto ch = chromek;
				while (ch->pNextChromosom)
					ch = ch->pNextChromosom;
				ch->pNextChromosom = new Chromosomy{ gen, nullptr };
			}
		}

		if (not osoba)
			osoba = new Osobnik{ ilosc_genu,ilosc_osobnikow,0,chromek, nullptr };
		else {
			auto o = osoba;
			while (o->pNext)
				o = o->pNext;
			o->pNext = new Osobnik{ ilosc_genu,ilosc_osobnikow,0,chromek, nullptr };
		}
	}
	auto grupa = new Stado{ ilosc_osobnikow,nullptr };
	plik.close();
	//debug(grupa->ilosc_osobnikow_w_grupie);
	//debug(grupa->pNextPokolenie);
	std::cout << "Wczytano grupe badawcza" << std::endl;
	return ilosc_osobnikow;
}