#include <iostream>
#include <stdlib.h>
#include <cassert>
#include <algorithm>

#include "struktury.h"
#include "wspolczynnik.h"
#include "eugenika.h"

int losowanie(int lewy, int prawy)
{
	if (lewy > prawy)
		return lewy;
	int wynik = rand() % prawy + lewy;
	return wynik;
}

Osobnik* szukanieOsobnika(int numer_osobnika, Osobnik* pHeadOsobnik)
{
	int i = 1;
	while (pHeadOsobnik->pNext != nullptr && i != numer_osobnika)
	{
		pHeadOsobnik = pHeadOsobnik->pNext;
		i++;
	}
	return pHeadOsobnik;
}

Chromosomy* znajdz_przeciecie(Osobnik*& pHeadOsobnik)
{
	auto pOs = pHeadOsobnik;
	auto pCh = pHeadOsobnik->pNaGloweListyGenow;
	int i = 1;
	int numer_przerwanego_genu = losowanie(2, (pOs->liczba) - 1);
	while (pCh != nullptr && i != numer_przerwanego_genu)
	{
		pCh = pCh->pNextChromosom;
		i++;
	}
	return pCh;
}
int liczenie_ilosci_genow(Osobnik*& pHeadOsobnik)

{
	int ilosc_genu = 1;
	auto pIle = pHeadOsobnik->pNaGloweListyGenow;
	while (pIle->pNextChromosom != nullptr)
	{
		ilosc_genu++;
		pIle = pIle->pNextChromosom;
	}
	return ilosc_genu;
}

void krzyzowanie_genow(int osobnikA, int osobnikB, Osobnik*& pHeadOsobnik)
{
	auto pOsobnikA = szukanieOsobnika(osobnikA, pHeadOsobnik); //tutaj
	auto pOsobnikB = szukanieOsobnika(osobnikB, pHeadOsobnik);
	Chromosomy* pMiejsciePrzecieciaA = znajdz_przeciecie(pOsobnikA);
	Chromosomy* pMiejsciePrzecieciaB = znajdz_przeciecie(pOsobnikB);

	// zamiana miejscami
	std::swap(pMiejsciePrzecieciaA->pNextChromosom, pMiejsciePrzecieciaB->pNextChromosom);
	pOsobnikA->liczba = liczenie_ilosci_genow(pOsobnikA);
	pOsobnikB->liczba = liczenie_ilosci_genow(pOsobnikB);

	// ponowne liczenie funkcji oceny po wymianie genów + liczenie ilosci genow;
	pOsobnikA->wartosc_funkcji_oceny = fukncja_oceny(pOsobnikA);
	pOsobnikB->wartosc_funkcji_oceny = fukncja_oceny(pOsobnikB);

	// finito
}

void doborOsobnikow(int wspolczynnik_p, int ile_osobnikow, Osobnik*& pHeadOsobnik)
{
	int osA, osB;

	while (wspolczynnik_p != 0)
	{
		// losowanie osobników.
		osA = losowanie(1, ile_osobnikow);
		do
		{
			osB = losowanie(1, ile_osobnikow);
		} while (osA == osB);
		wspolczynnik_p--;

		krzyzowanie_genow(osA, osB, pHeadOsobnik);
	}
}

//todo: Przepisaæ funckjê aby nowa generacja by³a now¹ list¹, a chromosomy nie kopiowaæ adrtes a przepisywac do wonych list

