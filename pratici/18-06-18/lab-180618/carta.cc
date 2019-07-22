#include <string.h>
#include <iostream>

using namespace std;

#include "carta.h"

int compare(tipo_inf a, tipo_inf b)
{
    return a->id - b->id;
}

void copy(tipo_inf &target, tipo_inf source)
{
    if (target == NULL)
        target = new carta;

    target->id = source->id;
    strcpy(target->owner, source->owner);
    target->points = source->points;
}

void print(tipo_inf a)
{
    cout << "{ "
         << "id: " << a->id << ", owner: " << a->owner << ", points: " << a->points << " }";
}

tipo_inf read()
{
    tipo_inf t = new carta;
    int id, points;
    char name[41], surname[41];
    cout << "inserisci numero carta, nome, cognome e numero punti" << endl;
    cin >> id >> name >> surname >> points;
    
    char owner[41] = "\0";
    strcat(owner,name);
    strcat(owner," ");
    strcat(owner,surname);
    strcpy(t->owner, owner);
    t->id = id;
    t->points = points;
    return t;
}