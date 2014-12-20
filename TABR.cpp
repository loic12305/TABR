#include "TABR.hpp"


void initialiser(TABR &tabr)
{
       tabr.nombreCase= 0;

}


void ajouterABR(ArbreBinaire **abr, int valeur)
{
    ArbreBinaire *tmpNoeud;
    ArbreBinaire *tmpAbr = *abr;

    ArbreBinaire *elem = new ArbreBinaire;
    elem->valeur = valeur;
    elem->sag = NULL;
    elem->sad = NULL;

    if(tmpAbr)
    do
    {
        tmpNoeud = tmpAbr;
        if(valeur > tmpAbr->valeur )
        {
            tmpAbr = tmpAbr->sad;
            if(!tmpAbr) tmpNoeud->sad = elem;
        }
        else
        {
            tmpAbr = tmpAbr->sag;
            if(!tmpAbr) tmpNoeud->sag = elem;
        }
    }
    while(tmpAbr);
    else  *abr = elem;
}


void creerCaseArbre(TABR &tabr, vector<int> tab, int deb, int fin)
{
  Intervalle intervalle;
  intervalle.debut = deb;
  intervalle.fin = fin;
  
  Case c;
  c.intervalle = intervalle;
         
  ArbreBinaire *arbre = NULL;
  c.abr = arbre;

  for(int i=(tab.size()-1);i>=0;i--)
    {
      ajouterABR(&c.abr, tab[i]);
      //cout <<  tab[i] << " ajoute" << endl;
    }
  tabr.tableau.push_back(c);
  tabr.nombreCase++;
  
}

void parserFichier(TABR &tabr, string fich)
{
    int indexFin = 0;
    string intervalle = "";

    ifstream fichier(fich);

    if(fichier)
    {
        string ligne;
        while(getline(fichier, ligne))
        {
            vector<int> tabTemp;

            /* On récupère l'intervalle de la ligne */
            indexFin = ligne.find(";");
            intervalle = ligne.substr(0, indexFin);
            int debutIntervalle = atoi(intervalle.substr(0, intervalle.find(":")).c_str());
            int finIntervalle = atoi(intervalle.substr(intervalle.find(":")+1, intervalle.size()).c_str());

            /* parcours des nombres de la ligne */
            int indexDebutNombre = indexFin;
            int indexFinNombre = ligne.find(":", indexDebutNombre);
            do
	    {
	      int nombre = atoi(ligne.substr(indexDebutNombre + 1, indexFinNombre - 1).c_str());
                //Ajouter les nombres à l'arbre de manière à avoir un arbre biniaire, on utilise un tableau temporaire car la racine si situe à la fin de la ligne
                tabTemp.push_back(nombre);
                indexDebutNombre = indexFinNombre;
                indexFinNombre = ligne.find(":", indexDebutNombre+1);
            }
            while(indexDebutNombre < ligne.size());
	    creerCaseArbre(tabr, tabTemp, debutIntervalle, finIntervalle);
        }


    }
    else
    {
        cout << "le fichier n'a pas pu etre ouvert" << endl;
    }
}

void afficherT(TABR tabr)
{
  int i = 0;
  while(i < tabr.nombreCase)
  {
    cout << tabr.tableau[i].intervalle.debut<<":"<< tabr.tableau[i].intervalle.fin;
    cout << ";";
    afficherABR(tabr.tableau[i].abr);
    cout << endl;
    i++;
  }
}

void afficherABR(ArbreBinaire *abr)
{
    if(!abr) return;

    if(abr->sag)  afficherABR(abr->sag);

    cout << abr->valeur << ":";

    if(abr->sad) afficherABR(abr->sad);
}
