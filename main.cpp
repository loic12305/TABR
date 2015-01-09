#include "TABR.cpp"

int main()
{

  bool quit=false,saisieOK=false;
  int saisie,n,m;
  TABR tabr;  
  while(!quit)
    {
      saisieOK = false;
      while (!saisieOK)
	{
	  cout<<"======================================="<<endl;
	  cout<<"=========  GESTION TABR  =============="<<endl;
	  cout<<"======================================="<<endl;
	  cout<<endl;
	  cout<<"Faites un choix : "<<endl;
	  cout<<"1- Créer un TABR à partir du fichier 'input.txt'"<<endl;
	  cout<<"2- Afficher le TABR'"<<endl;
	  cout<<"3- Générer un TABR aléatoirement (remplace TABR existant)"<<endl;
	  cout<<endl;
	  cout<<"4- Inserer un entier dans le TABR"<<endl;
	  cout<<"5- Sunpprimer un entier dans le TABR"<<endl;
	  cout<<endl;
	  cout<<"6- Fusionner 2 case du TABR"<<endl;
	  cout<<"7- Générer un ABR unique à partir du TABR"<<endl;
	  cout<<endl;
	  cout<<endl;
	  cout<<"0- Pour quitter"<<endl;

	  //saisie
	  cin >> saisie;

	  if(cin.fail())
	    {
	      cout << "mauvaise entree, la valeur attendue est un entier" << endl;
	      cin.clear();
	      cin.ignore( numeric_limits<streamsize>::max(), '\n' );
	    }
	  else
	    saisieOK = true;
	}

      //switch
      switch (saisie)
	{
	case 1: {
	  initialiser(tabr);
	  parserFichier(tabr, "input.txt");
	  break;
	}
	case 2:
	  {
	    cout << afficherT(tabr);
	    break;
	  }
	case 3:
	  {
	    // saisie + verif de n case
	    saisieOK=false;
	    while(!saisieOK){
	      cout<<"Saisir le nombre de case du TABR : ";
	      cin>>n;
	      if(saisie < 1)
		cout<<"Saisir un entier positif non nulle";
	      else
		saisieOK=true;
	    }
	    // saisie + verif de m maximum
	    saisieOK=false;
	    while(!saisieOK){
	      cout<<"Saisir la valeur max du TABR : ";
	      cin>>m;
	      saisieOK=false;
	      if(saisie < 1)
		cout<<"Saisir un entier positif > 10";
	      else
		saisieOK=true;
	    }
	    tabr = generer_aleatoire(n,m);
	  }
	}

      saisieOK=false;
      
    }

  // TABR tabr;
  //      bool test;

  //      initialiser(tabr);
  //      parserFichier(tabr, "input.txt");
  //      fusionTABR(tabr,2);
  //      fusionTABR(tabr,0);
  //	      tabrToAbr(tabr);
  // cout << afficherT(tabr);
  //bool res = verifierTABR(tabr);

  // exportTABR(tabr);
  // test = insertionEntier(tabr, 4);
  // if(test)
  // 	 cout << "Insertion Ok" << endl;
  // else
  // 	 cout << "Insertion KO" << endl;
  // cout << afficherT(tabr);

  return 0;
}
