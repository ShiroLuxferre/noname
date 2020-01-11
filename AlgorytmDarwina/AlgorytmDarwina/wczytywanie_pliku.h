#ifndef WCZYTYWANIE_PLIKU_H
#define WCZYTYWANIE_PLIKU_H

#include <iostream>

#include "struktury.h"

/** Funkcja wczytuje ci¹gi liczb i dodaje element na pocz¹tek listy Osobnik i Chromosomy, Dodaje ilosc populacji do listy Stado
@param[in, out] lCh adres pierwszego elementu listy  chromosomów
@param[in, out] pNextOsobnik adres kolejnego elementu listy Opis Osobników
@param wartosc wartosc do dodania do listy */
int wczytajGeneracje(Osobnik*& osoba, Chromosomy*&chromek, const std::string & nazwa_pliku);

#endif // WCZYTYWANIE_PLIKU_H