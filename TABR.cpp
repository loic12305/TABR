#include "TABR.hpp"


void initialiser(TABR &tabr)
{
       tabr.nombreCase= 0;

}


/* On est obligé de mettre un "pointeur de pointeur" car on veut agir sur le pointeur du TABR par référence */
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

bool verifierABRGauche(ArbreBinaire *abr, Intervalle i, int racine)
{
  if(!abr)
    return true;
  else
  {
    if((abr->valeur < racine) && (abr->valeur >= i.debut) && (abr->valeur <= i.fin))
    {
      bool res1 = verifierABRGauche(abr->sag, i, abr->valeur);
      bool res2 = verifierABRDroit(abr->sad, i, abr->valeur);
      return (res1 && res2);
    }
    else
      return false;
  }
}

bool verifierABRDroit(ArbreBinaire *abr, Intervalle i, int racine)
{
  if(!abr)
    return true;
  else
  {
    if((abr->valeur > racine) && (abr->valeur >= i.debut) && (abr->valeur <= i.fin))
    {
      bool res1 = verifierABRGauche(abr->sag, i, abr->valeur);
      bool res2 = verifierABRDroit(abr->sad, i, abr->valeur);
      return (res1 && res2);
    }
    else
      return false;
  }
}

bool verifierABR(ArbreBinaire *abr, Intervalle i)
{
  if(!abr)
    return true;
  else
  {
    //si la valeur du noeud respecte les contraintes de l'intervalle, alors on vérifie les noeuds du SAG et du SAD
    if((abr->valeur >= i.debut) && (abr->valeur <= i.fin))
    {
      cout << abr->valeur << endl;
      bool res1 = verifierABRGauche(abr->sag, i, abr->valeur);
      bool res2 = verifierABRDroit(abr->sad, i, abr->valeur);
      return (res1 && res2);
    }
    else
      return false;
  }
}

bool verifierTABR(TABR tabr)
{
  bool resIntervalle = true;
  bool resAbr = true;
  int finTmp = INT_MIN;
  int i = 0;

  while(i < tabr.nombreCase && resIntervalle == true && resAbr == true)
  {
    //Verifie propriété b et c : si debut>fin-1 et fin>debut alors fin>fin-1 donc disjoints et croissant
    if(tabr.tableau[i].intervalle.debut > finTmp)
    {
      //Verifie propriété a : debut > fin
      if(tabr.tableau[i].intervalle.debut > tabr.tableau[i].intervalle.fin)
        resIntervalle = false;
    }
    else
      resIntervalle = false;

    finTmp = tabr.tableau[i].intervalle.fin;
    //On teste la composition de l'arbre que si l'intervalle est correcte
    if(resIntervalle == true)
      resAbr = verifierABR(tabr.tableau[i].abr, tabr.tableau[i].intervalle);
    cout << i << endl;
    i++;
  }

  return (resIntervalle && resAbr);
}



