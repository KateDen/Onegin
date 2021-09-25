#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <TXLib.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>

int FileBufferize (struct text *my_first_structure);
int IndexFiller (int MAXLETTERS, char **Index, char *buffer);
int Sort1 (char **Index, int MAXLINES);
FILE *FileWriter (int MAXLINES, char **Index);

struct text
{
    char *buffer;
    int MAXLINES;
    int MAXLETTERS;
};

int main ()
{
    /**setlocale (LC_ALL, "Russian");
    qsort (void *getlines, MAXLINES, size_t MAXWORDS, strcmp (*line1, *line2)); **/

    struct text my_first_structure = {};


    FileBufferize (&my_first_structure);

    char *Index [my_first_structure.MAXLINES];

    IndexFiller (my_first_structure.MAXLETTERS, Index, my_first_structure.buffer);

    Sort1 (Index, my_first_structure.MAXLINES);

    FileWriter (my_first_structure.MAXLINES, Index);

    //qsort ();


    return 0;
}


//-----------------------------------------------------------------------------

int FileBufferize (struct text *my_first_structure)
{
    int size_of_element = sizeof (char);

    FILE *fileread = fopen ("Exampletext.txt", "rb");

    if ((ferror (fileread)) != 0)
    {
        printf ("File reading error!\n");
        return 0;
    }


    fseek (fileread, 0, SEEK_END);
    my_first_structure -> MAXLETTERS = ftell(fileread);
    fseek (fileread, 0, SEEK_SET);


    my_first_structure -> buffer = (char *) calloc (my_first_structure -> MAXLETTERS + 1, size_of_element);

    if  ((fread (my_first_structure-> buffer, size_of_element, my_first_structure -> MAXLETTERS, fileread))
    != (my_first_structure -> MAXLETTERS + 1))
    {
        printf ("Fread error!\n");
        return 0;
    }


    int counter = 0;
    int symbol = 0;

    while ((symbol = getc (my_first_structure -> buffer)) != '\0')
    {
        if (symbol == '\n')
        {
            symbol = '\0';
            counter++;
        }
    }

    my_first_structure -> MAXLINES = counter + 1;

    if ((fseek (fileread, 0, SEEK_SET)) != 0)
        printf ("File seek error!\n");


    if ((fclose (fileread)) == EOF)
        printf ("File close error!\n");

    return 0;
}


int IndexFiller (int MAXLETTERS, char **Index, FILE *fileread)
{
    assert (Index);


    char str [MAXLETTERS + 1];
    int i = 0;


    while (fgets (str, MAXLETTERS + 1, fileread) != NULL)
    {
        Index [i] = strdup(str);
        i++;
        strcpy (str, "Exampletext.txt");
    }

    /*int num_lines = i;
    //printf ("%c\n", str [45]);
    for (i = 0; i < num_lines; i++)
    {
        puts (Index [i]);

        if (puts (Index [i]) == EOF)
                printf ("puts error!");
    }    */

    return 0;
}

//-----------------------------------------------------------------------------


int Sort1 (char **Index, int MAXLINES)
{
    //int length = sizeof (*Index) / sizeof (int);

    unsigned counter = 1, maxrow = 0, i = 0;
    char *tmp = 0;

    while (counter != 0)
    {
        counter = 0, maxrow = 0;

        for (int k = 0; k <= MAXLINES - 1; ++k)
        {
            for (i = 0; i < (MAXLINES - k - 1); ++i)
            {
                int str_comp_res = strcmp (Index [i], Index [i+1]);

                if (str_comp_res > 0)
                {
                    tmp = Index [i];
                    Index [i] = Index [i+1];
                    Index [i+1] = tmp;

                    counter = 1;
                    ++maxrow;
                }
            }
        }
    }

    //for (i = 0; i < MAXLINES; i++)
        //puts (Index [i]);



    return 0;
}

FILE *FileWriter (int MAXLINES, char **Index)
{
    FILE *filewrite = fopen ("Hamlet_sort.txt", "wb");
    assert (filewrite != NULL);


    for (int i = 0; i < MAXLINES; i++)
    {
        fputs (Index [i], filewrite);
    }

    fclose (filewrite);

    return filewrite;
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
         *a == *(&b)

         char newfile = creat ("Hamlet_sorted.txt", 0);
    //if (newfile == -1)
        //printf ("File creating error!");

    newfile = open ("Hamlet_sorted.txt", O_RDONLY, 0);
    if (newfile == -1)
        printf ("File opening error!");  **/



