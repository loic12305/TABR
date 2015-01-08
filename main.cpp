#include "TABR.cpp"

int main()
{
  TABR tabr;
       initialiser(tabr);
       parserFichier(tabr, "input.txt");
       //       tabrToAbr(tabr);
       //     cout << afficherT(tabr);
       //bool res = verifierTABR(tabr);
       //exportTABR(tabr);

    return 0;
}
