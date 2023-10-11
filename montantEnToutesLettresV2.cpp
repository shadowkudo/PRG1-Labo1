/* ---------------------------
Laboratoire : 01-MontantEnToutesLettres
Auteur(s) : David Schildböck - Agron Markaj
Date : 06.10.2023
But : convertisseur nombre mathématique au langage français
Remarque(s) :   - pas de tableaux, pas de redondance de code, pas de plagiat
                - règles du français respectées
Sources utilisés :
 - static cast -> cppreference.com
--------------------------- */
#include <iostream>
#include <cmath>

using namespace std;

// fonction pour trouver le premier exposant dont le chiffre est différent de 1 (4320 -> chiffre 4 -> exposant 3)
int PremierExposant(long long Nombre){
    auto ExposantStart = static_cast<int>(floor(log10(Nombre)));

    return ExposantStart;
}

// fonction pour trouver le chiffre d'un nombre donné selon son exposant (0 -> unité, 1 -> dizaine, ...)
int PremierChiffre(long long Nombre, int ChercheExposant){
    int ChiffreTrouve = 0;
    int ExposantStart = PremierExposant(Nombre);

    for (; ExposantStart >= ChercheExposant; ExposantStart--) {
        ChiffreTrouve = static_cast<int>(trunc(static_cast<long double>(Nombre) / pow(10, ExposantStart)));
        Nombre -= static_cast<long long>(ChiffreTrouve * pow(10, ExposantStart));
    }
    return ChiffreTrouve;
}

// fonction pour séparer l'entier (à gauche de la virgule) et les décimales (à droite de la virgule)
// pour arrondir les décimales et ajouter un à l'entier quand D > 99
int ArrondirDecimales(long double Montant, long long& Entier){

    Entier = static_cast<long long>(Montant);
    auto Decimales = static_cast<int>(round((Montant - Entier)*100));

    if (Decimales > 99) {
        Entier++;
        Decimales = 0;
    }
    return Decimales;
}

// fonction pour connaître la catégorie de l'exposant demandé
int Category(int Exposant){
    int ExposantCategory = 0;

    switch (Exposant) {
        case 11:;
        case 10:;
        case 9: ExposantCategory = 9;
            break;
        case 8:;
        case 7:;
        case 6: ExposantCategory = 6;
            break;
        case 5:;
        case 4:;
        case 3: ExposantCategory = 3;
            break;
        case 2:;
        case 1:;
        case 0: ExposantCategory = 0;
            break;
    }
    return ExposantCategory;
}

// fonction pour décomposer l'entier en différentes catégories (milliard, millier, ...)
int DecompositionMontantCategory(long long& Entier, int ExposantCategory){
    int Decomposition = 0;
    int ExposantStart = 0;
    int ExposantReste = 0;
    ExposantStart = PremierExposant(Entier);
    ExposantReste = ExposantStart - ExposantCategory;

    for (; ExposantStart >= ExposantCategory; ExposantStart--) {

        auto NbTemp = static_cast<long long>(floor(static_cast<long double>(Entier) / pow(10, ExposantStart)));
        Entier -= static_cast<long long>(static_cast<long double>(NbTemp) * pow(10, ExposantStart));
        Decomposition += static_cast<int>(static_cast<long double>(NbTemp) * pow(10, ExposantReste));
        ExposantReste--;

    }
    return Decomposition;
}

/*pseudo liste chiffres et des nombres spéciaux de 11 à 19*/
string ConversionNormale(int Nombre){
    string Conversion;

    switch (Nombre) {
        case 2: Conversion = "deux"; break;
        case 3: Conversion = "trois"; break;
        case 4: Conversion = "quatre"; break;
        case 5: Conversion = "cinq"; break;
        case 6: Conversion = "six"; break;
        case 7: Conversion = "sept"; break;
        case 8: Conversion = "huit"; break;
        case 9: Conversion = "neuf"; break;
        case 10: Conversion = "dix"; break;
        case 11: Conversion = "onze"; break;
        case 12: Conversion = "douze"; break;
        case 13: Conversion = "treize"; break;
        case 14: Conversion = "quatorze"; break;
        case 15: Conversion = "quinze"; break;
        case 16: Conversion = "seize"; break;
        case 17: Conversion = "dix-sept"; break;
        case 18: Conversion = "dix-huite"; break;
        case 19: Conversion = "dix-neuf"; break;
    }
    return Conversion;
}

/*string ConversionUnite(int Chiffre){
    string Conversion;

    switch (Chiffre) {
        case 2: Conversion = "deux"; break;
        case 3: Conversion = "trois"; break;
        case 4: Conversion = "quatre"; break;
        case 5: Conversion = "cinq"; break;
        case 6: Conversion = "six"; break;
        case 7: Conversion = "sept"; break;
        case 8: Conversion = "huit"; break;
        case 9: Conversion = "neuf"; break;
    }
    return Conversion;
}*/

string ConversionDizaine(int Chiffre){
    string Conversion;

    switch (Chiffre) {
        case 1: Conversion = "dix"; break;
        case 2: Conversion = "vingt"; break;
        case 3: Conversion = "trente"; break;
        case 4: Conversion = "quarante"; break;
        case 5: Conversion = "cinquante"; break;
        case 6: Conversion = "soixante"; break;
        case 7: Conversion = "septante"; break;
        case 8: Conversion = "huitante"; break;
        case 9: Conversion = "nonante"; break;
    }
    return Conversion;
}

