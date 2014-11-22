#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef TABR_HPP
#define TABR_HPP

typedef struct _maillon{
     int valeur;
    _maillon *sag;
    _maillon *sad;
} Maillon;

struct ABR{
       Maillon* racine;
};

struct Intervalle{
       int debut;
       int fin;
       };
       
struct Case{
       Intervalle intervalle;
       ABR abr;
       };     

struct TABR{
       int nombreCase;
       Case tableau[100];
       };
       
void initialiser(TABR &tabr);
void creerCase(TABR &tabr, int deb, int fin);
void afficherT(TABR tabr);
            
#endif
