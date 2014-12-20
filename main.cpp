#include "TABR.cpp"


int main()
{
       TABR tabr;

       initialiser(tabr);
       parserFichier(tabr, "input.txt");
       afficherT(tabr);

    return 0;
}
