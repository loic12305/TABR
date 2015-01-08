#include "TABR.cpp"

int main()
{
  TABR tabr;
       initialiser(tabr);
       parserFichier(tabr, "input.txt");
          fusionTABR(tabr,0);
	  //       tabrToAbr(tabr);
       //     cout << afficherT(tabr);
       //bool res = verifierTABR(tabr);
       //exportTABR(tabr);

    return 0;
}
