/** @file */

#ifndef EUGENIKA_H
#define EUGENIKA_H

#include <iostream>
#include "struktury.h"
#include "wspolczynnik.h"
#include "eugenika.h"

/** Funkcja losuj¹ca.
 * @param lewy lewy zakres losowanie.
 * @param prawy prawy akres losowania.
 * @return wynik
 */
int losowanie(int lewy, int prawy);

/** Wyszukuje osobnika w liœcie
 * @param numer_osobnika numer porz¹dkowy osobnika.
 * @param pOsoba g³owa listy osobników.
 * @return adres szukanego osobnika.
 */
Osobnik* szukanieOsobnika(int numer_osobnika, Osobnik* pOsoba);

/** Wyszukuje adres genu
 * @param pOsobnik g³owa listy Osobnik.
 * @return adres szukanego chromosomu.
 */

Chromosomy* znajdz_przeciecie(Osobnik*& pOsobnik);

/**
 * @param pOsobnik g³owa listy Osobnik.
 * @return iloœæ genów w liœcie.
 */
int liczenie_ilosci_genow(Osobnik*& pHeadOsobnik);

/** Funckaj zbiera dane spod funkcji i wykonuje swap
 * @param osobnikA numer porz¹dkowy osobnika A.
 * @param osobnikB numer porz¹dkowy osobnika B.
 * @param pOsoba g³owa listy osobników.
 * @return adres szukanego osobnika.
 */
void krzyzowanie_genow(int osobnikA, int osobnikB, Osobnik*& pOsoba);

/** Losuje parê osobników do krzyzowania genów.
 * @param ile_par wspó³czynnik p.
 * @param ile_osobnikow iloœæ osobników w obecnym pokoleniu.
 * @param pOsobnik g³owa listy osobników.
 */
void doborOsobnikow(int ile_par, int ile_osobnikow, Osobnik*& pOsobnik);

/** Funkcja wykonuje selekjcê naturaln¹ na aktulanej populacji.
 * @param pOsobnik wskaŸnik na g³owê listy.
 * @param ilosc_osobnikow liczba osobników w starym pokoleniu.
 * @param wspolczynnik_rozmnazania parametr, powy¿ej którego osobniki s¹ klonowane.
 * @param wspolczynnik_wymierania wspolczynnik parametr, poni¿ej którego osobniki s¹ usuwane.
 */
int selekcja(Osobnik*& pOsobnik, Generacja*& pPokolenie, int ilosc_osobnikow, double wspolczynnik_rozmnazania, double wspolczynnik_wymierania);

/** Funkcja sprz¹ta dane po symulacji.
 * @param pHeadOsobnik wskaŸnik na g³owê listy.
 */
void usuwanie(Osobnik*& pHeadOsobnik);

/** Funkcja sprz¹ta dane po symulacji.
 * @param pPokolenie wskaŸnik na g³owê listy.
 */
void usuwanie_wszystkiego(Generacja*& pPokolenie);
#endif // EUGENIKA_H
