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
void DiffNoOption(int *tab1, int *tab2, FILE * F1, FILE *F2, int *nblignes,int *nblignes2,int *nbindice,int *nbindice2);
void Affiche(int *tab1,int *tab2, FILE *F1, FILE *F2,int nbindice, int nbindice2);


// Fonction principale
int main(int argc, char** argv)
{
    // déclaration des variables
    int *TabStockIndex1,*TabStockIndex2,Nombredelignes,Nombredelignes2,Nombreindice1,Nombreindice2;
    FILE* file1 = NULL;
    FILE* file2 = NULL;

    // initialisation des variables
    TabStockIndex1=(int *) malloc( sizeof(int)*100);
    TabStockIndex2=(int *) malloc( sizeof(int)*100);
    Nombredelignes=1;
    Nombredelignes2=1;
    Nombreindice1=0;
    Nombreindice2=0;

    // ouverture des fichiers
    file1 = fopen(argv[argc-2], "r");
    file2 = fopen(argv[argc-1], "r");
    // verification de l'ouverture
    if(file1 == NULL)
    {
        printf("open file 1 fail");
        return -1;
    }
    if(file2 == NULL)
    {
        printf("open file 2 fail");
        return -2;
    }

        // test du nombre d arguments
        if (2 > argc) //Pas assez de paramètre
        {
            printf("Nombre de parametres insuffisants\n");
        }
         else if (3 == argc) // Commande sans option
        {
            DiffNoOption(TabStockIndex1,TabStockIndex2,file1,file2,&Nombredelignes,&Nombredelignes2,&Nombreindice1,&Nombreindice2);
            fclose(file1);
            fclose(file2);
        }
        else // Commande avec une ou plusieurs options
        {

        }

// Affichage
        // ouverture des fichiers
        file1 = fopen(argv[argc-2], "r");
        file2 = fopen(argv[argc-1], "r");
        Affiche(TabStockIndex1,TabStockIndex2,file1,file2,Nombreindice1,Nombreindice2);
        fclose(file1);
        fclose(file2);

    return 0;
}




// Definition des fonctions
void DiffNoOption(int *tab1, int *tab2, FILE * F1, FILE *F2, int *nblignes,int *nblignes2,int *nbindice,int *nbindice2)
{
    char chaine1[1000]="";
    char chaine2[1000]="";
    int i=0,cpt=0,cpt2=0;
    char * r1,*r2;
    boolean difference,save,save2;
    save=false;
    save2=false;

    r1=fgets(chaine1,1000,F1);
    r2=fgets(chaine2,1000,F2);
    while ( r1 != NULL &&  r2 != NULL)
    {
        i=0;
        cpt=0;
        cpt2=0;
        difference=false;

        if( chaine1[0]=='\n' )
        {

            fgets(chaine1,1000,F1);
            if (save==false)
            {
                tab1[(*nbindice)]=(*nblignes);
                save=true;
                (*nbindice)++;
            }
            (*nblignes)++;
        }
        if( chaine2[0]=='\0')
        {

            fgets(chaine2,1000,F2);
            if (save2==false)
            {
                tab2[(*nbindice2)]=(*nblignes);
                save2=true;
                (*nbindice2)++;
            }
            (*nblignes2)++;
        }
        else
        {

            while(chaine1[cpt]!='\0')
            {
                cpt++;

            }

            while(chaine2[cpt2]!='\0')
            {
                cpt2++;
            }
            if(cpt<=cpt2)
            {
                while(i<cpt) // on compare les caracteres car les chaines on la même longueur
                {

                    if(chaine1[i]!= chaine2[i])
                    {
                        difference=true;
                        break;
                    }
                i++;
                }
             }
            else
            {
                while(i<cpt2) // on compare les caracteres car les chaines on la même longueur
                {

                    if(chaine1[i]!= chaine2[i])
                    {
                        difference=true;
                        break;
                    }
                i++;
                }
            }

         }
            if( difference==true) // detection debut bloc
            {
                if(save==false)
                {
                    tab1[(*nbindice)]=(*nblignes);
                    save=true;
                    (*nbindice)++;
                }
                if(save2==false)
                {
                    tab2[(*nbindice2)]=(*nblignes2);
                    save2=true;
                    (*nbindice2)++;
                }

            }
            else// detection fin bloc
            {

                if( save==true)
                {
                 tab1[ (*nbindice)]=(*nblignes)-1;
                 save=false;
                 (*nbindice)++;
                }
                if(save2==true)
                {
                    tab2[ (*nbindice2)]=(*nblignes2)-1;
                    save2=false;
                    (*nbindice2)++;
                }
                difference=false;

            }

            (*nblignes)++;
            (*nblignes2)++;
            r1=fgets(chaine1,1000,F1);
            r2=fgets(chaine2,1000,F2);
    }

    // si les derniere lignes sont toute diferentes

    if(difference==true)
    {
        tab1[ (*nbindice)]=(*nblignes);
        tab2[ (*nbindice)]=(*nblignes2);

        (*nbindice)++;
        (*nbindice2)++;
        printf(" Debug  derniere ligne DIFFFFFF \n \n ");
        getchar();
    }

    // fichier 1 fini avant fichier 2
    if (r1== NULL && r2 != NULL)
    {
        tab2[(*nbindice2)]=(*nblignes2);
        (*nbindice2)++;
        do
        {
         (*nblignes2)++;

          r2=fgets(chaine2,1000,F2);
        }while (r2!= NULL);
         tab2[(*nbindice2)]=(*nblignes2);
         (*nbindice2)++;

    }

    // fichier 2 fini avant fichier 1
    else
    {
        tab1[(*nbindice)]=(*nblignes);
        (*nbindice)++;

        do
        {
            (*nblignes)++;
            r1=fgets(chaine1,1000,F1);
        }while ( r1!= NULL);

        tab1[(*nbindice)]=(*nblignes)-1;
        (*nbindice)++;
     }

}

