#include "TABR.hpp"


void initialiser(TABR &tabr)
{
       tabr.nombreCase= 0;

}


void addNode(node **tree, unsigned int key)
{
    node *tmpNode;
    node *tmpTree = *tree;

    node *elem = new node;
    elem->key = key;
    elem->left = NULL;
    elem->right = NULL;

    if(tmpTree)
    do
    {
        tmpNode = tmpTree;
        if(key > tmpTree->key )
        {
            tmpTree = tmpTree->right;
            if(!tmpTree) tmpNode->right = elem;
        }
        else
        {
            tmpTree = tmpTree->left;
            if(!tmpTree) tmpNode->left = elem;
        }
    }
    while(tmpTree);
    else  *tree = elem;
}


void creerCaseArbre(TABR &tabr, vector<int> tab, int deb, int fin)
{
  Intervalle intervalle;
  intervalle.debut = deb;
  intervalle.fin = fin;
  
  Case c;
  c.intervalle = intervalle;
         
  node *arbre = NULL;
  c.abr = arbre;

  for(int i=(tab.size()-1);i>=0;i--)
    {
      addNode(&c.abr, tab[i]);
      cout <<  tab[i] << " ajoute" << endl;
    }
  tabr.tableau.push_back(c);
  tabr.nombreCase++;
  
}

void parserFichier(TABR &tabr, string emplacement, string fich)
{
    string entree = emplacement + fich;
    int indexFin = 0;
    string intervalle = "";

    ifstream fichier("/media/Documents/loic/MASTER1/S1/ALGO/Projet/Source/input.txt");
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
                //cout << nombre << endl;
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
    cout << tabr.tableau[i].intervalle.debut<<" .. "<< tabr.tableau[i].intervalle.fin <<endl;
    cout << ";" << endl;
    printTree(tabr.tableau[i].abr);
    i++;
  }
}

void printTree(node *tree)
{
    if(!tree) return;

    if(tree->left)  printTree(tree->left);

    printf("Cle = %d\n", tree->key);

    if(tree->right) printTree(tree->right);
}
