#include <iostream>
#include <istream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <random>

#include "struktury.h"

#include "wczytywanie_pliku.h"
#include "pokaz_obecna_generacje.h"
#include "wspolczynnik.h"
#include "eugenika.h"



//  TODO: Parametry przekazywane z linii polecen.
int main(int argc, char * argv[]) // wyklad z funkcji, main to tez funkcja 
{
	//std::random_device generator;

	double wspolczynnik_rozmnazania = -1, wspolczynnik_wymierania = -1;
	int wspolczynnik_k = 1, ilosc_osobnikow = 0, wspolczynnik_p = 0;
	std::string nazwa_pliku = "Blad", nazwa_pliku_wyjsciowego = "Blad", nazwaK, nazwaP, nazwaW, nazwaR;
	for (int i = 0; i < argc; i++)
	{
		std::string a = argv[i];
		std::cout << argv[i+1] << a << std::endl;
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
			std::cout << wspolczynnik_wymierania;
			i++;
		}
		else if (a == "-r")
		{
			nazwaR = argv[i + 1];
			wspolczynnik_rozmnazania = atof(nazwaR.c_str());
			std::cout << wspolczynnik_rozmnazania;
			i++;
		}
		else if (a == "-k")
		{
			nazwaK = argv[i + 1];
			wspolczynnik_k = atoi(nazwaK.c_str());
			std::cout << wspolczynnik_k;
			i++;
		}
		else if (a == "-p")
		{
			nazwaP = argv[i + 1];
			wspolczynnik_p = atoi(nazwaP.c_str());
			wspolczynnik_p;
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


		Osobnik *osoba = nullptr;
		Chromosomy *chromek = nullptr;
		
		ilosc_osobnikow = wczytajGeneracje(osoba, chromek, nazwa_pliku);
				
		// w petli
		
		for (int i = 0; i < wspolczynnik_p; i++)
		{
			std::cout << "Generacja: " << i << " Ilosc Osobnikow: " << ilosc_osobnikow << std::endl;
			// krzyzowanie
			doborOsobnikow(wspolczynnik_k, ilosc_osobnikow, osoba);
			std::cout<<"-----------"<< std::endl;

			// selekcja
			ilosc_osobnikow = selekcja(osoba, ilosc_osobnikow, wspolczynnik_rozmnazania, wspolczynnik_wymierania);
		}
		


		std::cout << std::endl;
		return 0;
	}


