#include <iostream>

#include "struktury.h"
#include "pokaz_obecna_generacje.h"

void wyswietlPopulacje(Osobnik* pGlowaOsobnika)
{
	Chromosomy* ch = nullptr;
	int l = 1;
	while (pGlowaOsobnika)
	{
		std::cout << l << std::endl;
		ch = pGlowaOsobnika->pNaGloweListyGenow;
		while (ch)
		{
			std::cout << ch->gen << "|";
			ch = ch->pNextChromosom;
		}
		std::cout << std::endl;
		std::cout << "[" << pGlowaOsobnika->wartosc_funkcji_oceny << ", " << pGlowaOsobnika->liczba << "]" << std::endl;
		pGlowaOsobnika = pGlowaOsobnika->pNext;
		l++;
	}
}