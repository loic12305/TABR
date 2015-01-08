#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <limits.h>
#include <algorithm>    
#include <vector>       
#include <limits>

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
string afficherT(TABR tabr);
void parserFichier(TABR &tabr, string fich);
void ajouterABR(ArbreBinaire **abr, int valeur);
string afficherABR(ArbreBinaire *abr);
bool verifierTABR(ArbreBinaire *abr);
bool verifierABR(ArbreBinaire *abr, Intervalle i);
bool verifierABRGauche(ArbreBinaire *abr, Intervalle i, int racine);
bool verifierABRDroit(ArbreBinaire *abr, Intervalle i, int racine);
void exportTABR(TABR tabr);
void generer_aleatoire(int cases, int max);
bool estPresent(vector<int> tab,int n);
void fusion(TABR tabr,int indice);
void tabrToAbr(TABR tabr);
bool insertionEntier(TABR &tabr, int val);

#endif
