/*
  Scrivere un programma per la gestione di liste doppie.
  Il programma presenta un menù all'utente che può
  - creare una lista di n valori (volendo ordinata)
  - cancellare tutti tutti gli elementi contenente un valore dato dalla lista
  - stampare la lista
  - cercare valori nella lista
  Se la lista è ordinata la ricerca deve richiamare ord_search() altrimenti search().
*/

#include <iostream>
#include <cstring>

#include "tipo.h"
#include "liste.h"

using namespace std;

//Modulo tipo

typedef char *tipo_inf;

int compare(tipo_inf s1, tipo_inf s2)
{
  return strcmp(s1, s2);
}

void copy(tipo_inf destination, tipo_inf source)
{
  strcpy(destination, source);
}

void stampa(tipo_inf t, ostream &os)
{
  os << t;
}

tipo_inf leggi(istream &is)
{
  tipo_inf t = new char[51];
  is >> t;
  return t;
}


