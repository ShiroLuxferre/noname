#ifndef EUGENIKA_H
#define EUGENIKA_H

#include <iostream>
#include "struktury.h"
#include "wspolczynnik.h"
#include "eugenika.h"


//todo: nieopisane funkcje 
/**
@param lewy lewy zakres losowanie
@param prawy prawy akres losowania
@param generator silnik losowania
@return 
 */
int losowanie(int lewy, int prawy);

/**
@param os numer porz¹dowa osobnika
@param pOsoba glowa listy osobnikow
@return adres szukanego osobnika 
 */
Osobnik * szukanieOsobnika(int numer_osobnika, Osobnik * pOsoba);


/**
@param n
@param chromek g³owa listy Chromosomy
@return adres szukanego chromosoma
 */

Chromosomy* znajdz_przeciecie(Osobnik *& pOsobnik);

int liczenie_ilosci_genow(Chromosomy *& pChrom);

/**
@param os ???
@param o glowa listy osobnikow
@return adres szukanego osobnika
 */
void krzyzowanie_genow(int osobnikA, int osobnikB, Osobnik *& pOsoba);

/**
 * @param ile_par ?
 * @param ile_osobnikow ?
 * @param osoba // glowa listy osobnikow, pHead
 */ 
void doborOsobnikow(int ile_par, int ile_osobnikow, Osobnik *& pOsobnik);
/**
 * @param pOsobnik wskaznik na glowe listy.
 * @param ilosc_osobnikow liczba osobnikow w starej generacji.
 * @param wspolczynnik_rozmnazania powy¿ej którego osobniki sa klonowane.
 * @param wspolczynnik_wymierania wspolczynnik poni¿ej którego osobniki s¹ usuwane.
 */
int selekcja(Osobnik *& pOsobnik, Generacja*& pPokolenie, int ilosc_osobnikow, double wspolczynnik_rozmnazania, double wspolczynnik_wymierania);



#endif // EUGENIKA_H