/*string ConversionSpecial(int Nombre){
    string Conversion;

    switch (Nombre) {
        case 10: Conversion = "dix"; break;
        case 11: Conversion = "onze"; break;
        case 12: Conversion = "douze"; break;
        case 13: Conversion = "treize"; break;
        case 14: Conversion = "quatorze"; break;
        case 15: Conversion = "quinze"; break;
        case 16: Conversion = "seize"; break;
        case 17: Conversion = "dix-sept"; break;
        case 18: Conversion = "dix-huite"; break;
        case 19: Conversion = "dix-neuf"; break;
    }
    return Conversion;
}*/

string ConversionDeuxChiffres(int Chiffre1, int Chiffre0, int Nombre){
    string Conversion;

    if (Nombre < 20 and Nombre >= 10){
        Conversion = ConversionNormale(Nombre);
    } else if (Chiffre1 > 1){
        switch (Chiffre0) {
            case 0: Conversion = ConversionDizaine(Chiffre1); break;
            case 1: Conversion = ConversionDizaine(Chiffre1) + "-et-un"; break;
            default: Conversion = ConversionDizaine(Chiffre1) + "-" + ConversionNormale(Chiffre0);
        }
    } else if (Nombre < 10){
        Conversion = ConversionNormale(Chiffre0);
    }
    return  Conversion;
}
string ConversionCentaine(int TroisChiffes, long long EntierReste){
    string Centaine;
    int Chiffre2 = PremierChiffre(TroisChiffes, 2);
    int Chiffre1 = PremierChiffre(TroisChiffes, 1);
    int Chiffre0 = PremierChiffre(TroisChiffes, 0);
    int EntierReste2Chiffre = static_cast<int>(TroisChiffes - Chiffre2 * pow(10,2));

    if (TroisChiffes != 0){
        if (Chiffre2 > 1 and EntierReste2Chiffre == 0 and EntierReste == 0){
            Centaine = ConversionNormale(Chiffre2) + "-cents";

        } else if (Chiffre2 == 1 and EntierReste2Chiffre > 1){
            Centaine = "cent-" + ConversionDeuxChiffres(Chiffre1, Chiffre0, EntierReste2Chiffre);

        } else if (Chiffre2 == 1 and EntierReste2Chiffre == 1) {
            Centaine = "cent-un";

        } else if (Chiffre2 > 1 and EntierReste2Chiffre == 0){
            Centaine = ConversionNormale(Chiffre2) + "-cent";

        } else if (Chiffre2 > 1 and EntierReste2Chiffre > 0){
            Centaine = ConversionNormale(Chiffre2) + "-cent-" + ConversionDeuxChiffres(Chiffre1, Chiffre0, EntierReste2Chiffre);

        } else{
            Centaine = ConversionDeuxChiffres(Chiffre1, Chiffre0, EntierReste2Chiffre);
        }
    }
    return Centaine;
}

string Conversion(int Centaine, int Categorie, long long Reste){
    string Conversion;
    string ConvertiCentaine = ConversionCentaine(Centaine, Reste);

    switch (Categorie) {
        case 9:
            Conversion = (Centaine > 1 ? ConvertiCentaine + "-" : (Centaine == 1 ? "un-" : "")) + "milliard" + (Centaine > 1 ? "s" : "") + (Reste > 0 ? "-" : " de francs")/* + (Reste == 1 ? "et-" : "")*/; break;
        case 6:
            Conversion += (Centaine > 1 ? ConvertiCentaine + "-" : (Centaine == 1 ? "un-" : "")) + "million" + (Centaine > 1 ? "s" : "") + (Reste > 0 ? "-" : " de francs")/* + (Reste == 1 ? "et-" : "")*/; break;
        case 3:
            Conversion += (Centaine > 1 ? ConvertiCentaine + "-" : "") + "mille" + (Reste > 0 ? "-" : ""); break;
        case 0:
            Conversion += (Centaine > 1 ? ConvertiCentaine + " " : (Centaine == 1 ? "un " : "zero ")) + "franc" + (Centaine > 1 ? "s" : ""); break;
        case -2:
            if (Centaine != 0){
                Conversion += (Centaine > 1 ? ConvertiCentaine + " " : "un ") + "centime" + (Centaine > 1 ? "s" : "");
            } break;
    }
    return Conversion;
}

string montantEnToutesLettres(long double Montant) {
    const double MontantTropGrand = 1000000000000.;
    const double MontantTropPetit = 0.;
    long long Entier = 0;
    int Decimales = 0;

    // check la valeur entrée par l'utilisateur
    if (Montant < MontantTropPetit or Montant > MontantTropGrand){
        return "Erreur, entrez un nombre compris entre 0 compris et 10 puissance 12 non compris";
    } else {

        Decimales = ArrondirDecimales(Montant, Entier);

        cout << "Resultat>" << Entier << "<>" << Decimales << endl;

        long long EntierTemp = Entier;
        string ConversionEntier;
        string ConversionDecimale;
        string ConversionFinale;
        int Decomposition;

        while (EntierTemp > 0) {
            int NbCat = Category(PremierExposant(EntierTemp));
            Decomposition = DecompositionMontantCategory(EntierTemp, NbCat);
            ConversionEntier += Conversion(Decomposition, NbCat, EntierTemp);
        }

        if (Decimales > 0){
            ConversionDecimale += Conversion(Decimales, -2, Decimales);
        }

        if (Entier == 0 and Decimales == 0){
            ConversionFinale = "zero franc";
        } else if (Entier == 0 and Decimales > 0){
            ConversionFinale = ConversionDecimale;
        } else if (Entier > 0 and Decimales == 0) {
            ConversionFinale = ConversionEntier;
        } else{
            ConversionFinale = ConversionEntier + " et " + ConversionDecimale;
        }

        cout << endl;
        return ConversionFinale;
    }
}