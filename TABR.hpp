#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <limits.h>

using namespace std;

#ifndef TABR_HPP
#define TABR_HPP

typedef struct ArbreBinaire
{
    int valeur;
    struct ArbreBinaire *sag;
    struct ArbreBinaire *sad;
} ArbreBinaire ;

struct Intervalle{
       int debut;
       int fin;
       };

struct Case{
       Intervalle intervalle;
       ArbreBinaire *abr;
       };

struct TABR{
       int nombreCase;
       vector<Case> tableau;
       };

void initialiser(TABR &tabr);
void creerCaseArbre(TABR &tabr, vector<int> tab, int deb, int fin);
void afficherT(TABR tabr);
void parserFichier(TABR &tabr, string fich);
void ajouterABR(ArbreBinaire **abr, int valeur);
void afficherABR(ArbreBinaire *abr);
bool verifierTABR(ArbreBinaire *abr);
bool verifierABR(ArbreBinaire *abr, Intervalle i);
bool verifierABRGauche(ArbreBinaire *abr, Intervalle i, int racine);
bool verifierABRDroit(ArbreBinaire *abr, Intervalle i, int racine);

#endif
