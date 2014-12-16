#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#ifndef TABR_HPP
#define TABR_HPP

typedef struct node
{
    unsigned int key;
    struct node *left;
    struct node *right;
} node ;

struct Intervalle{
       int debut;
       int fin;
       };

struct Case{
       Intervalle intervalle;
       node *abr;
       };

struct TABR{
       int nombreCase;
       vector<Case> tableau;
       };

void initialiser(TABR &tabr);
void creerCaseArbre(TABR &tabr, vector<int> tab, int deb, int fin);
void afficherT(TABR tabr);
void parserFichier(TABR &tabr, string emplacement, string fich);
void addNode(node **tree, unsigned int key);
void printTree(node *tree);
#endif
