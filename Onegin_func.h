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

    FILE *fileread = fopen ("Hamlet_example.txt", "rb");

    if (fileread == NULL)
    {
        return FOPEN_ERR;
    }

    /*if (feof (fileread) == 0)
    {
        return EOF_READ_ERR;
    }  */


    if ((fseek (fileread, 0, SEEK_END)) != 0)
    {
        return FSEEK_ERR;
    }

    txtStructPtr -> MAXLETTERS = ftell(fileread);
    fseek (fileread, 0, SEEK_SET);                                                /// специальная функция для освобождения памяти!


    txtStructPtr -> buffer = (char *) calloc ((txtStructPtr -> MAXLETTERS + 1), size_of_element);

    *(txtStructPtr -> buffer + txtStructPtr -> MAXLETTERS) = '\0';

    int readsymb = fread (txtStructPtr -> buffer, size_of_element, (txtStructPtr -> MAXLETTERS + 1), fileread);

    if (readsymb != (txtStructPtr -> MAXLETTERS))
    {
        return FREAD_ERR;
    }                                                             /// сделать разрушающий диструктор для текст


    //fread (txtStructPtr-> buffer, size_of_element, ((txtStructPtr -> MAXLETTERS) + 1), fileread);

    int counter = 0, i = 0;
    char symbol = 0;

    //char *Index [100000];

    while (*(txtStructPtr -> buffer + symbol) != '\0')        //strchr  strtok
    {
        if (*(txtStructPtr -> buffer + symbol) == '\n')
        {
            *(txtStructPtr -> buffer + symbol) = '\0';
            counter++;
            symbol++;
        }
        else symbol++;
    }

    printf ("counter = %d\n", counter);


    txtStructPtr -> MAXLINES = (counter + 1);

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


//-----------------------------------------------------------------------------


int InitStrings (char **Index, char *buffer, int MAXLINES)
{
    assert (Index);

    printf ("Initstrings started.\n");

    int i = 0;


    while (i <= MAXLINES)
    {
        gets (buffer);
        Index [i] = strchr (buffer + i, '\0') + 1;
        i++;
    }

    int num_lines = i;

    for (i = 0; i < num_lines; i++)
    {
        puts (Index [i]);

        if (puts (Index [i]) == EOF)
                printf ("puts error!\n");
    }

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
