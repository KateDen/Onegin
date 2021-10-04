#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <TXLib.h>
#include <assert.h>
#include <errno.h>

#include "Onegin_errors.cpp"


//-----------------------------------------------------------------------------


int Text_Ctor(FILE *fileread)
{
    text->filesize = FileBufferize (fileread);

    text->lines = (struct Index*) calloc (text.num_lines, sizeof(Line));

    char* begin_str = text->lines[i].str;
    InitStrings (&text);
}

int Text_Dtor(fileread)
{
    free(text->lines);
    free(text->buffer);
    text->lines = nullptr;
    text->buffer = nullptr;
    return 0;
}


//-----------------------------------------------------------------------------


int FileBufferize (struct Text *text, FILE *fileread)
{
    int size_of_element = sizeof (char);


    if (fileread == NULL)
    {
        return FOPEN_ERR;
    }

    if ((fseek (fileread, 0, SEEK_END)) != 0)
    {
        return FSEEK_ERR;
    }

    text -> filesize = ftell (fileread);
    if ((fseek (fileread, 0, SEEK_SET)) != 0)
    {
        return FSEEK_ERR;
    }

    return 0;
}


//-----------------------------------------------------------------------------


int Bufferizer (struct Text *text)
{
    text -> buffer = (char *) calloc ((text -> filesize + 1), size_of_element);

    int readsymb = fread (text -> buffer, size_of_element, (text -> filesize + 1), fileread);


    if (readsymb != (text -> filesize))
    {
        return FREAD_ERR;
    }

    text -> buffer[text -> filesize] = '\0';


    if ((fclose (fileread)) != 0)
    {
        return FCLOSE_ERR;
    }


    int counter = 0;
    char symbol = 0;
    int i = 0, k = 0;

    if (!i = strchr (text -> buffer[i], '\n'))
    {
        text ->  buffer[i] = '\0';
        ++counter;
    }

    if (text -> buffer [i] != '\n')
    {
        text -> numlines = (counter + 1);
    }

    else text -> numlines = (counter);

    /*while (*(text -> buffer + symbol) != '\0')        //strchr()
    {
        if (*(text -> buffer + symbol) == '\n')
        {
            *(text -> buffer + symbol) = '\0';
            counter++;
        }

        ++symbol;
    } */

    // Обработка символа на конце буффера

    //printf ("counter = %d\n", counter);

    return 0;
}


//-----------------------------------------------------------------------------

int InitStrings (struct Text *text)
{

    //printf ("Initstrings started.\n");
    assert (Index != NULL);

    int k = 1;
    int i = 0;

    char *ch = text->buffer;
    assert (ch != NULL);


    Index[0] = ch;
    // strtok

    while (1)
    {
        if (*(ch + i) == '\0')
        {
            if (i < text->filesize)
            {
                ++i;
                Index[k] = (ch + i);
                ++k;
            }
            else
                break;
        }
        ++i;
    }

    for (i = 0; i < text->numlines; i++)
    {
        puts (Index [i]);
    }

    free (text -> buffer);
    return 0;
}


//-----------------------------------------------------------------------------
qsort(buffer, n, sizeof(int), comp);

int comp(const void*, const void*);

my_qsort(struct Text* text, int (*comp) (const void*, const void*))     //оболочка example
{
    q_sort(text->buffer, text->nline, sizeof(Line), comp);
}


q_sort(buffer, n, sizeof(line), comp_lr);


int Sort1 (char **Index, int numlines)
{
    printf ("Sort1 started.\n\n");

    int counter = 1, i = 0, str_comp_res = 0, strlen = 0;

    while (counter != 0)
    {
        counter = 0;

        for (int k = 0; k < numlines - 1; ++k)
        {
            for (i = 0; i < numlines; ++i)
            {
                str_comp_res = strcmp (Index [i], Index [i+1]);

                if (str_comp_res > 0)
                {
                    if (JustSwap (Index, i) == 0)
                    {
                        counter = 1;
                    }

                    else return SWAP_ERR;
                }
            }
        }
    }

    printf ("111111111111111111111111111111111111\n\n");

    for (i = 0; i < numlines; ++i)
        puts (Index [i]);


    return 0;
}


//-----------------------------------------------------------------------------


FILE *FileWriter (int numlines, char **Index, FILE *filewrite)           //////////////////////////////////
{
    assert (filewrite != NULL);


    for (int i = 0; i < numlines; i++)
    {
        fputs (Lines->str[i], filewrite);
    }

    fclose (filewrite);

    return filewrite;
}


//-----------------------------------------------------------------------------


char *JustSwap (char **Index, int i)
{
    char *tmp = 0;

    tmp = Index [i];
    Index [i] = Index [i+1];
    Index [i+1] = tmp;
    return 0;
}

int MemFree ()
{
    return 0;
}
