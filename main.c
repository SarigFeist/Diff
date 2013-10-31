#include <stdio.h>
#include <stdlib.h>

    enum boolean
    {
        false = 0,
        true = 1
    }typedef boolean;

boolean diffNoOption(char* lineFile1, char* lineFile2);

int main(int argc, char** argv)
{



    {
        if (2 > argc) //Not enough parameter
        {
            printf("Not enough parameter\n");
        }
         else if (3 == argc) // Command without option
        {
            // Opening of files
            FILE* file1 = NULL;
            FILE* file2 = NULL;
            file1 = fopen(argv[1], "r");
            file2 = fopen(argv[2], "r");
            if(file1 == NULL)
            {
                printf("open file 1 fail");
                return -1;
            }
            if(file2 == NULL)
            {
                printf("open file 2 fail");
                return -1;
            }
            else
            {
                boolean endFile1 = false;
                boolean endFile2 = false;

                //while(endFile1 == false && endFile2 == false)
                {
                    char lineFile1[600]; //value just for test
                    char lineFile2[600]; //value just for test
                    fgets(lineFile1, 600, file1 );
                    fgets(lineFile2, 600, file2 );

                    if(diffNoOption(lineFile1, lineFile2) == 0)
                    {
                        printf("same");
                    }
                }

            }

        }
        else if ( 4== argc) // Single option
        {

        }
        else // Command(Order) with many options
        {

        }
    }

    return 0;
}

// Controls whether two lines are similar
boolean diffNoOption(char* lineFile1, char* lineFile2)
{
    //compared to fix

    return strcmp(lineFile1, lineFile2);
}
