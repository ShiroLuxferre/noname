#include <iostream>

#include "struktury.h"
#include "wspolczynnik.h"

double liczenie_wspolczynnika(Chromosomy * ch, typ liczba_genow)
{
	double wynik = 0;
	for (Chromosomy * pCh = ch; pCh != nullptr; pCh = pCh->pNextChromosom)
	{
		wynik += 1.0 / pCh->gen;
	}
	return wynik;
}

void mierzenieDopasowania(Osobnik *& osoba)
{
	int i = 0;
	for (Osobnik * p = osoba; p != nullptr; p = p->pNext)
	{
		p->wspolczynnik_Naturalny = liczenie_wspolczynnika(p->lista_Chromosomow, p->ilosc_genu);
		i++;
	}
	osoba->ilosc_genu = i; // napisywanie danej po wymianie genów z innym osobnikiem
}
