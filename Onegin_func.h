#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <TXLib.h>
#include <assert.h>
#include <errno.h>

#include "Onegin_errors.h"

int FileBufferize (struct text *txtStructPtr)
{
    int size_of_element = sizeof (char);

    FILE *fileread = fopen ("Exampletext.txt", "r");

    if ((ferror (fileread)) == 0)
    {
        return FOPEN_ERR;
    }

    if (feof (fileread) == 0)
    {
        return EOF_READ_ERR;
    }


    fseek (fileread, 0, SEEK_END);
    txtStructPtr -> MAXLETTERS = ftell(fileread);
    fseek (fileread, 0, SEEK_SET);                                        /// специальна€ функци€ дл€ освобождени€ пам€ти!


    txtStructPtr -> buffer = (char *) calloc (((txtStructPtr -> MAXLETTERS) + 1), size_of_element);

    *((txtStructPtr -> buffer) + (txtStructPtr -> MAXLETTERS) + 1) = '\0';


    if((fread (txtStructPtr -> buffer, size_of_element, ((txtStructPtr -> MAXLETTERS) + 1), fileread))
    == ((txtStructPtr -> MAXLETTERS) + 1))
    {                                                             //mistake is here
        return FREAD_ERR;
    }                                                             /// сделать разрушающий диструктор дл€ текста

/**/else printf ("Fread is OK!\n");


    //fread (txtStructPtr-> buffer, size_of_element, ((txtStructPtr -> MAXLETTERS) + 1), fileread);

    int counter = 0;
    char symbol = 0;


    while (*(txtStructPtr -> buffer + symbol) != '\0')
    {
        if (*(txtStructPtr -> buffer) == '\n')
        {
            *(txtStructPtr -> buffer) = '\0';
            counter++;
            symbol++;
        }
        else symbol++;
    }

    printf ("counter = %d\n", counter);


    txtStructPtr -> MAXLINES = (counter + 1);

    printf ("counter + 1 = %d\n", txtStructPtr -> MAXLINES);

    if ((fseek (fileread, 0, SEEK_SET)) != 0)
    {
        return FSEEK_ERR;
    }


    if ((fclose (fileread)) != 0)
    {
        return FCLOSE_ERR;
    }

    return 0;
}


int IndexFiller (int MAXLETTERS, char **Index, char *buffer)
{
    assert (Index);


    int i = 0;


    while (gets (buffer) != NULL)
    {
        Index [i] = strdup(buffer);
        i++;
        strcpy (buffer, "Exampletext.txt");
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
