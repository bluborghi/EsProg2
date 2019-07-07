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

using namespace std ;


#include "liste-tipo.h"
#include "liste.h"



/*******************************/
/* DEFINIZIONE MODULO "liste" */
/*******************************/

lista tail(lista p){return p->pun;}
lista prev(lista p){return p->prev;}

lista insert_elem(lista l, elem* e){
	e->pun=l;
	if(l!=NULL)
		l->prev=e;
	e->prev=NULL;
	return e;
}

lista delete_elem(lista l, elem* e){

		if(l==e)
			l=e->pun; // e è la testa della lista
		else // e non è la testa della lista
			(e->prev)->pun = e->pun;
		if(e->pun!=NULL)
			(e->pun)->prev=e->prev;
		delete e;
		return l;
}


lista ord_insert_elem(lista l, elem* e){
	if(l==NULL || compare(e->inf,head(l))<0)
		return insert_elem(l,e);
	else{
		lista l1=l;
		while (tail(l1)!=NULL && compare(head(tail(l1)),e->inf)<0)
			 l1=tail(l1);
		e->pun = l1->pun;
		if(l1->pun != NULL)
			l1->pun->prev=e;
		l1->pun = e;
		e->prev = l1;
		return l;}
}







