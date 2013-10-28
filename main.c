#include <stdio.h>
#include <stdlib.h>
//TEST NINJA COMMIT
int main(int argc, char** argv)
{
    enum boolean
    {
        false = 0,
        true = 1
    }typedef boolean;
	
	struct option
	{
	}
	;

    {
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
    }

    return 0;
}
