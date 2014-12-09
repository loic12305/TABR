#include "TABR.cpp"


int main()
{
       TABR tabr;

       initialiser(tabr);
       //creerCase(tabr, 1, 10);
       //creerCase(tabr, 9, 22);
       //creerCase(tabr, 50, 75);
       //creerCase(tabr, 78, 80);
       //afficherT(tabr);

       parserFichier(tabr, "/media/Documents/loic/MASTER1/S1/ALGO/Projet/Source/", "input.txt");
       afficherT(tabr);



    return 0;
}
