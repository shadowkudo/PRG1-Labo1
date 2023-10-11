/* ---------------------------
Laboratoire |   01-MontantEnToutesLettres
Auteur(s)   |   David Schildböck - Agron Markaj
Date début  |   06.10.2023
Date fin    |   12.10.2023 (2359)
But         |   convertisseur nombre mathématique au langage français
Remarque(s) |   - pas de tableaux, pas de redondance de code, pas de plagiat
                - règles du Français respectées selon https://www.dictionnaire-academie.fr/article/QDL057
                - arrondi 0.995 à 1.00
Source(s)   |   - static_cast   ->  https://en.cppreference.com/w/cpp/language/static_cast <> pour convertir les différents types de données nombre (p. ex : long double à long long)
                - floor()       ->  https://en.cppreference.com/w/cpp/numeric/math/floor <> fonction mathématique
                - round()       ->  https://en.cppreference.com/w/cpp/numeric/math/round <> fonction mathématique
                - trunc()       ->  https://en.cppreference.com/w/cpp/numeric/math/trunc <> fonction mathématique
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
Retourne    |   un int
But         |   Connaître la catégorie de l'exposant demandé
Exemple     |   Exposant = 5 <> 3
--------------------------- */
int Categorie(int Exposant){
    switch (Exposant) {
        case 11:
        case 10:
        case 9: return 9; // -> milliard
        case 8:
        case 7:
        case 6: return 6; // -> million
        case 5:
        case 4:
        case 3: return 3; // -> mille
        case 2:
        case 1:
        default: return 0; // -> centaine+dizaine+unité
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
    int ExposantDebut;
    int ExposantReste;
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
Retourne    |   un string
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
Retourne    |   un string
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
Retourne    |   un string
But         |   Convertir le nombre (de 2 chiffres seulement), contrôle les cas spéciaux.
Exemple     |   Chiffre1 = 4, Chiffre0 = 1, Nombre = 41 <> Conversion = "quarante-et-un"
--------------------------- */
string ConversionDeuxChiffres(int Chiffre1, int Chiffre0, int Nombre){
    if (Nombre < 20 and Nombre >= 10){
        return ConversionNormale(Nombre);
    } else if (Chiffre1 > 1){
        switch (Chiffre0) {
            case 0: return ConversionDizaine(Chiffre1);
            case 1: return ConversionDizaine(Chiffre1) + "-et-un";
            default: return ConversionDizaine(Chiffre1) + "-" + ConversionNormale(Chiffre0);
        }
    } else if (Nombre < 10){
        return ConversionNormale(Chiffre0);
    }
}
/*---------------------------
Nom         |   ConversionCentaine
Paramètre(s)|   int TroisChiffes, long long EntierReste
Retourne    |   un string
But         |   Convertir le nombre (3 chiffres max), contrôle les règles Français pour la centaine.
Exemple     |   TroisChiffes = 143, EntierReste = 102 <> Centaine = "cent-quarante-trois"
--------------------------- */
string ConversionCentaine(int TroisChiffes, long long EntierReste){
    int Chiffre2 = PremierChiffre(TroisChiffes, 2); // la centaine
    int Chiffre1 = PremierChiffre(TroisChiffes, 1); // la dizaine
    int Chiffre0 = PremierChiffre(TroisChiffes, 0); // l'unité
    int EntierReste2Chiffres = static_cast<int>(TroisChiffes - Chiffre2 * pow(10,2)); // le nombre sans la centaine

    if (Chiffre2 > 1){
        return ConversionNormale(Chiffre2) + "-cent" +
            (EntierReste2Chiffres == 0 ? (EntierReste == 0 ? "s" : "") : "-" +
            ConversionDeuxChiffres(Chiffre1, Chiffre0, EntierReste2Chiffres)); // visibilité meilleure que sur une ligne
        } else if (Chiffre2 == 1){
        switch (EntierReste2Chiffres) { // Impossible pour l'entier d'être négatif, donc default toujours positif.
            case 1: return "cent-un";
            case 0: return "cent";
            default: return "cent-" + ConversionDeuxChiffres(Chiffre1, Chiffre0, EntierReste2Chiffres);
        }
    } else{
        return ConversionDeuxChiffres(Chiffre1, Chiffre0, EntierReste2Chiffres);
    }
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
        case 9: // règles Français pour le milliard
            Conversion = (Centaine > 1 ? ConvertiCentaine + "-" : (Centaine == 1 ? "un-" : "")) + "milliard" + (Centaine > 1 ? "s" : "") + (Reste > 0 ? "-" : " de francs"); break;
        case 6: // règles Français pour le million
            Conversion = (Centaine > 1 ? ConvertiCentaine + "-" : (Centaine == 1 ? "un-" : "")) + "million" + (Centaine > 1 ? "s" : "") + (Reste > 0 ? "-" : " de francs"); break;
        case 3: // règles Français pour le millier
            Conversion = (Centaine > 1 ? ConvertiCentaine + "-" : "") + "mille" + (Reste > 0 ? "-" : " francs"); break;
        case 0: // règles Français pour un ou zero
            Conversion = (Centaine > 1 ? ConvertiCentaine + " " : (Centaine == 1 ? "un " : "zero ")) + "franc" + (Centaine > 1 ? "s" : ""); break;
        case -2: // règles Français pour le centime
            Conversion += (Centaine > 1 ? ConvertiCentaine + " " : "un ") + "centime" + (Centaine > 1 ? "s" : ""); break;
        default: cerr << "Erreur survenue lors dans la fonction ConversionCentrale"; // valeur default du switch jamais atteint dans ce programme, seulement ici pour ne pas recevoir un avertissement (jaune)
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
Exemple     |   montant = 200200.02  <> ConversionFinale = "deux-cent-mille-deux-cents francs et deux centimes"
--------------------------- */
string montantEnToutesLettres(long double montant) {
    // Déclaration des variables pour la fonction principale
    const double MontantTropGrand = 1000000000000.;
    const double MontantTropPetit = 0.;
    long long Entier = 0;
    int Decimales;
    int Decomposition;
    int NbCat;
    string ConversionFinale;
    string ConversionEntier;
    string ConversionDecimale;

    Decimales = ArrondirDecimales(montant, Entier);

    // Contôle de l'entrée
    if (montant < MontantTropPetit){
        return "erreur : montant negatif";
    } else if (static_cast<double>(Entier) >= MontantTropGrand){
        return  "erreur : montant trop grand";
    } else {

        // Conversion de l'entier
        long long EntierTemp = Entier; // Déclaration d'une variable Temp, car Entier sera référencié dans une fonction

        while (EntierTemp > 0) {
            NbCat = Categorie(PremierExposant(EntierTemp));
            Decomposition = DecompositionMontantCategorie(EntierTemp, NbCat);
            ConversionEntier += ConversionCentrale(Decomposition, NbCat, EntierTemp);
        }

        // Conversion des décimales
        if (Decimales > 0){
            ConversionDecimale += ConversionCentrale(Decimales, -2, Decimales);
        }

        // Ajout des conversions entier et décimales selon cas 0, avec ou sans décimales
        ConversionFinale = Entier == 0 ? (Decimales == 0 ? "zero franc" : ConversionDecimale) : (Decimales == 0 ? ConversionEntier : ConversionEntier + " et " + ConversionDecimale);

        return ConversionFinale;
    }
}