int selekcja(Osobnik*& pHeadOsobnik, Generacja*& pPokolenie, int ilosc_osobnikow, double wspolczynnik_rozmnazania, double wspolczynnik_wymierania)
{
	int ilosc_osobnikow_w_nowym_pokoleniu = 0, liczba_porzadkowa = 1;
	Osobnik* pHeadNowePokolenieOsobnik = nullptr;
	Osobnik* pOsobnik = nullptr;
	while (ilosc_osobnikow && pHeadOsobnik != nullptr)
	{
		// w<=f<=r

		//todo: osobnik == nullptr. Nastepnie puscic usuwanie pokolenia.
		if (pHeadOsobnik->wartosc_funkcji_oceny > wspolczynnik_wymierania&& pHeadOsobnik->wartosc_funkcji_oceny < wspolczynnik_rozmnazania)
		{
			pHeadNowePokolenieOsobnik = new Osobnik;
			pHeadNowePokolenieOsobnik->liczba = pHeadOsobnik->liczba;
			pHeadNowePokolenieOsobnik->numer_osobnika = ilosc_osobnikow_w_nowym_pokoleniu + 1;
			pHeadNowePokolenieOsobnik->wartosc_funkcji_oceny = pHeadOsobnik->wartosc_funkcji_oceny;
			pHeadNowePokolenieOsobnik->pNext = nullptr;
			//int i = 0;
			Chromosomy* pHeadNewChromosomy = nullptr, * pChromerk = pHeadOsobnik->pNaGloweListyGenow;
			pHeadNewChromosomy = new Chromosomy;
			pHeadNewChromosomy->gen = pChromerk->gen;
			pHeadNewChromosomy->pNextChromosom = nullptr;
			pHeadNowePokolenieOsobnik->pNaGloweListyGenow = pHeadNewChromosomy;
			auto temppHeadNewChromosomy = pHeadNewChromosomy;
			while (pChromerk->pNextChromosom != nullptr)
			{
				pChromerk = pChromerk->pNextChromosom;
				temppHeadNewChromosomy->pNextChromosom = new Chromosomy;
				temppHeadNewChromosomy = temppHeadNewChromosomy->pNextChromosom;
				temppHeadNewChromosomy->gen = pChromerk->gen;
				temppHeadNewChromosomy->pNextChromosom = nullptr;
			}
			ilosc_osobnikow_w_nowym_pokoleniu++;
			if (ilosc_osobnikow_w_nowym_pokoleniu == 1)
			{
				pPokolenie->pNextGeneracja = new Generacja{ pHeadNowePokolenieOsobnik, nullptr };
				pOsobnik = pPokolenie->pNextGeneracja->pNaPoczatekGeneracji;
			}
			else {
				/*auto temppHeadNowePokolenieOsobnik = pPokolenie->pNextGeneracja->pNaPoczatekGeneracji;
				while (temppHeadNowePokolenieOsobnik->pNext != nullptr) {
					temppHeadNowePokolenieOsobnik = temppHeadNowePokolenieOsobnik->pNext;
				}*/
				pOsobnik->pNext = pHeadNowePokolenieOsobnik;
				pOsobnik = pOsobnik->pNext;
			}
			//std::cout << ilosc_osobnikow_w_nowym_pokoleniu << " " << pHeadNowePokolenieOsobnik << " " << pHeadNowePokolenieOsobnik->pNaGloweListyGenow << std::endl;
		}
		// f>r
		else if (pHeadOsobnik->wartosc_funkcji_oceny > wspolczynnik_rozmnazania)
		{
			for (int q = 0; q < 2; q++)
			{
				pHeadNowePokolenieOsobnik = new Osobnik;
				pHeadNowePokolenieOsobnik->liczba = pHeadOsobnik->liczba;
				pHeadNowePokolenieOsobnik->numer_osobnika = ilosc_osobnikow_w_nowym_pokoleniu + 1;
				pHeadNowePokolenieOsobnik->wartosc_funkcji_oceny = pHeadOsobnik->wartosc_funkcji_oceny;
				pHeadNowePokolenieOsobnik->pNext = nullptr;
				//int i = 0;
				Chromosomy* pHeadNewChromosomy = nullptr, * pChromerk = pHeadOsobnik->pNaGloweListyGenow;
				pHeadNewChromosomy = new Chromosomy;
				pHeadNewChromosomy->gen = pChromerk->gen;
				pHeadNewChromosomy->pNextChromosom = nullptr;
				pHeadNowePokolenieOsobnik->pNaGloweListyGenow = pHeadNewChromosomy;
				auto temppHeadNewChromosomy = pHeadNewChromosomy;
				while (pChromerk->pNextChromosom != nullptr)
				{
					pChromerk = pChromerk->pNextChromosom;
					temppHeadNewChromosomy->pNextChromosom = new Chromosomy;
					temppHeadNewChromosomy = temppHeadNewChromosomy->pNextChromosom;
					temppHeadNewChromosomy->gen = pChromerk->gen;
					temppHeadNewChromosomy->pNextChromosom = nullptr;
				}
				ilosc_osobnikow_w_nowym_pokoleniu++;
				if (ilosc_osobnikow_w_nowym_pokoleniu == 1)
				{
					pPokolenie->pNextGeneracja = new Generacja{ pHeadNowePokolenieOsobnik, nullptr };
					pOsobnik = pPokolenie->pNextGeneracja->pNaPoczatekGeneracji;
				}
				else {
					/*auto temppHeadNowePokolenieOsobnik = pPokolenie->pNextGeneracja->pNaPoczatekGeneracji;
					while (temppHeadNowePokolenieOsobnik->pNext != nullptr) {
						temppHeadNowePokolenieOsobnik = temppHeadNowePokolenieOsobnik->pNext;
					}*/
					pOsobnik->pNext = pHeadNowePokolenieOsobnik;
					pOsobnik = pOsobnik->pNext;
				}
				//pHeadNowePokolenieOsobnik = pHeadNowePokolenieOsobnik->pNext;
				//std::cout << ilosc_osobnikow_w_nowym_pokoleniu << " " << pHeadNowePokolenieOsobnik << " " << pHeadNowePokolenieOsobnik->pNaGloweListyGenow << std::endl;
			}
		}
		pHeadOsobnik = pHeadOsobnik->pNext;
		ilosc_osobnikow--;
	}

	return ilosc_osobnikow_w_nowym_pokoleniu;
}

