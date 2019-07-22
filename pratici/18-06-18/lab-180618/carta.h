/*******************************/
/* HEADER MODULO "carta" 	   */
/*******************************/

struct carta {
    int id;
    char owner[41];
    int points;
};

typedef carta *tipo_inf;


int compare(tipo_inf,tipo_inf);
void copy(tipo_inf&,tipo_inf);
void print(tipo_inf);
tipo_inf read();
