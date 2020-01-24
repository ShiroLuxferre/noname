#include <iostream>

#include "struktury.h"
#include "wspolczynnik.h"

double fukncja_oceny(Chromosomy *& pChrom)
{
	double wynik = 0;
	auto pCh = pChrom->pNextChromosom;
	for (auto p = pChrom->pNextChromosom; p != nullptr; p = p->pNextChromosom)
	{
		wynik += 1.0 / pCh->gen;
	}
	return wynik;
}
