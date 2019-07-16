#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int fattoriale(int n)
{
    if (n == 0)
        return 1;
    return n * fattoriale(n - 1);
}

double chebyshev(int n, double x)
{
    double Tnx = 0;
    int num_somme = n / 2;
    for (int k = 0; k <= num_somme; k++)
    {
        double numeratore = pow(-1, k) * fattoriale(n) * pow(x, n - 2 * k) * pow((1 - pow(x, 2)), k);
        double denominatore = fattoriale(n - 2 * k) * fattoriale(2 * k);
        Tnx = Tnx + numeratore / denominatore;
    }
    return Tnx;
}

double chebyshev_r(int n, double x)
{
    //casi base
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    //caso generale
    double Tnx = 2 * x * chebyshev_r(n - 1, x) - chebyshev_r(n - 2, x);
    return Tnx;
}

double genera_punti(double *punti, int num_punti, double a, double b)
{
    double intervallo = b - a;
    double delta = intervallo / (num_punti - 1);
    for (int i = 0; i <= num_punti - 1; i++)
        punti[i] = i * delta + a;
}

void calcola_tabella_chebyshev(double **risultati, double *punti, int num_punti, int *ordini, int num_pol)
{
    for (int i = 0; i <= num_punti - 1; i++)
        for (int j = 0; j <= num_pol - 1; j++)
            risultati[i][j] = chebyshev(ordini[j], punti[i]);
}

void calcola_tabella_chebyshev_r(double **risultati, double *punti, int num_punti, int *ordini, int num_pol)
{
    for (int i = 0; i <= num_punti - 1; i++)
        for (int j = 0; j <= num_pol - 1; j++)
            risultati[i][j] = chebyshev_r(ordini[j], punti[i]);
}

void stampa_tabella(double **risultati, double *punti, int num_punti, int *ordini, int num_pol, string nome_f)
{
    ofstream f(nome_f);
    f << setw(15) << "x";
    for (int i = 0; i <= num_pol - 1; i++)
    {
        string s = "T" + to_string(ordini[i]) + "(x)";
        f << setw(15) << s;
    }
    f << endl;

    for (int i = 0; i <= num_punti - 1; i++)
    {
        f << setw(15) << punti[i];
        for (int j = 0; j <= num_pol - 1; j++)
            f << setw(15) << risultati[i][j];
        f << endl;
    }
    f.close();
}

int main()
{
    int num_pol;
    cout << "Quanti pol di chebycoso?" << endl;
    cin >> num_pol;

    int *ordini;
    ordini = new int[num_pol];

    for (int i = 0; i <= num_pol - 1; i++)
    {
        cout << "inserisci grado del " << i << "° polinomio" << endl;
        cin >> ordini[i];
    }

    int num_punti;
    cout << "in quanti punti valutare i polinomi?" << endl;
    cin >> num_punti;

    double *punti;
    punti = new double[num_punti];

    genera_punti(punti, num_punti, -1, 1);

    double **ris;
    ris = new double *[num_punti];
    for (int i = 0; i <= num_punti; i++)
        ris[i] = new double[num_pol];

    calcola_tabella_chebyshev(ris, punti, num_punti , ordini, num_pol);

    double **ris_r;
    ris_r = new double *[num_punti];
    for (int i = 0; i <= num_punti; i++)
        ris_r[i] = new double[num_pol];

    calcola_tabella_chebyshev_r(ris_r, punti, num_punti, ordini, num_pol);

    string nome_f1;
    cout << "come chiamo il file 1 (metodo iterativo)?" << endl;
    cin >> nome_f1;
    stampa_tabella(ris, punti, num_punti, ordini, num_pol, nome_f1);

    string nome_f2;
    cout << "come chiamo il file 2 (metodo ricorsivo)?" << endl;
    cin >> nome_f2;
    stampa_tabella(ris_r, punti, num_punti, ordini, num_pol, nome_f2);

    return 0;
}