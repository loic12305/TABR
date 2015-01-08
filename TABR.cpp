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


void suffixe_abr(ArbreBinaire *abr, vector<int> &res)
{
  if(abr->sag) suffixe_abr(abr->sag, res);

  if(abr->sad) suffixe_abr(abr->sad, res);

  res.push_back(abr->valeur);
}


void creerCaseArbre(TABR &tabr, vector<int> tab, int deb, int fin)
{
  Intervalle intervalle;
  intervalle.debut = deb;
  intervalle.fin = fin;
  vector<int> suffixe;
  
  Case c;
  c.intervalle = intervalle;
         
  ArbreBinaire *arbre = NULL;
  c.abr = arbre;

  for(int i = (tab.size()-1); i>=0; i--)
    {
      ajouterABR(&c.abr, tab[i]);
    }

  bool test = true;
  suffixe.clear();
  suffixe_abr(c.abr, suffixe);

  //ils ont forcement la meme taille
  for(int j=0; j<suffixe.size(); j++)
    {
      if(tab[j] != suffixe[j])
	{
	  test = false;
	}
    }
  
  if(test)
    {
      tabr.tableau.push_back(c);
      tabr.nombreCase++;
      //cout << "ajout de la ligne OK" << endl;
    }
  else
    {
      cout << "La ligne n'est pas bien formé " << endl;
    }
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


/*
 * Dans notre cas, verifier TABR ne teste finalement que les intervalles,
 * En effet, dans notre construction de l'ABR, il est toujours correct.
 * Pour verifier le fichier, il faut faire un parcours suffixe des arbres 
 * et compare avec la ligne correspondante du fichier (fait lors de l'insertion).
 */
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

void exportTABR(TABR tabr)
{
  ofstream fichier("output.txt", ios::out | ios::trunc);

  if(fichier)
    {
      fichier << afficherT(tabr);
 
      fichier.close();
    }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
}

string afficherT(TABR tabr)
{
  int i = 0;
  string resultat = "";
  string tmp = "";

  while(i < tabr.nombreCase)
    {
      resultat += to_string(tabr.tableau[i].intervalle.debut) +":" +  to_string(tabr.tableau[i].intervalle.fin);
      resultat += ";";
      tmp = afficherABR(tabr.tableau[i].abr);
      tmp.replace(tmp.size()-1,1,"");
      resultat += tmp;
      resultat += "\n";
      i++;
    }
  return(resultat);
}

string afficherABR(ArbreBinaire *abr)
{
  string resultat = "";

  if(!abr) return resultat ;

  if(abr->sag)  resultat += afficherABR(abr->sag);

  if(abr->sad) resultat += afficherABR(abr->sad);

  resultat = resultat + to_string(abr->valeur) + ":";

  return(resultat);
}


///////////////////////////////////////////////
// Générer tout un TABR de maniere aléatoire //
///////////////////////////////////////////////
void generer_aleatoire(int n, int m)
{
  int nb_elmt_max,nb_elmt,nb_rand,nombre_aleatoire;
  TABR tabr;
  bool existe;
  vector<int> tab_rand;
  Intervalle intervalle;
  Case c;
  ArbreBinaire *arbre = NULL;
  
  initialiser(tabr); // initialise un TABR
  srand(time(0));
  // ajouter 'n' cases au tableau
  tabr.nombreCase=0;

  // on genere (n*2)-2 nombre aléatoire
  nb_rand = (n*2)-2;


  //
  // CREATION D'UN TABLEAU DE nb_rand RAND
  //
  for(int i=1;i<=nb_rand;i++)
    {
      nombre_aleatoire = rand()%(m-1)+1;
      if(estPresent(tab_rand,nombre_aleatoire))
	i--;
      else
	  tab_rand.push_back(nombre_aleatoire);
    }



  //trie tab_rand
  sort(tab_rand.begin(),tab_rand.end());

  //on cree la premier case en dehors de la boucle 
  //creer un interval
  intervalle.debut = 1;
  intervalle.fin = tab_rand.at(0);
  // creer la premiere case
  c.intervalle = intervalle;
  arbre = NULL; //cree un arbre
  c.abr = arbre; //ajout de l'arbre
  tabr.tableau.push_back(c); //ajout de la case au tabr
  tabr.nombreCase++;

  //initialiser les case du TABR
  for(int i=1; i<nb_rand-1; i++)
    {
      //creer un interval
      intervalle.debut = tab_rand.at(i);
      i++;
      intervalle.fin = tab_rand.at(i);

      //cree la case
      c.intervalle = intervalle;
      arbre = NULL; //cree un arbre
      
      c.abr = arbre; //ajout de l'arbre
      tabr.tableau.push_back(c); //ajout de la case au tabr
      tabr.nombreCase++;
    } // end for

  // creer la derniere case
  intervalle.debut = tab_rand.at(nb_rand-1);
  intervalle.fin = m;
  c.intervalle = intervalle;
  arbre = NULL; //cree un arbre
  c.abr = arbre; //ajout de l'arbre
  tabr.tableau.push_back(c); //ajout de la case au tabr
  tabr.nombreCase++;

  // On obtient un TABR de n case avec les intervals : reste à creer les arbres

  for(int i=0 ; i<tabr.nombreCase ;i++)
    {
      cout<<tabr.tableau.at(i).intervalle.debut<<".."<<tabr.tableau.at(i).intervalle.fin<<endl;
      nb_elmt_max = (tabr.tableau.at(i).intervalle.fin - tabr.tableau.at(i).intervalle.debut) +1; //nb element max de l'arbre
      nb_elmt = rand()%(nb_elmt_max-1)+1; //nb element random
      //cout<<"::::::::::::::"<<rand()%6<<endl; // nb le rand à generer
      cout<<nb_elmt<<endl; // nb le rand à generer

      tab_rand.clear();
 
      for(int z=0;z<nb_elmt;z++)
      	{
	  nombre_aleatoire = rand()%(tabr.tableau.at(i).intervalle.fin-tabr.tableau.at(i).intervalle.debut)+tabr.tableau.at(i).intervalle.debut;
	  if(estPresent(tab_rand,nombre_aleatoire))
      	    z--;
      	  else
      	    tab_rand.push_back(nombre_aleatoire);
	  
	}
      for(int j=0 ; j<tab_rand.size() ; j++)
	ajouterABR(&tabr.tableau.at(i).abr, tab_rand[j]);

      cout<<endl;
    }

  int i = 0;
  
  cout<<afficherT(tabr);
}


bool estPresent(vector<int> tab,int n)
{
      for(int y=0;y<tab.size();y++)
	if(n == tab.at(y))
	  return true;
      return false;
}


void tabrToAbr(TABR tabr)
{
  ofstream fichier("tabr_to_abr.txt", ios::out | ios::trunc);

  if(fichier)
    {
      ArbreBinaire *tmp = NULL;
      //on parcour les case de gauche a droite
      for(int i=tabr.nombreCase-1 ; i>0 ; i--)
	 { 
	//   //on recupere l'adresse de la racine
	//   //on la colle au sad du max de l'arbre de la case d'avant

	//   //on se place au maximum de l'arbre d'avant
	   tmp = tabr.tableau.at(i-1).abr;
	   while(tmp->sad != NULL)
	    {
	       tmp = tmp->sad;    
	    }
	   // tmp contient le noeud max
	   tmp->sad = tabr.tableau.at(i).abr;

	  // //tmp est le max de la case i--
	   tmp->sad=tabr.tableau.at(i).abr;
	}

      cout<<afficherABR(tabr.tableau[0].abr)<<endl;
        fichier << afficherABR(tabr.tableau[0].abr);
      fichier.close();
    }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
}
