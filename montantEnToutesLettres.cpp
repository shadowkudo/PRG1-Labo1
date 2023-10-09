/* ---------------------------
Laboratoire : 01-MontantEnToutesLettres
Auteur(s) : David Schildböck
Date : 06.10.2023
But : convertisseur nombre mathématique au langage français
Remarque(s) :   - pas de tableaux, pas de redondance de code, pas de plagiat
                - règles du français respectées
--------------------------- */
#include "montantEnToutesLettres.h"
#include <iostream>
#include <cmath>

using namespace std;

// fonction pour afficher chaque chiffre du nombre donné par le user
int unite(long double& n, int exposant){
    int chiffre = 0;
    long double test = 0;
    long double test2 = 0;

    if (exposant > -2){
        chiffre = trunc(n / pow(10, exposant)); // ajoute le chiffre en arrondissant à la valeur inférieure (4.6 = 4) / ! il y a une conversion de type long double à int voulu !
    } else {
        chiffre = round(n*100);
    }
    n -= chiffre * pow(10, exposant); // change la valeur du nombre sans le chiffre trouvé avant

    return chiffre;
}

// fonction pour trouver le premier chiffre qui ne vaut pas 0
int premier(long double n, int exposant){
    // on cherche la valeur > 0
    for (int first = 0; first < 1; exposant--) {
        first = unite(n,exposant); // récupère le premier chiffre
    }

    return ++exposant; // rajoute 1, car la dernière décrémentation est de trop
}

int category(int exposant, string& NomCat){
    int cat;

    switch (exposant) {
        case 11:;
        case 10:;
        case 9: cat = 9;
            NomCat = "milliard";
            break;
        case 8:;
        case 7:;
        case 6: cat = 6;
            NomCat = "million";
            break;
        case 5:;
        case 4:;
        case 3: cat = 3;
            NomCat = "mille";
            break;
        case 2:;
        case 1:;
        case 0: cat = 0;
            NomCat = "";
            break;
        case -1:;
        case -2: cat = -2;
            NomCat = "centimes";
            break;
        default: cout << "\n-> Erreur_fonction_category..." << endl;
    }
    return cat;
}

int Decomposition(long double& n, int exposant_start, string& NomCat){

    int chiffre = 0;
    int exposant_reste = 0;
    int cat = 0;
    exposant_start = premier(n, exposant_start);
    cat = category(exposant_start, NomCat);
    exposant_reste = exposant_start - cat;

    while (exposant_start >= cat) {

        chiffre += unite(n, exposant_start) * pow(10,exposant_reste);

        exposant_start--;
        exposant_reste--;
    }
    return chiffre;
}

string conversion_unite(int chiffre){
    string mot = "";

    switch (chiffre) {
        case 2: mot = "deux"; break;
        case 3: mot = "trois"; break;
        case 4: mot = "quatre"; break;
        case 5: mot = "cinq"; break;
        case 6: mot = "six"; break;
        case 7: mot = "sept"; break;
        case 8: mot = "huit"; break;
        case 9: mot = "neuf"; break;
    }
    return mot;
}

string conversion_dizaine(int chiffre){
    string mot = "";

    switch (chiffre) {
        case 2: mot = "vingt"; break;
        case 3: mot = "trente"; break;
        case 4: mot = "quarante"; break;
        case 5: mot = "cinquante"; break;
        case 6: mot = "soixante"; break;
        case 7: mot = "septante"; break;
        case 8: mot = "huitante"; break;
        case 9: mot = "nonante"; break;
    }
    return mot;
}

string conversion_special(long double nombre){
    string mot = "";
    int n;
    n = trunc(nombre);

    switch (n) {
        case 10: mot = "dix"; break;
        case 11: mot = "onze"; break;
        case 12: mot = "douze"; break;
        case 13: mot = "treize"; break;
        case 14: mot = "quatorze"; break;
        case 15: mot = "quinze"; break;
        case 16: mot = "seize"; break;
        case 17: mot = "dix-sept"; break;
        case 18: mot = "dix-huit"; break;
        case 19: mot = "dix-neuf"; break;
    }
    return mot;
}

string conversion_2chiffres(long double nombre){
    string result = "";
    int chiffre1 = 0;
    int chiffre0 = 0;
    long double nombre_temp = nombre;
    chiffre1 = unite(nombre_temp, 1);
    chiffre0 = unite(nombre_temp, 0);

    if (chiffre1 >= 2) {
        if (chiffre0 != 1 and chiffre0 != 0) {
            result = conversion_dizaine(chiffre1) + "-" + conversion_unite(chiffre0);
        } else if (chiffre0 != 1 and chiffre0 == 0) {
            result = conversion_dizaine(chiffre1);
        } else {
            result = conversion_dizaine(chiffre1) + " et un";
        }
    } else if (chiffre1 == 1){
        result = conversion_special(nombre);
    } else{
        result = conversion_unite(chiffre0);
    }
    return result;
}

string conversion(long double n, int exposant){
    long double reste;
    long double check = 0;
    long double check_temp;
    string nom_cat = "";
    string result = "";
    string result_temp = "";
    int chiffre2 = 0;
    int chiffre0 = 0;
    long double n_temp = n;

    while (ceil(n) > 0.){
        check = Decomposition(n, exposant, nom_cat);
        check_temp = check;
        chiffre2 = unite(check_temp, 2);
        chiffre0 = unite(check_temp, 0);

        if (nom_cat == "centimes" and n_temp < 1){
            result_temp = "";
        } else if (nom_cat == "centimes" and round(n_temp) >= 1){
            result_temp = "Y et ";
        }

        if (chiffre2 > 1 and check_temp == 0 and n == 0){
            result_temp = conversion_unite(chiffre2) + "-cents-";
            check -= chiffre2 * pow(10, 2);

        } else if (chiffre2 > 1 or check_temp != 0 and n != 0) {
            result_temp += result_temp + conversion_2chiffres(chiffre2) + "-cent-";
            check -= chiffre2 * pow(10, 2);
        } else if (chiffre2 == 1 or check_temp != 0 and n != 0) {
            result_temp += result_temp + "cent-";
            check -= chiffre2 * pow(10, 2);
        }

        if (check != 0){
            result_temp += conversion_2chiffres(check);
        }

        if (nom_cat == "million" or nom_cat == "milliard"){
            if (chiffre0 == 1){
                result += result_temp + "un-" + nom_cat + "-";
            } else {
                result += result_temp + "-" + nom_cat + "s-";
            }
        } else if (nom_cat == "" or nom_cat == "centimes"){
            result += result_temp + " " + nom_cat;
        } else{
            result += result_temp + "-" + nom_cat + "-";
        }

        /*if (nom_cat == "" and exposant == 0){
            switch (chiffre0) {
                case 0: result = "zero franc"; break;
                case 1: result += "un franc";
            }
        }*/
        if (nom_cat == ""){
            result += "francs";
        }
        result_temp = "";
    }
    return result;
}

string montantEnToutesLettres(long double montant) {
    const double montant_trop_grand = 1000000000000.;
    const double montant_trop_petit = 0.;
    int exposant_actuel = 11;
    long double montant_temp = montant;
    string nom_cat = " ";

    // check la valeur entrée par l'utilisateur
    if (montant < montant_trop_petit or montant > montant_trop_grand){
        return "Erreur, entrez un nombre compris entre 0 compris et 10 puissance 12 non compris";
    } else {

        if (conversion(montant_temp, exposant_actuel).empty()){
            return "zero franc";
        } else {
            return conversion(montant_temp, exposant_actuel);
        }
    }
}