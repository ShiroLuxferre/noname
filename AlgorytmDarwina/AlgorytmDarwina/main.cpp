#include <iostream>
#include <istream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

#ifdef _WIN32
#  define _CRTDBG_MAP_ALLOC
#  include <stdlib.h>
#  include <crtdbg.h>
#endif

#include "struktury.h"

#include "wczytywanie_pliku.h"
#include "pokaz_obecna_generacje.h"
#include "wspolczynnik.h"
#include "eugenika.h"

//  TODO: Parametry przekazywane z linii polecen.

int main(int argc, char* argv[]) // wyklad z funkcji, main to tez funkcja
{
#ifdef _WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	{
		srand(time(NULL));
		// wprowadzanie wspołczynnika
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
			else if (a == "-h")
			{
				std::cout << "Parametry w programie: \n-i plik wejscia\n-o plik wyjscia\n-w wspolczynnik wymierania [0,1]\n-r wspolczynnik rozmnazania [0,1]\n-p liczba pokolen\n-k ilosc par" << std::endl;
				return 0;
			}
		}
		if (wspolczynnik_wymierania < 0 || wspolczynnik_wymierania>1 || wspolczynnik_rozmnazania < 0 || wspolczynnik_rozmnazania>1 || wspolczynnik_p < 0 || wspolczynnik_k < 0)
		{
			std::cout << wspolczynnik_wymierania << " | " << wspolczynnik_rozmnazania << " | " << wspolczynnik_k << " | " << wspolczynnik_p << std::endl;
			std::cout << "Nieprawidlowe parametry! Podaj poprawne!" << std::endl;
			return 0;
		}
		else if (nazwa_pliku == "Blad" || nazwa_pliku_wyjsciowego == "Blad")
		{
			std::cout << "Nie podano pliku/plikow!" << std::endl;
		}
		std::cout << "Parametry zaladowane" << std::endl;

		// sprawdzenie czy generacja ma wiecej niz 2 osobników.
		Generacja* pPokolenie = nullptr;
		ilosc_osobnikow = wczytaj_z_pliku(pPokolenie, nazwa_pliku);
		if (ilosc_osobnikow < 2)
		{
			std::cout << ilosc_osobnikow << " Symulacja przerwana, w populacji znajaduje sie jeden osobnik." << std::endl;
			return 0;
		}
		else if (ilosc_osobnikow < 1)
		{
			std::cout << ilosc_osobnikow << " Symulacja przerwana, populacja pusta." << std::endl;
			return 0;
		}

		auto pOsoba = pPokolenie->pNaPoczatekGeneracji;
		auto pPokDoUsun = pPokolenie;
		//wyswietlPopulacje(pOsoba);

		// w petli
		for (int i = 0; i < wspolczynnik_p; i++)
		{
			std::cout << "Generacja: " << i << " Ilosc Osobnikow: " << ilosc_osobnikow << std::endl;
			// krzyzowanie
			doborOsobnikow(wspolczynnik_k, ilosc_osobnikow, pOsoba);
			std::cout << "-----------" << std::endl;

			// selekcja
			ilosc_osobnikow = selekcja(pOsoba, pPokolenie, ilosc_osobnikow, wspolczynnik_rozmnazania, wspolczynnik_wymierania);
			usuwanie(pPokolenie);
			pOsoba = pPokolenie->pNaPoczatekGeneracji;
			// sprawdzenie czy generacja nie skończyła się przedwcześnie
			if (ilosc_osobnikow < 2)
			{
				std::cout << ilosc_osobnikow << " Symulacja przerwana, w populacji znajduje sie jeden osobnik!" << std::endl;
				zapisz_do_pliku(pPokolenie, nazwa_pliku_wyjsciowego, ilosc_osobnikow);
				return 0;
			}
		}
		// zapisanie do pliku
		zapisz_do_pliku(pPokolenie, nazwa_pliku_wyjsciowego, ilosc_osobnikow);
		std::cout << std::endl;

		//usuwanie
		usuwanie(pPokDoUsun);
		return 0;
	}
#ifdef _WIN32
	int __CrtDumpMemoryLeak(void);
#endif
}