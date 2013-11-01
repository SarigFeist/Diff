#include <stdio.h>
#include <stdlib.h>

// Définition des structures globales

typedef enum boolean // création du type booleen
{
    false = 0,
    true = 1
} boolean;


struct option // création de la structure d'option
{
}
;


// Déclaration des fonctions
int **createTable(int nbLin, int nbCol);




// Fonction principale
int main(int argc, char** argv)
{
    int **Tab_Compteur_de_ligne,index;

    Tab_Compteur_de_ligne= createTable(100,100);




        if (2 > argc) //Pas assez de paramètre
        {
            printf("Nombre de parametres insuffisants\n");
        }
         else if (3 == argc) // Commande sans option
        {

        }
        else if ( 4== argc) // une seule option
        {

        }
        else // Commande avec plusieurs options
        {

        }


    return 0;
}




// Définition des fonctions
int **createTable(int nbLin, int nbCol)
{
    int **tableau = (int **)malloc(sizeof(int*)*nbLin);
    int *tableau2 = (int *)malloc(sizeof(int)*nbCol*nbLin);
    for(int i = 0 ; i < nbLin ; i++){
        tableau[i] = &tableau2[i*nbCol];
    }
    return tableau;
}
