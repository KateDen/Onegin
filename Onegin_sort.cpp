#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <TXLib.h>
#include <sys/types.h>
#include <sys/stat.h>

//void qsort (void *getlines, size_t n, size_t MAXLINES, size_t MAXWORD, *comp)

char* FileRead ();
int Comparator1 ();

int main ()

{
    /*setlocale (LC_ALL, "Russian");
    qsort (void *getlines, MAXLINES, size_t MAXWORDS, strcmp (*line1, *line2)); */

   // FileRead ();
    Comparator1 ();

    return 0;
}

char* FileRead ()
{
    FILE *fileread = fopen ("Exampletext.txt", "rb");

    fseek (fileread, 0, SEEK_END);
    long cur_pos = ftell (fileread);

   // enum txtconst {
    int MAXLETTERS = cur_pos;

    char str [MAXLETTERS];

    char *Index [10000000];

    int i = 0;
    while (i != (MAXLETTERS + 1))
    {
        fgets (str, MAXLETTERS + 1, fileread);

        Index [i] = strdup (str);
        i++;
    }

    fclose (fileread);


    return *Index;
}

int Comparator1 ()
{
    int Index [5] = {3, 8, 1, 2, 9};
    int length = (sizeof (*Index) + 1);
    printf ("%d\n", length);

    //int counter = 1, maxrow = 0, i = 0;
    int tmp = 0;

    for (int k = 0; k <= length - 1; k++)
    {
        //i = k;

        /*while (counter != 0)
        {
            counter = 0, maxrow = 0;*/

            for (int i = 0; i < (length - i - 1); i++)
            {
                if (Index [i] > Index [i+1])
                {
                    tmp = Index [i];
                    Index [i] = Index [i+1];
                    Index [i+1] = tmp;
               // printf ("%d\n", Index [i]);

                    //counter = 1;
                    //maxrow++;
                }
            }
        //}
    }

    for (int i = 0; i <= length; i++)
    {
        printf ("%d", Index [i]);
    }

    return 0;
}



/*bool comp ()
{
    char firsts = getchar ();
    int n = 5;

    for (int i = 0; i <= n, i++);
    {
        if isalnum (firsts);
        break;
    }

    return   ;




} */

/*         int *a, *b, *c, d;
         int b;
         a = &b;
         *a == *(&b) */