void Affiche(int *tab1,int *tab2, FILE *F1, FILE *F2,int nbindice, int nbindice2)
{
    int i,j,k;
    char chaine1[1000]="";
    char chaine2[1000]="";
    if( nbindice !=0 && nbindice2!=0)
    {
            for (i=0;i<nbindice;i+=2)
            {
                if(tab1[i]==tab1[i+1])
                {
                    printf("%d",tab1[i]);

                }
                else
                {
                    printf("%d",tab1[i]);
                    printf(",");
                    printf("%d",tab1[i+1]);
                }
                if(i<nbindice2)
                {
                    if(tab2[i]==tab2[i+1])
                    {
                        printf("c");
                        printf("%d",tab2[i]);
                        printf("\n");
                    }
                    else
                    {
                        printf("c");
                        printf("%d",tab2[i]);
                        printf(",");
                        printf("%d",tab2[i+1]);
                        printf("\n");
                    }
                }
                else
                {
                    printf("\n");
                }

                for( j=0;j<tab1[i];j++)
                {
                    fgets(chaine1,1000,F1);

                    j++;
                }
                printf("< %s",chaine1);
                for(k=tab1[i+1];j<=k;j++)
                {
                    fgets(chaine1,1000,F1);
                    printf("< %s",chaine1);
                }
                if(i<nbindice2)
                {
                    printf("---\n");
                    for( j=0;j<tab2[i];j++)
                    {
                        fgets(chaine2,1000,F2);
                        j++;
                    }
                    printf("> %s",chaine2);
                    for(k=tab2[i+1];j<=k;j++)
                    {

                        fgets(chaine2,1000,F2);
                        printf("> %s",chaine2);
                    }
                }

            }
            if(nbindice<nbindice2)
            {
                for( ;i<nbindice2;i+=2)
                {
                    if(tab2[i]==tab2[i+1])
                    {
                        printf("%d",tab2[i]);
                        printf("\n");
                    }
                    else
                    {
                        printf("%d",tab2[i]);
                        printf(",");
                        printf("%d",tab2[i+1]);
                        printf("\n");
                    }
                    for( j=0;j<tab2[i];j++)
                    {
                        fgets(chaine2,1000,F2);
                        j++;
                    }
                    printf("> %s",chaine2);

                    for(k=tab2[i+1];j<k-1;j++)
                    {
                        fgets(chaine2,1000,F2);
                        printf("> %s",chaine2);
                    }

                }
            }


    }

}
