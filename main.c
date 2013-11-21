#include <stdio.h>
#include <stdlib.h>

// Definition des structures globales

typedef enum boolean // creation du type booleen
{
    false = 0,
    true = 1
} boolean;


typedef struct option // creation de la structure d'option
{
    boolean w;
    boolean y;
    boolean q;
    boolean help;
    boolean ed;
    boolean v;
    boolean s;

} Goptions;

Goptions ListOptions ={0,0,0,0,0,0,0};


// Declaration des fonctions
boolean DiffNoOption(char * ch1, char * ch2);
boolean WOption(char * ch1, char *ch2);
boolean Strcmp(char * ch1,char * ch2);
int ParserOption(char * options);

void Affiche(int *tab1,int *tab2, FILE *F1, FILE *F2,int nbindice, int nbindice2);
void AfficheY(int *tab1,int *tab2, FILE *F1, FILE *F2,int nbindice, int nbindice2);
void AfficheS(int *tab1,int *tab2, FILE *F1, FILE *F2,int nbindice, int nbindice2);
void VOption();
void HelpOption();
void QOption();
void EDOption();

// Fonction principale
int main(int argc, char** argv)
{
    // declaration des variablese
    int *TabStockIndex1,*TabStockIndex2,Nombredelignes,Nombredelignes2,Nombreindice1,Nombreindice2,i;
    FILE* file1 = NULL;
    FILE* file2 = NULL;
    int NombreOption,retour;

    // initialisation des variables
    TabStockIndex1=(int *) malloc( sizeof(int)*100);
    TabStockIndex2=(int *) malloc( sizeof(int)*100);
    Nombredelignes=1;
    Nombredelignes2=1;
    Nombreindice1=0;
    Nombreindice2=0;

    // test du nombre d arguments
    if (2 >= argc) //Pas assez de paramètre
    {
        if(argv[1][1]=='v')
        {
            VOption();
            return 0;
        }
        else if( argv[1][1]=='-' && argv[1][2]=='h' && argv[1][3]=='e' && argv[1][4]=='l' && argv[1][5]=='p')
        {
            HelpOption();
            return 0;
        }
        else
        {
            printf("diff: loption << %s >> nest pas reconnue \ndiff: Pour en savoir davantage, utilisez << diff: --help >>.",argv[1]);
            return 0;
        }
    }

    if (3<argc)
    {
        i=1;
        NombreOption=0;
        while(i<argc-2)
        {
            retour=ParserOption(argv[i]);
            i++;
            if(retour==0)
                { printf("diff: loption << %s >> nest pas reconnue \ndiff: Pour en savoir davantage, utilisez << diff: --help >>.",argv[i-1]); return 0; }
            else
                NombreOption+=retour;
        }
    }

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

    // ______________________________PRETRAITEMENT _________________________________________ \\

    char chaine1[1000]="";
    char chaine2[1000]="";

    char * r1,*r2;
    boolean difference,save,save2;
    save=false;
    save2=false;

    r1=fgets(chaine1,1000,file1);
    r2=fgets(chaine2,1000,file2);
    while ( r1 != NULL &&  r2 != NULL)
    {


        difference=false;

        if( chaine1[0]=='\n' )
        {

            fgets(chaine1,1000,file1);
            if (save==false)
            {
                TabStockIndex1[Nombreindice1]=Nombredelignes;
                save=true;
                Nombreindice1++;
            }
            Nombredelignes++;
        }
        if( chaine2[0]=='\0')
        {

            fgets(chaine2,1000,file2);
            if (save2==false)
            {
                TabStockIndex2[Nombreindice2]=Nombredelignes2;
                save2=true;
                Nombreindice2++;
            }
            Nombredelignes2++;
        }
        // ____________________________________________ traitement des lignes _________________________________________\\
        else
        {

            if (3 == argc) // Commande sans option
            {
                difference=DiffNoOption(chaine1,chaine2);
            }
            else // Commande avec une ou plusieurs options
            {
                // option de traitements
                if(ListOptions.w==true)
                    difference=WOption(chaine1,chaine2);

            }
        }

    //______________________________________________ Traitement de la sauvegarde _____________________________________________ \\

    if( difference==true) // detection debut bloc
    {
        if(save==false)
        {
            TabStockIndex1[Nombreindice1]=Nombredelignes;
            save=true;
            Nombredelignes++;
        }
        if(save2==false)
        {
            TabStockIndex2[Nombreindice2]=Nombredelignes2;
            save2=true;
            Nombreindice2++;
        }
    }
    else// detection fin bloc
    {

        if( save==true)
        {
         TabStockIndex1[ Nombreindice1]=Nombredelignes-1;
         save=false;
         Nombreindice1++;
        }
        if(save2==true)
        {
            TabStockIndex2[ Nombreindice2]=Nombredelignes2-1;
            save2=false;
            Nombreindice2++;
        }
        difference=false;


    }

    Nombredelignes++;
    Nombredelignes2++;
    r1=fgets(chaine1,1000,file1);
    r2=fgets(chaine2,1000,file2);
}

            // si les derniere lignes sont toute diferentes

            if(difference==true)
            {
                TabStockIndex1[ Nombreindice1]=Nombredelignes;
                TabStockIndex2[ Nombreindice2]=Nombredelignes2;

                Nombreindice1++;
                Nombreindice2++;
            }

            // fichier 1 fini avant fichier 2
            if (r1== NULL && r2 != NULL)
            {
                TabStockIndex2[Nombreindice2]=Nombredelignes2-1;
                Nombreindice2++;
            do
            {
                Nombredelignes2++;

              r2=fgets(chaine2,1000,file2);
            }while (r2!= NULL);
             TabStockIndex2[Nombreindice2]=Nombredelignes2;
             Nombreindice2++;

            }

            // fichier 2 fini avant fichier 1
            else
            {
                TabStockIndex1[Nombreindice1]=Nombredelignes;
                Nombreindice1++;

                do
                {
                    Nombredelignes++;
                    r1=fgets(chaine1,1000,file1);
                }while ( r1!= NULL);

                TabStockIndex1[Nombreindice1]=Nombredelignes-1;
                Nombreindice1++;
            }
    fseek(file1,0,SEEK_SET);
    fseek(file2,0,SEEK_SET);


// Affichage
    if(ListOptions.v==true)
        VOption();
    else
    {
        if(ListOptions.q==true)
           QOption();
        else
        {
            if(ListOptions.y==true && ListOptions.ed==true)
               { printf("diff: options de style de sortie conflictuelles \ndiff: Pour en savoir davantage, utilisez << diff --help >>. "); return 3; }
            else
            {
                if(ListOptions.y==true )
                    AfficheY(TabStockIndex1,TabStockIndex2,file1,file2,Nombreindice1,Nombreindice2);
                else
                {
                    if(ListOptions.s == true)
                    {
                        AfficheS(TabStockIndex1,TabStockIndex2,file1,file2,Nombreindice1,Nombreindice2);
                    }
                    else
                    {
                        if(ListOptions.ed==true)
                            EDOption();
                        else
                        {
                            Affiche(TabStockIndex1,TabStockIndex2,file1,file2,Nombreindice1,Nombreindice2);
                        }
                    }

                }
            }
        }
    }
        fclose(file1);
        fclose(file2);

    return 0;
}

