/** @file */
#ifndef STRUKTURY_H_INCLUDED
#define STRUKTURY_H_INCLUDED

#include <iostream>
#define debug(x) std::cerr<<"("<<__LINE__<<")"<<#x<<" == "<<(x)<<"\n";

/**
Struktura zawiera listê genów dla ka¿dego osobnika.
*/
struct Chromosomy
{
	int gen;	///< wartoœæ genu przechowywana w liœcie.
	Chromosomy* pNextChromosom;	///< wskaŸnik na kolejny element listy.
};

/**
Struktura zawiera listê ze szczegó³owym opisem osobnika.
*/
struct Osobnik
{
	int liczba; ///< liczba genów.
	int numer_osobnika; ///< numer porz¹dkowy osobnika.
	double wartosc_funkcji_oceny;///< wartoœæ funkcji oceny.
	Chromosomy* pNaGloweListyGenow; ///< wskaŸnik na listê genów osobnika.
	Osobnik* pNext; ///< wskaŸnik na kolejny element listy.
};
/**
Struktura zawiera listê z adresami na pierwszego osobnika w pokoleniu.
*/
struct Generacja
{
	Osobnik* pNaPoczatekGeneracji; ///< adres na pierwszego osobnika nowej generacji.
	Generacja* pNextGeneracja; ///< wskaŸnik na kolejny element listy.
};
#endif // STRUKTURY_H_INCLUDED
