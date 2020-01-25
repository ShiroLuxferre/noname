#include <iostream>

#include <stdlib.h>
#include <cassert>
#include <algorithm>

#include "struktury.h"
#include "wspolczynnik.h"
#include "eugenika.h"


int losowanie(int lewy, int prawy)
{
	// TODO: przekzywac generator z main
	if (lewy > prawy)
		return lewy;
	int wynik = rand() % prawy + lewy;
	debug(wynik);
	return wynik;
}

Osobnik * szukanieOsobnika(int numer_osobnika, Osobnik * pOsoba)
{
	int i = 1;
	while (true)
	{
		if (pOsoba == nullptr || i == numer_osobnika)
			break;
		pOsoba = pOsoba->pNext;
		i++;
	}
	return pOsoba;
}

Chromosomy* znajdz_przeciecie(Osobnik *& pOsobnik)
{
	auto pOs = pOsobnik;
	auto pCh = pOsobnik->pNaGloweListyGenow;
	//debug(o);
	//o = szukanieOsobnika(osA, pOpis);
	int numer_przerwanego_genu = losowanie(2, (pOs->liczba)-1);
	for (int i = 1; i < numer_przerwanego_genu; i++)
	{
		pCh = pCh->pNextChromosom;
	}
	auto miejsce_przerwania = pCh;
	return miejsce_przerwania;
}
int liczenie_ilosci_genow(Chromosomy *& pChrom)
{
	int ilosc_genu = 0;
	auto pCh = pChrom->pNextChromosom;
	for (auto p = pChrom->pNextChromosom; p != nullptr; p = p->pNextChromosom)
	{
		ilosc_genu++;
	}
	return ilosc_genu;
}

void krzyzowanie_genow(int osobnikA, int osobnikB, Osobnik *& pOsoba)
{
	auto o1 = pOsoba;
	//debug(o1);
	auto chromek1 = o1->pNaGloweListyGenow;
    
    auto pOsobnikA = szukanieOsobnika (osobnikA, pOsoba);
    auto pOsobnikB = szukanieOsobnika (osobnikB, pOsoba);
	debug(pOsobnikA);
	debug(pOsobnikB);
    Chromosomy*  pMiejsciePrzecieciaA = znajdz_przeciecie (pOsobnikA);
    Chromosomy*  pMiejsciePrzecieciaB = znajdz_przeciecie (pOsobnikB);
    
    std::swap(pMiejsciePrzecieciaA->pNextChromosom, pMiejsciePrzecieciaB->pNextChromosom); // zamiana miejscami
	pOsobnikA->wartosc_funkcji_oceny=fukncja_oceny(pOsobnikA->pNaGloweListyGenow);
	//std::cout << pOsobnikA->wartosc_funkcji_oceny<<std::endl;
	pOsobnikB->wartosc_funkcji_oceny=fukncja_oceny(pOsobnikB->pNaGloweListyGenow);
	//std::cout << pOsobnikB->wartosc_funkcji_oceny << std::endl;

	pOsobnikA->liczba = liczenie_ilosci_genow(pOsobnikA->pNaGloweListyGenow);
	pOsobnikB->liczba = liczenie_ilosci_genow(pOsobnikB->pNaGloweListyGenow);

    // finito 
}


void doborOsobnikow(int ile_par, int ile_osobnikow, Osobnik *& pOsobnik)
{
	int osA, osB;
	
	while (ile_par != 0)
	{
		osA = losowanie(1, ile_osobnikow);
		do
		{
			osB = losowanie(1, ile_osobnikow);
		} while (osA == osB);
		ile_par--;
		
		krzyzowanie_genow(osA, osB, pOsobnik);
	}

}
int selekcja(Osobnik *& pOsobnik, Generacja*& pPokolenie, int ilosc_osobnikow, double wspolczynnik_rozmnazania, double wspolczynnik_wymierania)
{
	int ilosc_osobnikow_w_nowym_pokoleniu = 0, liczba_porzadkowa = 1;

	while (ilosc_osobnikow&&pOsobnik != nullptr)
	{
		if (pOsobnik->wartosc_funkcji_oceny > wspolczynnik_wymierania&&pOsobnik->wartosc_funkcji_oceny< wspolczynnik_rozmnazania)
		{
			pOsobnik = new Osobnik{ pOsobnik->liczba, pOsobnik->numer_osobnika,pOsobnik->wartosc_funkcji_oceny,pOsobnik->pNaGloweListyGenow, nullptr };
			ilosc_osobnikow_w_nowym_pokoleniu++;
			if (ilosc_osobnikow_w_nowym_pokoleniu == 1)
			{
				pPokolenie = new Generacja;
				pPokolenie->pNaPoczatekGenercji = pOsobnik;
				pPokolenie->pNextGeneracja = nullptr;

			}
		}
		else if (pOsobnik->wartosc_funkcji_oceny > wspolczynnik_rozmnazania)
		{
			for (int q = 0; q < 2; q++)
			{
				pOsobnik = new Osobnik{ pOsobnik->liczba, pOsobnik->numer_osobnika,pOsobnik->wartosc_funkcji_oceny,pOsobnik->pNaGloweListyGenow, nullptr };
				ilosc_osobnikow_w_nowym_pokoleniu++;
				if (ilosc_osobnikow_w_nowym_pokoleniu == 1)
				{
					pPokolenie = new Generacja{ pOsobnik, nullptr };
				}
			}
		}
		pOsobnik = pOsobnik->pNext;
		ilosc_osobnikow--;
	}
	return ilosc_osobnikow_w_nowym_pokoleniu;
}