#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>                                        
#include <TXLib.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>

enum error_consts {
    FOPEN_ERR    = 1,
    EOF_READ_ERR = 2,
    FREAD_ERR    = 3,
    FSEEK_ERR    = 4,
    FCLOSE_ERR   = 5,
    SWAP_ERR     = 6
};


struct Text
{
    char *buffer;
    int filesize;

    int numlines;
    struct Line* lines;
};

struct Line
{
    char *str;
    int length;
};

#include "Onegin_func.h"
#include "Onegin_errors.h"


int main ()
{
    /**setlocale (LC_ALL, "Russian");
    qsort (void *getlines, numlines, size_t MAXWORDS, strcmp (*line1, *line2)); */

    struct Text text = {};

    FILE *fileread = fopen ("Hamlet_example.txt", "rb");

    if (!fileread)
    {
        return FOPEN_ERR;
    }

    Text_Ctor(fileread);

    Sort1 (Index, text.numlines);

    FILE *filewrite = fopen ("Hamlet_sort.txt", "wb");

    if (!filewrite)
    {
        return FOPEN_ERR;
    }

    FileWriter (text.numlines, Index);

    Text_Dtor(fileread);

    ErrorPrints();

    return 0;
}


//-----------------------------------------------------------------------------


int ErrorPrints (void)
{
    if (!errno) return 0;

    switch (errno)
    {
        case FOPEN_ERR:
            fprintf (stderr, "File opening error!\n");
            break;

        case EOF_READ_ERR:
            fprintf (stderr, "EOF error!\n");
            break;

        case FREAD_ERR:
            fprintf (stderr, "Fread error!\n");
            break;

        case FSEEK_ERR:
            fprintf (stderr, "File seek error!\n");
            break;

        case FCLOSE_ERR:
            fprintf (stderr, "File close error!\n");
            break;

        case SWAP_ERR:
            fprintf (stderr, "Swap error!\n");
            break;

        default:
            // perror();
    }
}

