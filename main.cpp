
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace chrono;


//                  TAS MAXIMUM


class TasMaximum {
private:
    vector<int> tas;

public:
    void reserver(int n) {
        tas.reserve(n);
    }

    void inserer(int valeur) {
        tas.push_back(valeur);
        int i = tas.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (tas[i] > tas[parent]) {
                swap(tas[i], tas[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }

    int obtenirMax() {
        return tas[0];
    }

    // EXTRACTION SANS REAJUSTEMENT
    int extraireRacine() {
        int maximum = tas[0];

        tas[0] = tas.back();
        tas.pop_back();

        return maximum;
    }

    // REAJUSTEMENT SEPARE
    void reajuster() {
        int i = 0;
        int n = tas.size();

        while (2 * i + 1 < n) {
            int gauche = 2 * i + 1;
            int droite = 2 * i + 2;
            int plusGrand = gauche;

            if (droite < n && tas[droite] > tas[gauche]) {
                plusGrand = droite;
            }

            if (tas[i] < tas[plusGrand]) {
                swap(tas[i], tas[plusGrand]);
                i = plusGrand;
            } else {
                break;
            }
        }
    }

    bool estVide() {
        return tas.empty();
    }
};


//                  TAS MINIMUM


class TasMinimum {
private:
    vector<int> tas;

public:
    void reserver(int n) {
        tas.reserve(n);
    }

    void inserer(int valeur) {
        tas.push_back(valeur);
        int i = tas.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (tas[i] < tas[parent]) {
                swap(tas[i], tas[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }

    int obtenirMin() {
        return tas[0];
    }

    // EXTRACTION SANS REAJUSTEMENT
    int extraireRacine() {
        int minimum = tas[0];

        tas[0] = tas.back();
        tas.pop_back();

        return minimum;
    }

    // REAJUSTEMENT SEPARE
    void reajuster() {
        int i = 0;
        int n = tas.size();

        while (2 * i + 1 < n) {
            int gauche = 2 * i + 1;
            int droite = 2 * i + 2;
            int plusPetit = gauche;

            if (droite < n && tas[droite] < tas[gauche]) {
                plusPetit = droite;
            }

            if (tas[i] > tas[plusPetit]) {
                swap(tas[i], tas[plusPetit]);
                i = plusPetit;
            } else {
                break;
            }
        }
    }

    bool estVide() {
        return tas.empty();
    }
};


//           MESURE DU TAS MAXIMUM PERSONNALISE


void testerTasMaximum(
    const vector<int>& valeurs, int N,
    double& tempsInsertion,
    double& tempsExtraction,
    double& tempsReajustement,
    int& maximum) {

    TasMaximum tas;
    tas.reserver(N);

    // Mesure de l'insertion
    auto debut = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        tas.inserer(valeurs[i]);
    }

    auto fin = high_resolution_clock::now();

    tempsInsertion = duration<double>(fin - debut).count();

    maximum = tas.obtenirMax();

    // Initialisation des temps
    tempsExtraction = 0;
    tempsReajustement = 0;

    // Mesures separees de l'extraction et du reajustement
    while (!tas.estVide()) {

        debut = high_resolution_clock::now();

        tas.extraireRacine();

        fin = high_resolution_clock::now();

        tempsExtraction += duration<double>(fin - debut).count();

        if (!tas.estVide()) {
            debut = high_resolution_clock::now();

            tas.reajuster();

            fin = high_resolution_clock::now();

            tempsReajustement += duration<double>(fin - debut).count();
        }
    }
}

//                  MESURE DU TAS MAXIMUM STL


void testerSTLMaximum(
    const vector<int>& valeurs, int N,
    double& tempsInsertion,
    double& tempsExtraction,
    int& maximum) {

    priority_queue<int> file;

    auto debut = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        file.push(valeurs[i]);
    }

    auto fin = high_resolution_clock::now();

    tempsInsertion = duration<double>(fin - debut).count();

    maximum = file.top();

    // pop() comprend le reajustement interne de la STL
    debut = high_resolution_clock::now();

    while (!file.empty()) {
        file.pop();
    }

    fin = high_resolution_clock::now();

    tempsExtraction = duration<double>(fin - debut).count();
}


//           MESURE DU TAS MINIMUM PERSONNALISE


void testerTasMinimum(
    const vector<int>& valeurs, int N,
    double& tempsInsertion,
    double& tempsExtraction,
    double& tempsReajustement,
    int& minimum) {

    TasMinimum tas;
    tas.reserver(N);

    // Mesure de l'insertion
    auto debut = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        tas.inserer(valeurs[i]);
    }

    auto fin = high_resolution_clock::now();

    tempsInsertion = duration<double>(fin - debut).count();

    minimum = tas.obtenirMin();

    tempsExtraction = 0;
    tempsReajustement = 0;

    // Mesures separees de l'extraction et du reajustement
    while (!tas.estVide()) {

        debut = high_resolution_clock::now();

        tas.extraireRacine();

        fin = high_resolution_clock::now();

        tempsExtraction += duration<double>(fin - debut).count();

        if (!tas.estVide()) {
            debut = high_resolution_clock::now();

            tas.reajuster();

            fin = high_resolution_clock::now();

            tempsReajustement += duration<double>(fin - debut).count();
        }
    }
}

//                  MESURE DU TAS MINIMUM STL


void testerSTLMinimum(
    const vector<int>& valeurs, int N,
    double& tempsInsertion,
    double& tempsExtraction,
    int& minimum) {

    priority_queue<int, vector<int>, greater<int>> file;

    auto debut = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        file.push(valeurs[i]);
    }

    auto fin = high_resolution_clock::now();

    tempsInsertion = duration<double>(fin - debut).count();

    minimum = file.top();

    // pop() comprend le reajustement interne de la STL
    debut = high_resolution_clock::now();

    while (!file.empty()) {
        file.pop();
    }

    fin = high_resolution_clock::now();

    tempsExtraction = duration<double>(fin - debut).count();
}


//                  PROGRAMME PRINCIPAL


int main() {

    const int N = 1000000;

    vector<int> valeurs;
    valeurs.reserve(N);

    mt19937 generateur(random_device{}());

    uniform_int_distribution<int> distribution(0, 1000000000);

    // Generation des valeurs aleatoires
    for (int i = 0; i < N; i++) {
        valeurs.push_back(distribution(generateur));
    }

    int tailles[] = {1000, 10000, 100000, 1000000};

    cout << fixed << setprecision(6);


    //                  TABLEAU TAS MAXIMUM


    cout << "\n==================== TAS MAXIMUM ====================\n\n";

    cout << left
         << setw(12) << "Elements"
         << setw(13) << "Ins. Tas"
         << setw(13) << "Ins. STL"
         << setw(13) << "Ext. Tas"
         << setw(13) << "Reaj. Tas"
         << setw(13) << "Total Tas"
         << setw(13) << "Ext. STL"
         << setw(13) << "Max Tas"
         << setw(13) << "Max STL"
         << endl;

    cout << string(116, '-') << endl;

    for (int Ntest : tailles) {

        double insTas, extTas, reajTas;
        double insSTL, extSTL;
        int maxTas, maxSTL;

        testerTasMaximum(
            valeurs, Ntest,
            insTas, extTas, reajTas, maxTas
        );

        testerSTLMaximum(
            valeurs, Ntest,
            insSTL, extSTL, maxSTL
        );

        cout << left
             << setw(12) << Ntest
             << setw(13) << insTas
             << setw(13) << insSTL
             << setw(13) << extTas
             << setw(13) << reajTas
             << setw(13) << extTas + reajTas
             << setw(13) << extSTL
             << setw(13) << maxTas
             << setw(13) << maxSTL
             << endl;
    }

    //                  TABLEAU TAS MINIMUM


    cout << "\n==================== TAS MINIMUM ====================\n\n";

    cout << left
         << setw(12) << "Elements"
         << setw(13) << "Ins. Tas"
         << setw(13) << "Ins. STL"
         << setw(13) << "Ext. Tas"
         << setw(13) << "Reaj. Tas"
         << setw(13) << "Total Tas"
         << setw(13) << "Ext. STL"
         << setw(13) << "Min Tas"
         << setw(13) << "Min STL"
         << endl;

    cout << string(116, '-') << endl;

    for (int Ntest : tailles) {

        double insTas, extTas, reajTas;
        double insSTL, extSTL;
        int minTas, minSTL;

        testerTasMinimum(
            valeurs, Ntest,
            insTas, extTas, reajTas, minTas
        );

        testerSTLMinimum(
            valeurs, Ntest,
            insSTL, extSTL, minSTL
        );

        cout << left
             << setw(12) << Ntest
             << setw(13) << insTas
             << setw(13) << insSTL
             << setw(13) << extTas
             << setw(13) << reajTas
             << setw(13) << extTas + reajTas
             << setw(13) << extSTL
             << setw(13) << minTas
             << setw(13) << minSTL
             << endl;
    }

    return 0;
}
