#include <iostream>

#include "struktury.h"
#include "pokaz_obecna_generacje.h"

void wyswietlPopulacje(Osobnik* opis)
{

	while (opis)
	{
		auto ch = opis->lista_Chromosomow;
		while (ch)
		{
			std::cout << ch->gen << "|";
			ch = ch->pNextChromosom;
		}
		std::cout << std::endl;
		std::cout << "[" << opis->wspolczynnik_Naturalny << ", " << opis->ilosc_genu << "]" << std::endl;
		opis = opis->pNext;
	}
}