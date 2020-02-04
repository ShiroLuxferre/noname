#include <iostream>
#include <math.h>
#include "struktury.h"
#include "wspolczynnik.h"

double funkcja_oceny(Osobnik*& pOsoba) //poprawiæ nazwê!!!
{
	const double m = 5;
	const double s = 2;
	int i = pOsoba->liczba;
	double wynik = exp(-(i - m) * (i - m) / (2 * s * s));
	//std::cerr << wynik << std::endl;
	return wynik;
}