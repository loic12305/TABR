#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#ifndef TABR_HPP
#define TABR_HPP

typedef struct _abr{
     int valeur;
    _abr *sag;
    _abr *sad;
} ABR;

struct Intervalle{
       int debut;
       int fin;
       };

struct Case{
       Intervalle intervalle;
       ABR *abr;
       };

struct TABR{
       int nombreCase;
       vector<Case> tableau;
       };

void initialiser(TABR &tabr);
void creerCaseVide(TABR &tabr, int deb, int fin);
void insertionABR(ABR* abr, vector<int>, int debut, int fin);
void creerCaseArbre(TABR &tabr, vector<int> tab, int deb, int fin);
void afficherT(TABR tabr);
void afficherArbreBinaire(ABR* abr);
void ajoutElement(TABR &tabr, int element);
void parserFichier(TABR &tabr, string emplacement, string fich);

#endif
