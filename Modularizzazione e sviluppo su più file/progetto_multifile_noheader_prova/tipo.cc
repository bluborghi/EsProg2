#include <iostream>
#include <cstring>

#include "tipo.h"
#include "liste.h"

using namespace std;

//Modulo tipo

int compare(tipo_inf s1, tipo_inf s2)
{
  if (s1->stars > s2->stars)
    return 1;
  if (s1->stars < s2->stars)
    return -1;
  int tmp = strcmp(s1->nome, s2->nome);
  if (tmp != 0)
    return tmp;
  return strcmp(s1->desc, s2->desc);
}

void copy(tipo_inf &destination, tipo_inf source)
{
  if (destination == NULL)
    destination = new prodotto;
  strcpy(destination->nome, source->nome);
  strcpy(destination->desc, source->desc);
  destination->stars = source->stars;
}

void stampa(tipo_inf t, ostream &os)
{
  os << "{ " << t->nome << ", " << t->desc << ", *" << t->stars << "/5 }";
}

tipo_inf leggi(istream &is)
{
  tipo_inf t = new prodotto;
  is >> t->nome >> t->desc >> t->stars;
  return t;
}
