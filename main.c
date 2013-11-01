#include <stdio.h>
#include <stdlib.h>

// Definition des structures globales

typedef enum boolean // creation du type booleen
{
    false = 0,
    true = 1
} boolean;


struct option // creation de la structure d'option
{
}
;


// Declaration des fonctions
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
        else // Commande avec une ou plusieurs options
        {

        }


    return 0;
}




// Definition des fonctions
int **createTable(int nbLin, int nbCol)
{
    int **tableau = (int **)malloc(sizeof(int*)*nbLin);
    int *tableau2 = (int *)malloc(sizeof(int)*nbCol*nbLin);
    for(int i = 0 ; i < nbLin ; i++){
        tableau[i] = &tableau2[i*nbCol];
    }
    return tableau;
}
