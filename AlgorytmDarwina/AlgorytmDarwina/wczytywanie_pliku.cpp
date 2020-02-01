#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "struktury.h"
#include "wspolczynnik.h"
#include "wczytywanie_pliku.h"

int wczytaj_z_pliku(Generacja*& pPokolenie, const std::string& nazwa_pliku)
{
	int ilosc_osobnikow = 0, gen = 0, ilosc_genu;
	std::string caly_chromosom;
	std::ifstream plik(nazwa_pliku);
	Chromosomy* pChromosom = nullptr;

	if (!plik)
	{
		std::cout << "Blad pliku" << std::endl;
		return 1;
	}
	Osobnik* pOsoba = nullptr;
	while (std::getline(plik, caly_chromosom))
	{
		ilosc_osobnikow++;
		ilosc_genu = 0;
		std::istringstream iss(caly_chromosom);
		while (iss >> gen)
		{
			/*if (!(iss >> gen))
			{
				break;
			}*/
			ilosc_genu++;
			if (ilosc_genu == 1)
			{
				pChromosom = new Chromosomy{ gen, nullptr };
			}
			else
			{
				auto ch = pChromosom;
				while (ch->pNextChromosom)
					ch = ch->pNextChromosom;
				ch->pNextChromosom = new Chromosomy{ gen, nullptr };
			}
		}

		if (ilosc_osobnikow == 1)
		{
			pOsoba = new Osobnik;
			pOsoba->liczba = ilosc_genu;
			pOsoba->numer_osobnika = ilosc_osobnikow;
			pOsoba->pNaGloweListyGenow = pChromosom;
			pOsoba->wartosc_funkcji_oceny = fukncja_oceny(pOsoba);
			pOsoba->pNext = nullptr;
			pPokolenie = new Generacja{ pOsoba,nullptr };
			//todo - poprawic blad fukncja
		}
		else
		{
			pOsoba = new Osobnik;
			pOsoba->liczba = ilosc_genu;
			pOsoba->numer_osobnika = ilosc_osobnikow;
			pOsoba->pNaGloweListyGenow = pChromosom;
			pOsoba->wartosc_funkcji_oceny = fukncja_oceny(pOsoba);
			pOsoba->pNext = nullptr;
		}
	}

	plik.close();
	std::cout << "Wczytano grupe badawcza" << std::endl;
	return ilosc_osobnikow;
}

void zapisz_do_pliku(Generacja*& pPokolenie, const std::string& nazwa_pliku, int ilosc_osobnikow)
{
	std::ofstream plik(nazwa_pliku);
	auto pOsoba = pPokolenie->pNaPoczatekGeneracji;
	while (ilosc_osobnikow > 0)
	{
		auto pCh = pOsoba->pNaGloweListyGenow;
		while (pCh)
		{
			plik << pCh->gen << " ";
			pCh = pCh->pNextChromosom;
		}
		plik << "\n";
		ilosc_osobnikow--;
		pOsoba = pOsoba->pNext;
	}
	plik.close();
}