boolean Strcmp(char * ch1,char * ch2)
{
    int i=0,cpt=0,cpt2=0;
    while(ch1[cpt]!='\0')
    {
        cpt++;

    }

    while(ch2[cpt2]!='\0')
    {
        cpt2++;
    }
    if(cpt<=cpt2)
    {
        while(i<cpt) // on compare les caracteres
        {

            if(ch1[i]!= ch2[i])
            {
                return true;
                break;
            }
        i++;
        }
     }
    else
    {
        while(i<cpt2) // on compare les caracteres
        {

            if(ch1[i]!= ch2[i])
            {
                return true;
                break;
            }
        i++;
        }
    }
    return false;
}

int ParserOption(char * options)
{
    int cpt;
    cpt=0;

    while(options[cpt]!='\0')
    {
        if(cpt==0 && options[cpt]!='-')
           return 0;
        if(cpt>0 && options[1]!='-') // option simple a une lettre
        {
            if(options[cpt]=='e') ListOptions.ed=true;
            else if(options[cpt]=='v') ListOptions.v=true;
            else if(options[cpt]=='q') ListOptions.q=true;
            else if(options[cpt]=='w') ListOptions.w=true;
            else if(options[cpt]=='y') ListOptions.y=true;
            else if(options[cpt]=='s') ListOptions.s=true;
            else
                return 0;

        }
        else // option nom complet
        {
                return 0;
        }

        cpt++;
    }

    return cpt-1;



}

