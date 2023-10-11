/* ---------------------------
Laboratoire :   01-MontantEnToutesLettres
Auteur(s)   :   David Schildböck - Agron Markaj
Date        :   06.10.2023
But         :   convertisseur nombre mathématique au langage français
Remarque(s) :   - pas de tableaux, pas de redondance de code, pas de plagiat
                - règles du Français respectées selon https://www.dictionnaire-academie.fr/article/QDL057
                - arrondi 0.995 à 1.00
Source(s)   :   - static_cast   ->  https://en.cppreference.com/w/cpp/language/static_cast
                - floor()       ->  https://en.cppreference.com/w/cpp/numeric/math/floor
                - round()       ->  https://en.cppreference.com/w/cpp/numeric/math/round
                - trunc()       ->  https://en.cppreference.com/w/cpp/numeric/math/trunc
--------------------------- */
#include <iostream>
#include <cmath>

using namespace std;

/*---------------------------
Nom         |   PremierExposant
Paramètre(s)|   long long Nombre
Retourne    |   int ExposantDebut
But         |   Trouver le premier exposant dont le chiffre n'est pas égal à 0.
Exemple     |   Nombre = 4320 <> Chiffre 4 <> Exposant en base 10 = 3
--------------------------- */
 int PremierExposant(long long Nombre){
    auto ExposantDebut = static_cast<int>(floor(log10(Nombre)));

    return ExposantDebut;
}

/*---------------------------
Nom         |   PremierChiffre
Paramètre(s)|   long long Nombre, int ChercheExposant
Retourne    |   int ExposantDebut
But         |   Trouver le chiffre d'un nombre donné selon son exposant en base 10.
Exemple     |   Nombre = 213, ChercheExposant = 0 <> on veut retourner la valeur 3
--------------------------- */
int PremierChiffre(long long Nombre, int ChercheExposant){
    int ChiffreTrouve = 0;
    int ExposantDebut = PremierExposant(Nombre);

    for (; ExposantDebut >= ChercheExposant; ExposantDebut--) {
        ChiffreTrouve = static_cast<int>(trunc(static_cast<long double>(Nombre) / pow(10, ExposantDebut)));
        Nombre -= static_cast<long long>(ChiffreTrouve * pow(10, ExposantDebut));
    }
    return ChiffreTrouve;
}

/*---------------------------
Nom         |   ArrondirDecimales
Paramètre(s)|   long double Montant, long long& Entier (référence)
Retourne    |   int Decimales
But         |   Séparer l'entier (à gauche de la virgule) et les décimales (à droite de la virgule),
                pour arrondir les décimales et ajouter un à l'entier quand Decimales > 99.
Exemple     |   Montant = 1.995 <> Entier = 2, Decimales = 0
--------------------------- */
int ArrondirDecimales(long double Montant, long long& Entier){

    Entier = static_cast<long long>(Montant);
    auto Decimales = static_cast<int>(round((Montant - Entier)*100));

    if (Decimales > 99) {
        Entier++;
        Decimales = 0;
    }
    return Decimales;
}

/*---------------------------
Nom         |   Categorie
Paramètre(s)|   int Exposant
Retourne    |   int valeur x
But         |   Connaître la catégorie de l'exposant demandé
Exemple     |   Exposant = 5 <> 3
--------------------------- */
int Categorie(int Exposant){
    int Exp;
    switch (Exposant) {
        case 11:;
        case 10:;
        case 9: return 9;
        case 8:;
        case 7:;
        case 6: return 6;
        case 5:;
        case 4:;
        case 3: return 3;
        case 2:;
        case 1:;
        case 0: return 0;
    }
}

/*---------------------------
Nom         |   DecompositionMontantCategorie
Paramètre(s)|   long long& Entier (référence), int ExposantCategorie
Retourne    |   int Decomposition
But         |   Décomposer l'entier selon catégorie
Exemple     |   Entier = 75435, ExposantCategorie = 3 (millier) <> Decomposition = 75
--------------------------- */
int DecompositionMontantCategorie(long long& Entier, int ExposantCategorie){
    int Decomposition = 0;
    int ExposantDebut = 0;
    int ExposantReste = 0;
    ExposantDebut = PremierExposant(Entier);
    ExposantReste = ExposantDebut - ExposantCategorie;

    for (; ExposantDebut >= ExposantCategorie; ExposantDebut--) {

        auto NbTemp = static_cast<long long>(floor(static_cast<long double>(Entier) / pow(10, ExposantDebut)));
        Entier -= static_cast<long long>(static_cast<long double>(NbTemp) * pow(10, ExposantDebut));
        Decomposition += static_cast<int>(static_cast<long double>(NbTemp) * pow(10, ExposantReste));
        ExposantReste--;

    }
    return Decomposition;
}

/*---------------------------
Nom         |   ConversionNormale
Paramètre(s)|   int Nombre
Retourne    |   string valeur ""
But         |   Convertir le nombre en string
Exemple     |   Nombre = 14 <> quatorze
--------------------------- */
string ConversionNormale(int Nombre){

    switch (Nombre) {
        case 2: return "deux";
        case 3: return "trois";
        case 4: return "quatre";
        case 5: return "cinq";
        case 6: return "six";
        case 7: return "sept";
        case 8: return "huit";
        case 9: return "neuf";
        case 10: return "dix";
        case 11: return "onze";
        case 12: return "douze";
        case 13: return "treize";
        case 14: return "quatorze";
        case 15: return "quinze";
        case 16: return "seize";
        case 17: return "dix-sept";
        case 18: return "dix-huit";
        case 19: return "dix-neuf";
        default: return  "";
    }
}

