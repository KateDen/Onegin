#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <TXLib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <assert.h>
#include <errno.h>

int FileRead (int, int, char**);
int Comparator1 (char**);

int main ()
{
    /**setlocale (LC_ALL, "Russian");
    qsort (void *getlines, MAXLINES, size_t MAXWORDS, strcmp (*line1, *line2)); **/

    FILE *fileread = fopen ("Exampletext.txt", "rb");

    if ((ferror (fileread)) != 0)
        printf ("File reading error!");


    fseek (fileread, 0, SEEK_END);

    long cur_pos = ftell(fileread);

    fseek (fileread, 0, SEEK_SET);

    int MAXLETTERS = cur_pos;
    int MAXLINES = 0;
    char symbol = 0;


    while ((symbol = fgetc (fileread)) != EOF)
    {
        if (symbol == '\n')
            MAXLINES++;
    }

    char *Index [MAXLINES];

    fclose (fileread);


    FileRead (MAXLETTERS, MAXLINES, Index);
    Comparator1 (Index);

    return 0;
}


//-----------------------------------------------------------------------------


int FileRead (MAXLETTERS, MAXLINES, Index)
{
    char str [MAXLETTERS + 1];
    int i = 0;


    while (fgets (str, MAXLETTERS + 1, fileread) != NULL)
    {
        Index[i] = strdup(str);

        i++;
        strcpy (str, "Exampletext.txt");
    }


    int num_lines = i;



    for (i = 0; i < num_lines; i++)
        puts (Index[i]);


    return 0;
}

//-----------------------------------------------------------------------------


int Comparator1 (Index)
{
    newfile = creat ("Hamlet_sorted.txt", 0);
    if (newfile == -1)
        printf ("File creating error!");

    newfile = open ("Hamlet_sorted.txt", O_RDONLY, 0);
    if (newfile == -1)
        printf ("File opening error!");

    int length = sizeof (Index) / sizeof (char);

    int counter = 1, maxrow = 0, i = 0;
    char tmp = 0;

    while (counter != 0)
    {
        counter = 0, maxrow = 0;

        for (int k = 0; k <= length - 1; k++)
        {
            for (int i = 0; i < (length - k - 1); i++)
            {
                if (Index [i] > Index [i+1])
                {
                    tmp = Index [i];
                    Index [i] = Index [i+1];
                    Index [i+1] = tmp;

                    counter = 1;
                    maxrow++;
                }
            }
        }
    }

    for (int i = 0; i < length; i++)
    {
        printf ("%d", Index [i]);
    }

    return 0;
}


//-----------------------------------------------------------------------------


/**bool comp ()
{
    char firsts = getchar ();
    int n = 5;

    for (int i = 0; i <= n, i++);
    {
        if isalnum (firsts);
        break;
    }

    return   ;




}

        int *a, *b, *c, d;
         int b;
         a = &b;
         *a == *(&b) **/



