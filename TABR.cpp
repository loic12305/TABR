#include "TABR.hpp"


void initialiser(TABR &tabr)
{
       tabr.nombreCase= 0;
       
}


void creerCase(TABR &tabr, int deb, int fin)
{
       Intervalle intervalle;
       intervalle.debut = deb;
       intervalle.fin = fin;
       
       ABR abr;
       abr.racine = NULL;
       
       Case c;
       c.intervalle = intervalle;
       c.abr = abr;
       
       tabr.tableau[tabr.nombreCase] = c;
       tabr.nombreCase++;
}


void afficherT(TABR tabr)
{
  int i = 0;
  while(i < tabr.nombreCase)
  {
    cout << tabr.tableau[i].intervalle.debut<<" .. "<< tabr.tableau[i].intervalle.fin <<endl;
    i++;
  }
}
