#include "TABR.cpp"

int main()
{
       TABR tabr;
       bool test;

       initialiser(tabr);
       parserFichier(tabr, "input.txt");
       //       tabrToAbr(tabr);
       //     cout << afficherT(tabr);
       //bool res = verifierTABR(tabr);

       exportTABR(tabr);
       // test = insertionEntier(tabr, 4);
       // if(test)
       // 	 cout << "Insertion Ok" << endl;
       // else
       // 	 cout << "Insertion KO" << endl;
       // cout << afficherT(tabr);

       suppressionEntier(tabr);
       cout << "Main : " << endl;
       cout << afficherT(tabr);

    return 0;
}
