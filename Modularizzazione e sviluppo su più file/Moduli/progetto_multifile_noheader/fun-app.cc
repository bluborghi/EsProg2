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

/*******************************/
/* HEADER MODULO "liste-tipo" */
/*******************************/

struct elem
{
       char inf[51] ;
       elem* pun ;
       elem* prev;
} ;

typedef elem* lista ;

int compare(char*,char*);
char* head(lista);
elem* ord_search(lista, char*);
elem* new_elem(char*);
elem* search(lista, char*);

/*******************************/
/* HEADER MODULO "liste" */
/*******************************/
	
lista tail(lista);
lista prev(lista);
lista insert_elem(lista, elem*);
lista delete_elem(lista, elem*);
lista ord_insert_elem(lista, elem*);

/**********************************************/
/* HEADER MODULO "funzioni dell'applicazione" */
/**********************************************/
void stampalista(lista);
lista crealista(int, bool);
lista cancella(lista, char*);
void naviga(elem*);



/***************************************************/
/* DEFINIZIONE MODULO "funzioni dell'applicazione" */
/***************************************************/

void stampalista(lista p)
{
	cout<<"[";
	while (p != NULL) {
		cout<<head(p)<<" " ; // stampa valore
		p = tail(p);     // spostamento sul
			                  // prossimo elemento
	}
	cout<<"]"<<endl;
}


lista crealista(int n, bool ord)
{
	char url[80];
      lista testa = NULL ;
      for (int i = 1 ; i <= n ; i++) {
          cout<<"URL "<<i<<": " ;
          cin>>url;
		  elem* p = new_elem(url);
          if(ord)
        	  	  testa=ord_insert_elem(testa,p);
          else
        	  	  testa=insert_elem(testa,p);
      }
      return testa ;
}

lista cancella(lista l, char* v){
	elem* e;
	while((e=search(l,v))!=NULL){
		cout<<"Cancello un elemento con valore "<<v<<endl;
		l=delete_elem(l,e);}
	cout<<"Fine cancellazione!!"<<endl;
	return l;
}

void naviga(elem* e){
	char scelta;
	cout<< "Trovato!!";
	do{
		cout<< "Cosa vuoi fare (B per backward,F per forward, S per stop)"<<endl;
		cin>>scelta;
	    if(scelta=='F' && tail(e)!=NULL){
	    			cout<<head(tail(e))<<endl;
	    			e=tail(e);}
	    else
	    		if(scelta=='B' && prev(e) !=NULL){
	    			cout<<head(prev(e))<<endl;
	    			e=prev(e);}
	    		else cout<<"Elemento non esistente!!"<<endl;}		while(scelta!='S');
}

