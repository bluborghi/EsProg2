#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

double legendre_ricorsiva(int ordine, double x)
{
    //casi base
    if (ordine == 0)
        return 1;
    if (ordine == 1)
        return x;

    //caso generico
    return ((2 * ordine - 1) * x * legendre_ricorsiva(ordine - 1, x) - (ordine - 1) * legendre_ricorsiva(ordine - 2, x)) / ordine;
}

double legendre(int ordine, double x)
{
    double *p = new double[ordine + 1];
    p[0] = 1;
    p[1] = x;
    for (int n = 2; n <= ordine; n++)
    {
        p[n] = ((2 * n - 1) * x * p[n - 1] - (n - 1) * p[n - 2]) / n;
    }
    return p[ordine];
}

void generaPunti(double *arr, int numPunti)
{
    double offset = -1;
    double dimensioneIntervallo = 2;
    double delta = dimensioneIntervallo / (numPunti - 1);
    for (int i = 0; i <= numPunti - 1; i++)
    {
        arr[i] = i * delta + offset;
    }
}

void calcola_tabella_legendre(double **risultati, double *punti, int numero_punti, int *ordini, int numero_polinomi)
{
    for (int i = 0; i <= numero_punti - 1; i++)
    {
        for (int j = 0; j <= numero_polinomi - 1; j++)
        {
            risultati[i][j] = legendre(ordini[j], punti[i]);
        }
    }
}

int main()
{
    int numero_polinomi;
    int numero_punti;

    cout << "quanti polinomi di legendre?" << endl;
    cin >> numero_polinomi;

    int *ordini = new int[numero_polinomi];

    for (int i = 0; i <= numero_polinomi - 1; i++)
    {
        cout << "inserisci l'ordine del " << i + 1 << "° polinomio" << endl;
        cin >> ordini[i];
    }

    cout << "in quanti punti valutare i polinomi?" << endl;
    cin >> numero_punti;

    double *punti = new double[numero_punti];
    generaPunti(punti, numero_punti);

    //inizializzo matrice dei risultati
    double **risultati;
    risultati = new double *[numero_punti];
    for (int i = 0; i <= numero_punti - 1; i++)
    {
        risultati[i] = new double[numero_polinomi];
    }

    //calcola valori della matrice dei risultati
    calcola_tabella_legendre(risultati, punti, numero_punti, ordini, numero_polinomi);

    string nomeFileOutput;
    cout << "nome del file di output?" << endl;
    cin >> nomeFileOutput;
    ofstream of(nomeFileOutput);

    //visualizza tabella
    of << setw(20) << "x";
    for (int j = 0; j <= numero_polinomi - 1; j++)
    {
        string s = "P" + to_string(ordini[j]) + "(x)";
        of << setw(20) << s;
    }
    of << endl;
    for (int i = 0; i <= numero_punti - 1; i++)
    {
        of << setw(20) << punti[i];

        for (int j = 0; j <= numero_polinomi - 1; j++)
        {
            of << setw(20) << round(1000 * risultati[i][j]) / 1000;
        }
        of << endl;
    }

    return 0;
}
