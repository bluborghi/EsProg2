#include <iostream>

using namespace std;

#include "carta.h"
#include "bst.h"

int totalePunti(bst b, int inf, int sup)
{
    if (b == NULL)
        return 0;
    int node_value = 0;
    int node_key = get_key(b);
    if (inf <= node_key && node_key <= sup)
        node_value = get_value(b)->points;

    return node_value + totalePunti(get_left(b), inf, sup) + totalePunti(get_right(b), inf, sup);
}

bool aggiorna(bst &b, int num_carta, int punti)
{
    bnode *node = bst_search(b, num_carta);
    if (node == NULL)
        return false;

    tipo_key k = get_key(node);
    tipo_inf c = new carta;
    c = get_value(node);
    c->points += punti;

    cout << c->points << " " << k << " - ";

    bst_delete(b, node);

    cout << c->points << " " << k << endl;
    node = bst_newNode(k, c);
    bst_insert(b, node);

    return true;
}

void print_nonbuyers(bst carte, bst acquisti)
{
    if (carte == NULL)
        return;

    print_nonbuyers(get_left(carte), acquisti);

    bnode *node = bst_search(acquisti, get_key(carte));
    if (node == NULL)
    {
        print(get_value(carte));
        cout << endl;
    }

    print_nonbuyers(get_right(carte), acquisti);
}

int main()
{
    int num_carte;
    cout << "quante carte inserire?" << endl;
    cin >> num_carte;

    bst carte = NULL;

    for (int i = 0; i < num_carte; i++)
    {
        tipo_inf carta = read();
        bnode *b = bst_newNode(carta->id, carta);
        bst_insert(carte, b);
    }

    print_increasing_order(carte);

    int inf, sup;
    cout << "estremo inferiore:";
    cin >> inf;
    cout << "estremo superiore:";
    cin >> sup;

    cout << "la somma delle carte comprese in [" << inf << "," << sup << "] è: " << totalePunti(carte, inf, sup) << endl;

    bst acquisti = NULL;

    int num_carta;
    cout << "inserisci numero tessera (-1 per terminare)" << endl;
    cin >> num_carta;
    while (num_carta != -1)
    {
        int punti;
        cout << "inserisci punti acquisto" << endl;
        cin >> punti;
        if (!aggiorna(carte, num_carta, punti))
            cout << "Errore, tessera non valida" << endl;
        else
        {
            bnode *utente = bst_search(carte, num_carta);
            tipo_key k = get_key(utente);
            tipo_inf c = new carta;
            c = get_value(utente);
            bst_insert(acquisti, bst_newNode(k,c));
        }

        cout << "inserisci numero tessera (-1 per terminare)" << endl;
        cin >> num_carta;
    }

    print_increasing_order(carte);

    cout << "queste carte non hanno effettuato acquisti oggi: " << endl;
    print_nonbuyers(carte, acquisti);

    return 0;
}