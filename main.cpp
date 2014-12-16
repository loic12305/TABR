#include "TABR.cpp"


int main()
{
       TABR tabr;

       initialiser(tabr);
       parserFichier(tabr, "/media/Documents/loic/MASTER1/S1/ALGO/Projet/Source/", "input.txt");
       afficherT(tabr);      



    return 0;
}