/*---------------------------
Nom         |   ConversionDizaine
Paramètre(s)|   int Chiffre
Retourne    |   string valeur ""
But         |   Convertir le chiffre en string (pour les dizaines)
Exemple     |   Chiffre = 4 <> quarante
--------------------------- */
string ConversionDizaine(int Chiffre){

    switch (Chiffre) {
        case 1: return "dix";
        case 2: return "vingt";
        case 3: return "trente";
        case 4: return "quarante";
        case 5: return "cinquante";
        case 6: return "soixante";
        case 7: return "septante";
        case 8: return "huitante";
        case 9: return "nonante";
        default: return "";
    }
}

/*---------------------------
Nom         |   ConversionDeuxChiffres
Paramètre(s)|   int Chiffre1, int Chiffre0, int Nombre
Retourne    |   string Conversion
But         |   Convertir le nombre (de 2 chiffres seulement), contrôle les cas spéciaux
Exemple     |   Chiffre1 = 4, Chiffre0 = 1, Nombre = 41 <> Conversion = "quarante-et-un"
--------------------------- */
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

/*---------------------------
Nom         |   ConversionCentaine
Paramètre(s)|   int TroisChiffes, long long EntierReste
Retourne    |   string Centaine
But         |   Convertir le nombre (3 chiffres max), contrôle les cas spéciaux avec cent(s)
Exemple     |   TroisChiffes = 143, EntierReste = 102 <> Centaine = "cent-quarante-trois"
--------------------------- */
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

        } else if (Chiffre2 == 1 and EntierReste2Chiffre == 0) {
            Centaine = "cent";

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

/*---------------------------
Nom         |   ConversionCentrale
Paramètre(s)|   int Centaine, int Categorie, long long Reste
Retourne    |   string Conversion
But         |   Selon les différents cas de la langue française,
                convertir le nombre en string selon la catégorie donnée
Exemple     |   Centaine = 1, Categorie = 6, Reste = 0 <> Reste = "un-million de francs"
--------------------------- */
string ConversionCentrale(int Centaine, int Categorie, long long Reste){
    string Conversion;
    string ConvertiCentaine = ConversionCentaine(Centaine, Reste);

    switch (Categorie) {
        case 9:
            Conversion = (Centaine > 1 ? ConvertiCentaine + "-" : (Centaine == 1 ? "un-" : "")) + "milliard" + (Centaine > 1 ? "s" : "") + (Reste > 0 ? "-" : " de francs"); break;
        case 6:
            Conversion += (Centaine > 1 ? ConvertiCentaine + "-" : (Centaine == 1 ? "un-" : "")) + "million" + (Centaine > 1 ? "s" : "") + (Reste > 0 ? "-" : " de francs"); break;
        case 3:
            Conversion += (Centaine > 1 ? ConvertiCentaine + "-" : "") + "mille" + (Reste > 0 ? "-" : " francs"); break;
        case 0:
            Conversion += (Centaine > 1 ? ConvertiCentaine + " " : (Centaine == 1 ? "un " : "zero ")) + "franc" + (Centaine > 1 ? "s" : ""); break;
        case -2:
            if (Centaine != 0){
                Conversion += (Centaine > 1 ? ConvertiCentaine + " " : "un ") + "centime" + (Centaine > 1 ? "s" : "");
            } break;
    }
    return Conversion;
}

/*---------------------------
Nom         |   montantEnToutesLettres (Fonction principale)
Paramètre(s)|   long double montant
Retourne    |   string ConversionFinale
But         |   - Contrôler l'entrée de l'utilisateur (0 <= montant < 10 puissance 12)
                - Séparer le montant en entier et décimales
                - Continuer à convertir l'entier tant que le nombre est plus grand que 0
                - Contrôler les cas spéciaux (montant = 0, sans décimales, ...)
Exemple     |   montant = 200200.02  <> ConversionFinale = "deux-cent-mille-deux-cents francs et -deux centimes"
--------------------------- */
string montantEnToutesLettres(long double montant) {
    const double MontantTropGrand = 1000000000000.;
    const double MontantTropPetit = 0.;
    long long Entier = 0;
    int Decimales = 0;
    string ConversionFinale;

    Decimales = ArrondirDecimales(montant, Entier);

    // check la valeur entrée par l'utilisateur
    if (montant < MontantTropPetit){
        return "erreur : montant negatif";
    } else if (static_cast<double>(Entier) >= MontantTropGrand){
        return  "erreur : montant trop grand";
    } else {

        long long EntierTemp = Entier;
        string ConversionEntier;
        string ConversionDecimale;
        int Decomposition;

        while (EntierTemp > 0) {
            int NbCat = Categorie(PremierExposant(EntierTemp));
            Decomposition = DecompositionMontantCategorie(EntierTemp, NbCat);
            ConversionEntier += ConversionCentrale(Decomposition, NbCat, EntierTemp);
        }

        if (Decimales > 0){
            ConversionDecimale += ConversionCentrale(Decimales, -2, Decimales);
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

        return ConversionFinale;
    }
}