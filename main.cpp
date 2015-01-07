#include "TABR.cpp"

int main()
{
       TABR tabr;

       initialiser(tabr);
       parserFichier(tabr, "input.txt");
       cout << afficherT(tabr);
       bool res = verifierTABR(tabr);
       if(res)
       		cout << "Vrai" << endl;
       	else
       		cout << "Faux" << endl;

    return 0;
}
