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


//typedef         //?
struct Text
{
    char *buffer;
    int file_size;

    int num_lines;
    struct Line* lines;
};

//typedef            //?
struct Line
{
    char *str;
    int length;
};



int Text_Ctor (FILE *fileread, struct Text *text);
int Text_Dtor(struct Text *text);

int FileReader (struct Text *text, FILE *fileread);
int Bufferizer (struct Text *text, FILE *fileread);
int InitStrings (struct Text *text);

int Sort1 (struct Text *text, int numlines);

int JustSwap (struct Text *text, int i);

int FileWriter (struct Text *text, FILE *filewrite);

int ErrorPrints (void);