// Definition des fonctions
boolean DiffNoOption(char * ch1, char * ch2)
{

            int i=0,cpt=0,cpt2=0;
            while(ch1[cpt]!='\0')
            {
                cpt++;

            }

            while(ch2[cpt2]!='\0')
            {
                cpt2++;
            }
            if(cpt<=cpt2)
            {
                while(i<cpt) // on compare les caracteres car les chaines on la même longueur
                {

                    if(ch1[i]!= ch2[i])
                    {
                        return true;
                        break;
                    }
                i++;
                }
             }
            else
            {
                while(i<cpt2) // on compare les caracteres car les chaines on la même longueur
                {

                    if(ch1[i]!= ch2[i])
                    {
                        return true;
                        break;
                    }
                i++;
                }
            }
            return false;
}

// option W
boolean WOption(char * ch1, char *ch2)
{
    int i=0,j=0,cpt=0,cpt2=0;
    while(ch1[cpt]!='\0')
    {
        cpt++;

    }

    while(ch2[cpt2]!='\0')
    {
        cpt2++;
    }
    if(cpt<=cpt2)
    {
        while(i<cpt) // on compare les caracteres car les chaines on la même longueur
        {

            if(ch1[i]==' ')
                i++;
            else if( ch2[j]==' ')
                j++;
            else
            {
                if(ch1[i]!= ch2[j])
                {
                return true;
                break;
                }

                i++;
                j++;
             }
        }
     }
    else
    {
        while(i<cpt2) // on compare les caracteres car les chaines on la même longueur
        {

            if(ch1[i]==' ')
                i++;
            else if( ch2[j]==' ')
                j++;
            else
            {
                if(ch1[i]!= ch2[j])
                {
                return true;
                break;
                }

                i++;
                j++;
             }

        }
    }
    return false;
}

// Fonction version
void VOption()
{
    printf(" Fonction Diff realiser par Emerich IMBART, Lucas .... , Laurent  Mazza Dans le cadre du projet de langage C pour L ESGI \n ");

}

