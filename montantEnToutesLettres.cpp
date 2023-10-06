#include "montantEnToutesLettres.h"
#include <iostream>
#include <cmath>

using namespace std;

// fonction pour afficher chaque chiffre du nombre donné par le user
int unite(long double& n, int& exposant){
    int chiffre;

    chiffre = trunc(n / pow(10, exposant)); // ajoute le chiffre en arrondissant à la valeur inférieure (4.6 = 4) / ! il y a une conversion de type long double à int voulu !
    n -= chiffre * pow(10, exposant); // change la valeur du nombre sans le chiffre trouvé avant

    return chiffre;
}

// fonction pour trouver le premier chiffre qui ne vaut pas 0
int premier(long double n, int exposant){
    long double first;

    // on cherche la valeur > 0
    while (first < 1) {
        first = unite(n,exposant); // récupère le premier chiffre
        --exposant;
    }

    return exposant;
}

string montantEnToutesLettres(long double montant) {
    const double montant_trop_grand = 1000000000000.;
    const double montant_trop_petit = 0.;
    int exposant_actuel = 11;
    long double montant_temp = montant;

    // check la valeur entrée par l'utilisateur
    if (montant < montant_trop_petit or montant > montant_trop_grand){
        return "Erreur, entrez un nombre compris entre 0 compris et 10 puissance 12 non compris";
    } else {
        exposant_actuel = premier(montant, exposant_actuel);

        while (exposant_actuel >= -2) {
            cout << unite(montant_temp, exposant_actuel) << " - " << exposant_actuel << " - " << montant_temp << endl;
            exposant_actuel--;
        }
        return "zero franc"s;
    }
}