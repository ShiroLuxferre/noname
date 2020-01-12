#ifndef EUGENIKA_H
#define EUGENIKA_H

#include <iostream>
#include "struktury.h"
#include "wspolczynnik.h"
#include "eugenika.h"

int losowanie(int a, int b);

Osobnik * szukanieOsobnika(typ os, Osobnik * o);

Chromosomy * znajdz_enty_chromosom(int n, Chromosomy *chromek);

int pekniecie_genu(int osA, Osobnik *&opis);

void krzyzowanie_genow(int pekniecie1, int osA, int pekniecie2, int osB, Osobnik *& osoba);

void doborOsobnikow(int ile_par, int ile_osobnikow, Osobnik *& osoba);

void usunZleDopasowane(Osobnik *& osoba, Stado *& grupa, double w);

void klonowanie(Stado *& grupa, Osobnik *& opis, double wspolczynnikRozmnazania, double wspolczynikWymierania);

void narodziny(Stado *& grup, Osobnik *& opis, double wspolczynnikRozmnazania, double wspolczynikWymierania);

#endif // EUGENIKA_H