// Fonction Help
void HelpOption()
{
printf("Usage: diff [OPTION]... FICHIERS\n");
printf("Comparer les fichiers ligne par ligne.\n");
printf("Les parametres requis pour les options longues sont egalement requis pour les options courtes.\n");
printf("--normal Produire un « diff » en format normal (par defaut)\n");
printf("-q, --brief Indiquer seulement si les fichiers different\n");
printf("-s, --report-identical-files Indiquer si les deux fichiers sont identiques\n");
printf("-c, -C N, --context[=N] Afficher N (3 par defaut) lignes du contexte copie\n");
printf("-u, -U N, --unified[=N] Afficher N (3 par defaut) lignes dans le context unifie\n");
printf("-e, --ed Generer un script pour « ed »\n");
printf("-n, --rcs Generer un fichier « diff » au format RCS\n");
printf("-y, --side-by-side Affichage sur deux colonnes\n");
printf("-w, --width=N Limiter la sortie a au plus N colonnes imprimees (130 par defaut)\n");
printf("--left-column Afficher les lignes identiques uniquement dans la colonne de gauche\n");
printf("--suppress-common-lines Ne pas afficher les lignes identiques\n");
printf("-p, --show-c-function Afficher dans quelle fonction C le changement se trouve\n");
printf("-F, --show-function-line=RE Montrer la ligne la plus recente correspondant a RE\n");
printf("--label eTIQUETTE Utiliser eTIQUETTE au lieu du nom de fichier\n");
printf("(peut etre repete)\n");
printf("-t, --expand-tabs etaler les tabulateurs en espaces dans la sortie\n");
printf("-T, --initial-tab Aligner les tabulateurs en prefixant un tabulateur\n");
printf("--tabsize=N Les balises de tabulation sont a chaque N (8 par defaut) colonnes\n");
printf("SUPPORT DE COURS EXERCICES ReSULTATS PROJET\n");
printf("--suppress-blank-empty Supprimer les espaces et les tabulations avant les lignes vides\n");
printf("-l, --paginate Relayer la sortie a « pr » afin de la paginer\n");
printf("-r, --recursive Comparer recursivement les sous-repertoires trouves\n");
printf("-N, --new-file Traiter les fichiers absents comme des fichiers vides\n");
printf("--unidirectional-new-file Traiter les premiers fichiers absents comme vides\n");
printf("--ignore-file-name-case Ignorer la casse lors de la comparaison des noms de fichiers\n");
printf("--no-ignore-file-name-case Tenir compte de la casse lors de la comparaison des noms de fichiers\n");
printf("-x, --exclude=PAT Exclure les fichiers dont les noms concordent avec le PATron\n");
printf("-X, --exclude-from=FICHIER Exclure les fichiers dont les noms\n");
printf("concordent avec ceux contenus dans le FICHIER\n");
printf("-S, --starting-file=FICHIER Debuter la comparaison des repertoires par le FICHIER\n");
printf("--from-file=FICHIER1 Comparer le FICHIER1 a toutes les operandes.\n");
printf("FICHIER1 peut etre un repertoire\n");
printf("--to-file=FICHIER2 Comparer toutes les operandes a FICHIER2.\n");
printf("FICHIER2 peut etre un repertoire\n");
printf("-i, --ignore-case Ignorer les differences de casses dans le contenu des fichiers\n");
printf("-E, --ignore-tab-expansion Ignorer les changements lies a l expansion des tabulations\n");
printf("-Z, --ignore-trailing-space ignore white space at line end\n");
printf("-b, --ignore-space-change Ignorer les changements dans le nombre d espaces\n");
printf("-w, --ignore-all-space Ignorer tout blanc d espacement\n");
printf("-B, --ignore-blank-lines Ignorer les changements dont toutes les lignes sont blanches\n");
printf("-I, --ignore-matching-lines=RE Ignorer les differences dont toutes les\n");
printf("lignes concordent avec l expression reguliere RE\n");
printf("-a, --text Traiter tous les fichiers comme des textes\n");
printf("--strip-trailing-cr eliminer les retours de chariot de l entree\n");
printf("-D, --ifdef=NOM Afficher les fichiers fusionnes en marquant les differences par des « #ifdef NOM »\n");
printf("--GTYPE-group-format=GFMT Formater les groupes d entree GTYPE avec GFMT\n");
printf("--line-format=LFMT Formater toutes les lignes d entree avec LFMT\n");
printf("--LTYPE-line-format=LFMT Formater les lignes d entree LTYPE avec LFMT\n");
printf("Ces options de formatage fournissent un contrôle fin sur la sortie\n");
printf("de diff et generalise -D/--ifdef.\n");
printf("LTYPE peut etre soit « old », « new », ou « unchanged ». GTYPE prend une des valeurs de LTYPE ou « changed ».\n");
printf("GFMT (uniquement) peut contenir :\n");
printf("%< pour marquer les lignes du FICHIER1\n");
printf("%> pour marquer les lignes du FICHIER2\n");
printf("%= pour marquer les lignes identiques entre FICHIER1 et FICHIER2\n");
printf("%[-][LARGEUR][.[PREC]]{doxX}LETTRE la specification de LETTRE\n");
printf("est identique a la notation de printf()\n");
printf("dont les codes possibles de LETTRE sont\n");
printf("en majuscule pour le nouveau groupe,\n");
printf("en minuscules pour l ancien groupe:\n");
printf("F numero de la premiere ligne\n");
printf("L numero de la derniere ligne\n");
printf("N nombre de lignes = L-F+1\n");
printf("E F-1\n");
printf("M L+1 %(A=B?T:E) si A egal B alors T sinon E\n");
printf("LFMT (uniquement) peut contenir :\n");
printf("%L pour le contenu de la ligne\n");
printf("%l pour le contenu de la ligne sans fin de ligne\n");
printf("%[-][LARGEUR][.[PREC]]{doxX}n la specification du numero de ligne\n");
printf("d entree selon le format de printf\n");
printf("GFMT et LFMT peuvent contenir :\n");
printf("%% %\n");
printf("%c«C» le caractere «C» lui-meme\n");
printf(" %c \\OOO» le caractere dont le code octal est OOO C le caractere C (les autres caracteres se representent eux-memes)\n");
printf("-d, --minimal Rechercher assidûment le plus petit ensemble de differences\n");
printf("--horizon-lines=N Retenir N lignes ayant des prefixes et suffixes identiques\n");
printf("--speed-large-files Suppose de grands fichiers et de nombreux petits changements eparpilles\n");
printf("--help Afficher cette aide et terminer\n");
printf("-v, --version Afficher le nom et la version du logiciel et terminer \n");
}

