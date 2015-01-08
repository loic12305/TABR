#include "TABR.cpp"

int main()
{
       TABR tabr;
       bool test;

       initialiser(tabr);
       parserFichier(tabr, "input.txt");
       fusionTABR(tabr,2);
       fusionTABR(tabr,0);
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