//todo: przerobic funkcje aby pasowa³a do 1 pokolenie == 1 lista
void usuwanie(Osobnik*& pHeadOsobnik)
{
	Chromosomy* pChrom = nullptr;
	Chromosomy* pChromC = nullptr;
	Osobnik* pOsC = nullptr;
	Generacja* pPoC = nullptr;
	Osobnik* pOsoba = nullptr;

		while (pHeadOsobnik != nullptr)
		{
			while (pHeadOsobnik->pNaGloweListyGenow != nullptr && pHeadOsobnik->pNaGloweListyGenow->gen > 0)
			{
				
				pChrom = pHeadOsobnik->pNaGloweListyGenow;
				pChromC = pChrom;
				if (pChromC->pNextChromosom != nullptr)
					pChromC = pChromC->pNextChromosom;
				else
					pChromC = nullptr;
				delete pChrom;
				pChrom = nullptr;
				pHeadOsobnik->pNaGloweListyGenow = pChromC;
			}
			pOsC = pHeadOsobnik;
			if (pOsC->pNext != nullptr)
				pOsC = pOsC->pNext;
			else
				pOsC = nullptr;
			delete pHeadOsobnik;
			pHeadOsobnik = nullptr;
			pHeadOsobnik= pOsC;
		}
		/*
		pPoC = pPokolenie;
		if (pPoC->pNextGeneracja != nullptr)
			pPoC = pPoC->pNextGeneracja;
		else
			pPoC = nullptr;
		pPokolenie->pNextGeneracja = nullptr;
		delete pPokolenie;
		pPokolenie = nullptr;
		pPokolenie = pPoC;
		*/

	delete pChrom;
	delete pChromC;
	delete pOsC;
	delete pPoC;
	delete pOsoba;
	pChrom = nullptr;
	pChromC = nullptr;
	pOsC = nullptr;
	pPoC = nullptr;
	pOsoba = nullptr;
}

void usuwanie_wszystkiego(Generacja*& pPokolenie)
{
	Chromosomy* pChrom = nullptr;
	Chromosomy* pChromC = nullptr;
	Osobnik* pOsC = nullptr;
	Generacja* pPoC = nullptr;
	Osobnik* pOsoba = nullptr;

	while (pPokolenie != nullptr)
	{
		while (pPokolenie->pNaPoczatekGeneracji != nullptr)
		{
			pOsoba = pPokolenie->pNaPoczatekGeneracji;
			while (pPokolenie->pNaPoczatekGeneracji->pNaGloweListyGenow != nullptr && pPokolenie->pNaPoczatekGeneracji->pNaGloweListyGenow->gen > 0)
			{
				pChrom = pPokolenie->pNaPoczatekGeneracji->pNaGloweListyGenow;
				pChromC = pChrom;
				if (pChromC->pNextChromosom != nullptr)
					pChromC = pChromC->pNextChromosom;
				else
					pChromC = nullptr;
				delete pChrom;
				pChrom = nullptr;
				pOsoba->pNaGloweListyGenow = pChromC;
			}
			pOsC = pOsoba;
			if (pOsC->pNext != nullptr)
				pOsC = pOsC->pNext;
			else
				pOsC = nullptr;
			delete pOsoba;
			pOsoba = nullptr;
			pPokolenie->pNaPoczatekGeneracji = pOsC;
		}

		pPoC = pPokolenie;
		if (pPoC->pNextGeneracja != nullptr)
			pPoC = pPoC->pNextGeneracja;
		else
			pPoC = nullptr;
		pPokolenie->pNextGeneracja = nullptr;
		delete pPokolenie;
		pPokolenie = nullptr;
		pPokolenie = pPoC;
	}
	delete pChrom;
	delete pChromC;
	delete pOsC;
	delete pPoC;
	delete pOsoba;
	pChrom = nullptr;
	pChromC = nullptr;
	pOsC = nullptr;
	pPoC = nullptr;
	pOsoba = nullptr;
}