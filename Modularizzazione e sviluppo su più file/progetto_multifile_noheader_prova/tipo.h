
/*******************************/
/* HEADER MODULO "liste-tipo" */
/*******************************/

#include<iostream>
using namespace std;


struct prodotto {
  char nome[21];
  char desc[81];
  int stars;
};

typedef prodotto* tipo_inf;

struct elem
{
	tipo_inf inf;
	elem *pun;
	elem *prev;
};

int compare(tipo_inf s1, tipo_inf s2);
void copy(tipo_inf& destination, tipo_inf source);
void stampa(tipo_inf t, ostream &os);
tipo_inf leggi(istream &is);