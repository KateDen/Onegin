#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <locale.h>
//#include <TXLib.h>
//#include <sys/types.h>
//#include <assert.h>
//#include <errno.h>

enum error_consts {
    FOPEN_ERR    = 1,
    EOF_READ_ERR = 2,
    FREAD_ERR    = 3,
    FSEEK_ERR    = 4,
    FCLOSE_ERR   = 5,
    SWAP_ERR     = 6
};


//typedef         //?
struct Text
{
    char *buffer;
    int file_size;

    int num_lines;
    struct Line* lines;
} text;

//typedef            //?
struct Line
{
    char *str;
    int length;
} lines;

#include "Onegin_func.cpp"
#include "Onegin_errors.cpp"
#include "Str_func.h"


int main ()
{
    Text text = {};
    Line lines = {};

    FILE *fileread = fopen ("Hamlet_example.txt", "rb");

    if (!fileread)
    {
        return FOPEN_ERR;
    }

    Text_Ctor(fileread, &text);

    //Sort1 (text);

    FILE *filewrite = fopen ("Hamlet_sort.txt", "wb");

    if (!filewrite)
    {
        return FOPEN_ERR;
    }

    FileWriter (text);

    Text_Dtor(text);

    ErrorPrints();

    return 0;
}


//-----------------------------------------------------------------------------


void ErrorPrints (void)
{
    if (!errno) return 0;

    switch (errno)
    {
        case FOPEN_ERR:
            fprintf (stderr, "File opening error!\n");     //fprintf ("%s\n", stderr(errno));
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
            perror("Undefined error\n");
    }
}
