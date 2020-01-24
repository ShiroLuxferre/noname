#ifndef WCZYTYWANIE_PLIKU_H
#define WCZYTYWANIE_PLIKU_H

#include <iostream>

#include "struktury.h"
#include "wspolczynnik.h"

/**Funkcja zape³nia liste z wskazaniem na pierwszego osobnika w gerneracji
* @param pPokolenie wskaznik na pierwszy element listy
* @param p ilosc pokolen
*/
void addGen(Generacja*& pPokolenie, int p);

/** Funkcja wczytuje ci¹gi liczb i dodaje element na pocz¹tek listy Osobnik i Chromosomy, Dodaje ilosc populacji do listy Stado
* @param pOsoba adres na pierwszy element listy Osobnik
* @param pChromek adres pierwszego elementu listy  chromosomów
* @param wartosc wartoœæ do dodania do listy 
* @return iloœæ osobników w generacji*/
int wczytajGeneracje(Generacja*&  pokolenie, const std::string & nazwa_pliku);

#endif // WCZYTYWANIE_PLIKU_H
 