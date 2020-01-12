#include <iostream>
#include <istream>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>



#include "struktury.h"
#include "wczytywanie_pliku.h"
#include "pokaz_obecna_generacje.h"
#include "wspolczynnik.h"
#include "eugenika.h"

//Spis funkcji algorytmu
void crt(const std::string & text)
{
	int N = 1, n=text.length();
	for (int i = 0; i<n; i++)
	{
		std::cout << text[i];
		Sleep(N);
	}
}
void opcje()
{
	
	std::string opcion("######################################################################\n############## \t\t\t\t\t\t##############\n#########                     \t\t\t\t     #########\n#####    '-i' plik wejsciowy z populacja                         #####\n####     '-o' plik wyjsciowy z populacja                          ####\n##       '-w' wspolczynnik wymierania w E[0, 1]                     ##\n##       '-r' wspolczynnik rozmnazania r E[0, 1]                    ##\n####     '-p' liczba pokolen p                                    ####\n#####    '-k' liczba par osobnikow losowanych do krzyzowania     #####\n########\t\t\t\t\t\t     #########\n##############                                          ##############\n######################################################################");
	crt(opcion);
	std::wcout << std::endl;
	//752
}
void wiersz_polecen(Osobnik*& osoba, Chromosomy*&chromek, Stado *& grupa,int r, int w, int k, int p  )
{
	
}
int main()
{
	Osobnik *osoba = nullptr;
	Chromosomy *chromek = nullptr;
	Stado *stadko = nullptr;
	double wspolczynnik_rozmanrzania = 0.75, wspolczynnik_wymierania = 0.25;
	int wspolczynnik_k = 3, ilosc_osobnikow, pokolenia = 1;
	std::string nazwa_pliku;
	opcje();
	std::cout << std::endl;
	std::string wybor;
	do
	{
		char przelacznik = 'z';
		std::getline(std::cin, wybor);
		if (wybor.size() < 2)wybor = "hue hue";
		else if (wybor == "exit")
			std::exit(0);
		else if (wybor == "help")
			przelacznik = 'h';
		if (wybor[wybor.size() - 2] == '-')
		{
			przelacznik = wybor.back();
			wybor.resize(wybor.size() - 2);
			if (wybor[wybor.size() - 1] == ' ')
				wybor.resize(wybor.size() - 1);
		}

		switch (przelacznik)
		{
		case 'i':
		{
			nazwa_pliku = wybor + ".txt";
			ilosc_osobnikow = wczytajGeneracje(osoba, chromek, stadko, nazwa_pliku);
			//wyswietlPopulacje(osoba, stadko);
			break;
		}
		case 'w':
		{
			std::istringstream iss(wybor);
			if (!(iss >> wspolczynnik_wymierania))
			{
				crt("Nie wprowadzono liczby\n");
				break;
			}
			if (wspolczynnik_wymierania < 0 || wspolczynnik_wymierania>1)
			{
				crt( "Wspolczynnik wymierania poza przedzialem [0,1]\nWpisz popwawna wartosc wspolczynnika.\n");
				do
				{
					std::cin >> wspolczynnik_wymierania;
				} while (wspolczynnik_wymierania < 0 || wspolczynnik_wymierania>1);
			}
			crt("Wspolczynnik wymierania wynosi: ");
			std::cout<< wspolczynnik_wymierania << std::endl;
			break;
		}
		case 'r':
		{
			std::istringstream iss(wybor);
			iss >> wspolczynnik_rozmanrzania;
			if (!(iss >> wspolczynnik_rozmanrzania))
			{
				crt("Nie wprowadzono liczby\n");
				break;
			}
			if (wspolczynnik_rozmanrzania < 0 || wspolczynnik_rozmanrzania > 1)
			{
				crt("wspołczynnik rozmnazania poza przedzialem [0,1]\nWpisz popwawna wartosc wspolczynnika.\n");
				do
				{
					std::cin >> wspolczynnik_rozmanrzania;
				} while (wspolczynnik_rozmanrzania < 0 || wspolczynnik_rozmanrzania>1);
			}
			crt("Wspolczynnik rozmnazania wynosi: ");
			std::cout<< wspolczynnik_wymierania << std::endl;
			break;
		}
		case 'k':
		{
			std::istringstream iss(wybor);
			iss >> wspolczynnik_k;
			if (!(iss >> wspolczynnik_k))
			{
				crt("Nie wprowadzono liczby\n");
				break;
			}
			if (wspolczynnik_k < 1)
			{
				
			crt("Wspolczynnik k jest mniejsza od 1\nWpisz popwawna wartosc wspolczynnika.\n");
				do
				{
					std::cin >> wspolczynnik_k;
				} while (wspolczynnik_k < 1);
			}
			crt("Ilosc par w pokoleniu wynosi: ");
			std::cout<< wspolczynnik_wymierania << std::endl;
			break;
		}
		case 'p':
		{
			std::istringstream iss(wybor);
			iss >> pokolenia;
			if (!(iss >> pokolenia))
			{
				crt("Nie wprowadzono liczby\n");
				break;
			}
			if (pokolenia < 1)
			{
				crt("Liczba pokolen jest mniejsza od 1.\nWpisz popwawna wartosc wspolczynnika.\n");
				do
				{
					std::cin >> pokolenia;
				} while (pokolenia < 1);
			}
			crt("Wspolczynnik wymierania wynosi: ");
			std::cout<< pokolenia << std::endl;
			break;
		}
		case 'o':
		{
			crt("W budowie");
			break;
		}
		case 'q':
		{
			crt("Wspolczynnik rozmanraznia:"); std::cout << wspolczynnik_rozmanrzania;
			crt("\nWspolczynnik wymierania: "); std::cout << wspolczynnik_wymierania;
			crt("\nIlosc par: "); std::cout << wspolczynnik_k;
			crt("\nIlosc badanych generacji: "); std::cout << pokolenia << std::endl;
		}
		case 'h':
		{
			opcje();
			break;
		}
		case 'a':
		{
			if (nazwa_pliku.size() != 0)
				wyswietlPopulacje(osoba, stadko);
			break;
		}
		default:
			if (wybor == "start")
			{
				if (nazwa_pliku.empty() == true)
				{
					crt("Czy napewno chcesz isc daje? PLik wejsciowy jest pusty.\n(y/n)\n");
					switch (std::cin.get())
					{
					case 'y':
						wybor == "start";
						break;
					default:
						wybor.clear();
						wybor == "true";
						break;
					}
				}
				else
				{
					crt("Naperwo chcesz opuscic liste konfiguracyjna\n(y/n)\n");
					switch (std::cin.get())
					{
					case 'y':
						wybor == "start";
						break;
					default:
						wybor.clear();
						wybor == "true";
						break;
					}
				}
			}
			else
			{
				if (wybor != "start" && przelacznik == 'z')
					crt("Podaj parametr\n");
				else if(przelacznik != 'z')
					crt("Podano niewlasciwy parametr\n");
			}
		}
	}while (wybor != "start");
		
		
		

		mierzenieDopasowania(osoba);
		doborOsobnikow(wspolczynnik_k, ilosc_osobnikow, osoba);
		//std::cout << std::endl;
		usunZleDopasowane(osoba, stadko, wspolczynnik_wymierania);
		//std::cout << std::endl;
		klonowanie(stadko, osoba, wspolczynnik_rozmanrzania, wspolczynnik_wymierania);

		narodziny(stadko, osoba, wspolczynnik_rozmanrzania, wspolczynnik_wymierania); 

	
	std::cout << std::endl;
	return 0;
}

