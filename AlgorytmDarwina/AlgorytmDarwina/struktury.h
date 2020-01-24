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
	//int numer_osobnika; ///< numer osobnika
	double wartosc_funkcji_oceny;///< wartosc funkcji oceny
	
	Chromosomy *pNaGloweListyGenow; /// wskaznik na liste genow osobnika
	Osobnik *pNext;
};
// TODO: usunac strukture
struct Stado
{
	int ilosc_osobnikow_w_grupie;
	Osobnik *pierwszy_w_generacji;
	Stado *pNextPokolenie;
};


#endif // STRUKTURY_H_INCLUDED 
