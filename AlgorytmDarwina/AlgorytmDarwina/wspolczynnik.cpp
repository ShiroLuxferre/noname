#include <iostream>
#include <math.h>
#include "struktury.h"
#include "wspolczynnik.h"

/*
double fukncja_oceny(Chromosomy *& pChrom)
{
	double wynik = 0;
	int i = 0;
	auto pCh = pChrom->pNextChromosom;
	for (auto p = pChrom->pNextChromosom; p != nullptr; p = p->pNextChromosom)
	{
		wynik = sin(wynik += 1.0 / pCh->gen);
		i++;
	}
	return wynik;
}
*/

double fukncja_oceny(Osobnik*& pOsoba) //todo: poprawiæ nazwê!!!
{
	double wynik = 0;
	/*int i = 0;
	auto pCh = pOsoba->pNaGloweListyGenow;
	for (auto p = pCh->pNextChromosom; p != nullptr; p = p->pNextChromosom)
	{
		// 		wynik = sin(wynik += 1.0 / pCh->gen);
		i++;
	}*/

	const double m = 5;
	const double s = 2;
	int i = pOsoba->liczba;
	double w = exp(-(i - m) * (i - m) / (2 * s * s));
	//std::cerr << w << std::endl;
	return w;
	return wynik;
}