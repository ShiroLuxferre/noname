#ifndef STRUKTURY_H_INCLUDED
#define STRUKTURY_H_INCLUDED

#include <iostream>
#define debug(x) std::cerr<<"("<<__LINE__<<")"<<#x<<" == "<<(x)<<"\n";




/**
Struktura zawiera listê genów dla ka¿dego osobnika
*/
struct Chromosomy
{
	int gen;	///< wartosc genu przechowywana w liscie
	Chromosomy *pNextChromosom;	///<wskaznik na kolejny element listy
};


/**
Struktura zawiera listê ze szczegolowym opisem osobnika
*/
struct Osobnik
{
	int liczba; ///< liczba genow
	double wartosc_funkcji_oceny;///< wartosc funkcji oceny
	Chromosomy *pNaGloweListyGenow; /// wskaznik na liste genow osobnika
	Osobnik *pNext; ///<wskaznik na kolejny element listy
};
/**
Struktura zawiera listê z adresami na pierszego  
*/
struct Generacja
{
	Osobnik *pNaPoczatekGenercji; ///< Adres na pierszego osobnika nowej generacji;
	Generacja *pNextGeneracja; ///<wskaznik na kolejny element listy
};
#endif // STRUKTURY_H_INCLUDED 
