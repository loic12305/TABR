#include "TABR.hpp"


void initialiser(TABR &tabr)
{
  tabr.nombreCase= 0;
}


/* On est obligé de mettre un "pointeur de pointeur" car on veut agir sur le pointeur du TABR par référence */
void ajouterABR(ArbreBinaire **abr, int valeur)
{
  bool stop = false;
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
        if(valeur == tmpAbr->valeur)
	  {
	    //lorsqu'il y'a doublon, on n'ajoute pas la valeur
	    cout << "Doublon : " << valeur << ", la valeur n'est pas ajouté" << endl;
	    stop = true;
	  }
	else
	  {
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
      }
    while(tmpAbr and !stop);
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

  //verification que le TABR correspond au suffixe
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

bool insertionEntier(TABR &tabr)
{
  int entree;
  bool test = false;
  bool resultat = false;
  int i = 0;

  cout << "*********Insertion d'un entier*********" << endl;
  //test si la valeur est un entier
  while (!test)
    {
      cout << "Entrez l'entier a inserer" << endl;
      cin >> entree;
      if(cin.fail())
	{
	  cout << "mauvaise entree, la valeur attendue est un entier" << endl;
	  cin.clear();
	  cin.ignore( numeric_limits<streamsize>::max(), '\n' );
	}
      else
	{
	  test = true;
	}
    }

  while(i < tabr.nombreCase && resultat == false)
    {
      cout << tabr.tableau[i].intervalle.debut << " ";
      cout << tabr.tableau[i].intervalle.fin << endl;
      //On cherche la bonne intervalle
      if((tabr.tableau[i].intervalle.debut <= entree) && (tabr.tableau[i].intervalle.fin >= entree))
	{
	  ajouterABR(&tabr.tableau[i].abr, entree);
	  resultat = true;
	}
      i++;
    }

  return(resultat);
}

void suppriMax(ArbreBinaire **abr, int valeur)
{

  ArbreBinaire *tmpAbr = *abr;
  ArbreBinaire *tmpTest = tmpAbr->sad;
  cout << "SuppriMax" << endl;

  if((tmpAbr->sad) == NULL)
    {
      cout << "ici" << endl;
      valeur = tmpAbr->valeur;
      tmpAbr = tmpAbr->sag;
    }
  else
    {
      suppriMax(&tmpAbr->sad, valeur);
    }

  *abr = tmpAbr;
}


void supprimerABR(ArbreBinaire **abr, int valeur)
{
  cout << "Supprimer ABR" << endl;
  ArbreBinaire *tmpAbr = *abr;
  
  if(tmpAbr)
    {
      if(valeur < tmpAbr->valeur)
	{
	  supprimerABR(&tmpAbr->sag, valeur);
	}
      else
	{
	  if(valeur > tmpAbr->valeur)
	    {
	      supprimerABR(&tmpAbr->sad, valeur);
	    }
	  else
	    {
	      if(!tmpAbr->sag)
		{
		  tmpAbr = tmpAbr->sad;
		}
	      else
		{
		  if(!tmpAbr->sad)
		    {
		      tmpAbr = tmpAbr->sag;
		    }
		  else
		    {
		      suppriMax(&tmpAbr->sag, valeur);
		      tmpAbr->valeur = valeur;
		    }
		}
	    }
	}
      *abr = tmpAbr;
    }
}

void suppressionEntier(TABR &tabr)
{
  int entree;
  bool test = false;
  bool resultat = false;
  int i = 0;

  cout << "*********Suppression d'un entier*********" << endl;
  //test si la valeur est un entier
  while (!test)
    {
      cout << "Entrez l'entier a supprimer" << endl;
      cin >> entree;
      if(cin.fail())
	{
	  cout << "mauvaise entree, la valeur attendue est un entier" << endl;
	  cin.clear();
	  cin.ignore( numeric_limits<streamsize>::max(), '\n' );
	}
      else
	{
	  test = true;
	}
    }

  while(i < tabr.nombreCase && resultat == false)
    {
      cout << tabr.tableau[i].intervalle.debut << " ";
      cout << tabr.tableau[i].intervalle.fin << endl;
      //On cherche la bonne intervalle
      if((tabr.tableau[i].intervalle.debut <= entree) && (tabr.tableau[i].intervalle.fin >= entree))
	{
	  cout << "passe intervalle" << endl;
	  supprimerABR(&(tabr.tableau[i].abr), entree);
	  cout << "Valeur fin boucle : " << tabr.tableau[i].abr->valeur << endl;
	  cout << afficherABR(tabr.tableau[i].abr) << endl;
	}
      i++;
    }
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
TABR generer_aleatoire(int n, int m) //n nombre de case // m le max de tout les intervalles
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

      
    }

  int i = 0;
  
  return tabr;
  
}


bool estPresent(vector<int> tab,int n)
{
      for(int y=0;y<tab.size();y++)
	if(n == tab.at(y))
	  return true;
      return false;
}


///////////////////////////////
// Fusion la case i avec i+1 //
///////////////////////////////
void fusionTABR(TABR tabr,int indice)
{

  ArbreBinaire *tmp = NULL;
  
  if(indice >= tabr.nombreCase)
    cerr<<"Indice invalide"<<endl;
  else
    {
      //fusion de l'intervalle dans indice
      tabr.tableau[indice].intervalle.fin = tabr.tableau[indice+1].intervalle.fin;
      //   //on se place au maximum de l'arbre
      tmp = tabr.tableau.at(indice).abr;
      while(tmp->sad != NULL)
	tmp = tmp->sad;    

      // tmp contient le noeud max
      //on ajoute a sad de max l'arbre i+1
      tmp->sad = tabr.tableau.at(indice+1).abr;
      tabr.tableau.erase(tabr.tableau.begin() + 3);
      tabr.nombreCase=tabr.nombreCase-1;
      cout<<afficherABR(tabr.tableau[indice].abr)<<endl;
     
    }
}


////////////////////////////////////////////
// Fusion tout les arbres avec le premier //
////////////////////////////////////////////
void tabrToAbr(TABR tabr)
{
  ofstream fichier("tabr_to_abr.txt", ios::out | ios::trunc);
  if(fichier)
    {
      //on utilise la fonction fusion
      for(int i=tabr.nombreCase-1 ; i>0 ; i--)
	fusionTABR(tabr,i-1);

      tabr.nombreCase=1;
      cout << afficherABR(tabr.tableau[0].abr)<<endl;;
      fichier << afficherABR(tabr.tableau[0].abr);
      fichier.close();
    }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
}
