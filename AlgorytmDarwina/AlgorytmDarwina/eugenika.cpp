#include <iostream>
#include <random>
#include <cassert>
#include <algorithm>

#include "struktury.h"
#include "wspolczynnik.h"
#include "eugenika.h"


int losowanie(int lewy, int prawy)
{
	// TODO: przekzywac generator z main
	std::random_device generator;
	std::uniform_int_distribution<int> los(lewy, prawy);
	int wynik = los(generator);
	//debug(wynik);
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

void krzyzowanie_genow(int osobnikA, int osobnikB, Osobnik *& pOsoba)
{
	auto o1 = pOsoba;
	//debug(o1);
	auto chromek1 = o1->pNaGloweListyGenow;
    
    auto pOsobnikA = szukanieOsobnika (osobnikA, pOsoba);
    auto pOsobnikB = szukanieOsobnika (osobnikB, pOsoba);
    
    Chromosomy*  pMiejsciePrzecieciaA = znajdz_przeciecie (pOsobnikA);
    Chromosomy*  pMiejsciePrzecieciaB = znajdz_przeciecie (pOsobnikB);
    
    std::swap(pMiejsciePrzecieciaA->pNextChromosom, pMiejsciePrzecieciaB->pNextChromosom); // zamiana miejscami
	pOsobnikA->wartosc_funkcji_oceny=fukncja_oceny(pOsobnikA->pNaGloweListyGenow);
	pOsobnikB->wartosc_funkcji_oceny=fukncja_oceny(pOsobnikB->pNaGloweListyGenow);
    // finito 
}


void doborOsobnikow(int ile_par, int ile_osobnikow, Osobnik *& pOsobnik)
{
	int osA, osB;

	while (ile_par != 0 )
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
int selekcja(Osobnik *& pOsobnik,int ilosc_osobnikow, double wspolczynnikRozmnazania, double wspolczynikWymierania)
{
	
	int ilosc_osobnikow_w_nowym_pokoleniu = 0, liczba_porzadkowa = 1;
	Osobnik  *tmp;

	while (ilosc_osobnikow&&pOsobnik != nullptr)
	{
		if (pOsobnik->pNext->wartosc_funkcji_oceny < wspolczynikWymierania )
		{
			tmp = pOsobnik->pNext;
			pOsobnik->pNext = tmp->pNext;
			delete tmp;
		}
		else if (pOsobnik->pNext->wartosc_funkcji_oceny > wspolczynnikRozmnazania)
		{
			pOsobnik = new Osobnik{ pOsobnik->liczba ,pOsobnik->wartosc_funkcji_oceny,pOsobnik->pNaGloweListyGenow, nullptr };
			ilosc_osobnikow_w_nowym_pokoleniu++;
		}
		else
		{
			ilosc_osobnikow_w_nowym_pokoleniu++;
		}
		pOsobnik = pOsobnik->pNext;
		ilosc_osobnikow--;
	}
	std::cout << "Przeminelo Yule, przetrwali najlepsi" << std::endl;
	return ilosc_osobnikow_w_nowym_pokoleniu++;
}