#include <iostream>
#include <istream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

#include "struktury.h"

#include "wczytywanie_pliku.h"
#include "pokaz_obecna_generacje.h"
#include "wspolczynnik.h"
#include "eugenika.h"



//  TODO: Parametry przekazywane z linii polecen.
int main(int argc, char * argv[]) // wyklad z funkcji, main to tez funkcja 
{
	srand(time(NULL));

	double wspolczynnik_rozmnazania = -1, wspolczynnik_wymierania = -1;
	int wspolczynnik_k = 1, ilosc_osobnikow = 0, wspolczynnik_p = 0;
	std::string nazwa_pliku = "Blad", nazwa_pliku_wyjsciowego = "Blad", nazwaK, nazwaP, nazwaW, nazwaR;
	for (int i = 0; i < argc; i++)
	{
		std::string a = argv[i];
		if (a == "-i")
		{
			nazwa_pliku = argv[i + 1];
			i++;
		}
		else if (a == "-o")
		{
			nazwa_pliku_wyjsciowego = argv[i + 1];
			i++;
		}
		else if (a == "-w")
		{
			nazwaW = argv[i + 1];
			wspolczynnik_wymierania = atof(nazwaW.c_str());
			i++;
		}
		else if (a == "-r")
		{
			nazwaR = argv[i + 1];
			wspolczynnik_rozmnazania = atof(nazwaR.c_str());
			i++;
		}
		else if (a == "-k")
		{
			nazwaK = argv[i + 1];
			wspolczynnik_k = atoi(nazwaK.c_str());
			i++;
		}
		else if (a == "-p")
		{
			nazwaP = argv[i + 1];
			wspolczynnik_p = atoi(nazwaP.c_str());
			i++;
		}
	}
		if (nazwa_pliku == "Blad" || nazwa_pliku_wyjsciowego == "Blad" || wspolczynnik_wymierania < 0 || wspolczynnik_wymierania>1 || wspolczynnik_rozmnazania < 0 || wspolczynnik_rozmnazania>1 || wspolczynnik_p < 0 || wspolczynnik_k < 0)
		{
			std::cout << nazwa_pliku << " | " << nazwa_pliku_wyjsciowego << " | " << wspolczynnik_wymierania << " | " << wspolczynnik_rozmnazania << " | " << wspolczynnik_k << " | " << wspolczynnik_p << std::endl;
			std::cout << "Zle paramatry, podaj poprawne" << std::endl;
			return 1;
		}
		std::cout << "Parametry zaladowane" << std::endl;


		
		Generacja *pPokolenie = nullptr;
		addGen(pPokolenie, wspolczynnik_p);
		ilosc_osobnikow = wczytajGeneracje(pPokolenie, nazwa_pliku);
		
		auto pOsoba = pPokolenie->pNaPoczatekGenercji;
		// w petli
		//wyswietlPopulacje(pPokolenie->pNaPoczatekGenercji);
		for (int i = 0; i < wspolczynnik_p; i++)
		{
			std::cout << "Generacja: " << i << " Ilosc Osobnikow: " << ilosc_osobnikow << std::endl;
			// krzyzowanie
			doborOsobnikow(wspolczynnik_k, ilosc_osobnikow, pOsoba);
			std::cout<<"-----------"<< std::endl;

			// selekcja
			ilosc_osobnikow = selekcja(pOsoba, pPokolenie, ilosc_osobnikow, wspolczynnik_rozmnazania, wspolczynnik_wymierania);
			pOsoba = pPokolenie->pNaPoczatekGenercji;
			pPokolenie;
			debug(pOsoba);
			debug(pPokolenie);
			if (ilosc_osobnikow < 2)
			{
				std::cout << ilosc_osobnikow <<" Symulacja przerwana, w populacji znajaduje sie jeden osobnik" << std::endl;
				return 0;
			}
			//
		}
		


		std::cout << std::endl;
		return 0;
	}


