# Projet algorithmique - Tableau d'ABR

Projet réalisé par Loïc ENTRESSANGLE et Boris LEBRUN

## Compile

- g++ :  `g++ -g main.cpp -std=c++0x -o bin/pgm`

## How To Use

- `./bin/pgm`
- Le programme ne possède qu'un seul TABR en memoire. Ainsi à chaque modification ou génération, tout se fait sur le même TABR
- La génération d'un ABR à partir du TABR crée également un fichier `tabr_to_abr.txt`
- Lors de la génération aléatoire, il se peut qu'une erreur se produise : `Floating point exception` : il faut alors augmenter l'entier maximum du TABR

## Support Future Development

- Boris LEBRUN : `boris.lebrun@etu.univ-nantes.fr`
- Loïc ENTRESSANGLE : `loic.entressangle@etu.univ-nantes.fr`
