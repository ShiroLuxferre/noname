#ifndef STRUKTURY_H_INCLUDED
#define STRUKTURY_H_INCLUDED

#include <iostream>
#define debug(x) std::cerr<<"("<<__LINE__<<")"<<#x<<" == "<<(x)<<"\n";

typedef int typ;

struct Chromosomy
{
	typ gen;	///< wartosc genu przechowywana w liscie
	Chromosomy *pNextChromosom;	///<wskaznik na kolejny element listy
};
struct Stado
{
	typ ilosc_osobnikow_w_grupie;
	Stado *pNextPokolenie;
};


struct Osobnik
{
	typ ilosc_genu;
	typ liczba_porzadkowa;
	double wspolczynnik_Naturalny;
	Chromosomy *lista_Chromosomow;
	Osobnik *pNext;
};

struct Pary
{
	typ osobnikA;
	typ miejsce_pekniecia_A;
	typ osobnikB;
	typ miejsce_pekniecia_B;
	Pary *pNextPary;
};

#endif / STRUKTURY_H_INCLUDED 