// Options Q
void QOption()
{
    printf("Les fichiers sont differents");
}

void AfficheS(int *tab1,int *tab2, FILE *F1, FILE *F2,int nbindice, int nbindice2)
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
    else
    {
        printf("Les fichiers sont identiques");
    }
}













































//  Affichage
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


// AFFICHAGE OPTION Y
void AfficheY(int *tab1,int *tab2, FILE *F1, FILE *F2,int nbindice, int nbindice2)
{
    int i=0,j=0,k=0,LigneEnCours=1;
    char chaine1[1000]="";
    char chaine2[1000]="";
    char * R1, *R2;
    if( nbindice !=0 && nbindice2!=0)
    {
            R1=fgets(chaine1,1000,F1);
            R2=fgets(chaine2,1000,F2);
            while (R1!=NULL && R2 != NULL)
            {
                if(i<nbindice2 && tab2[i]<=LigneEnCours)
                {
                    printf("%-62s | %-62s \n"," ",chaine2);
                    i++;
                }
                else
                {
                   if(chaine2[0]=='\n')
                        printf("%-62s <"," ");
                    else
                        printf("%-62s   %-62s \n"," ",chaine2);
                }
                if(chaine1[0]=='\n')
                {    printf("%-62s \n",chaine1);
                     R1=fgets(chaine1,1000,F1);
                }
             printf("%-62s \n",chaine1);

             LigneEnCours++;
             R1=fgets(chaine1,1000,F1);
             R2=fgets(chaine2,1000,F2);
            }
            if (R1==NULL && R2 !=NULL)
            {
                do
               {    printf("%-62s > %-62s \n"," ",chaine2);
                    R2=fgets(chaine2,1000,F2);
                }while ( R2 != NULL);
            }
            else
            {

                do
               {
                     printf("%-62s ",chaine1);
                     printf("< \n");
                     R1=fgets(chaine1,1000,F1);
               }while ( R1 != NULL);
            }
    }
}



// Option ED
void EDOption(int *tab1,int *tab2, FILE *F1, FILE *F2,int nbindice, int nbindice2)
{
    int i,j,k;
    char chaine1[1000]="";
    char chaine2[1000]="";
    if( nbindice !=0 && nbindice2!=0)
    {

        if(nbindice>nbindice2)
        {

            printf("%d,%da\n",tab1[nbindice-2],tab1[nbindice-1]);
            for(i=tab1[nbindice-2];i<=tab1[nbindice-1];i++)
                printf("\n");
            printf(".\n");
        }
        else
        {
            printf("%d,%da\n",tab2[nbindice2-2],tab2[nbindice2-1]);
            fseek(F2,0,nbindice2-2);
            for(i=tab2[nbindice2-2];i<=tab2[nbindice2-1];i++)
            {
                fgets(chaine2,1000,F2);
                printf("%s \n",chaine2);
            }
            printf(".\n");
            k=1;
        }
        j=1;
        if(k==1) k=nbindice2-2;
        else k=nbindice2;
        for(;j<k;j+=2)
        {
            fseek(F2,0,nbindice2-j-1);
            printf("%d,%dc\n",tab2[nbindice2-j-1],tab2[nbindice2-j]);
            for(i=tab2[nbindice2-j-1];i<=tab2[nbindice2-j];i++)
            {
                fgets(chaine2,1000,F2);
                printf("%s \n",chaine2);
            }
            printf("\n.");
        }
    }
}
