#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
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


// size_t - done
struct Text
{
    char *buffer = nullptr;
    size_t file_size;

    size_t num_lines;
    struct Line *lines = nullptr;
};

struct Line
{
    char  *str;
    size_t length;
};

//==================================================================================

// см что принимают функции!
// см сто возвращают
// названия следить

int text_Ctor (FILE *fileread, struct Text *text);
int text_Dtor(struct Text *text);

ssize_t file_sizer (struct Text *text, FILE *fileread);
int create_buffer (struct Text *text, FILE *fileread);
size_t str_counter (struct Text *text);
int init_strings (struct Text *text);

int Sort1 (struct Text *text, int numlines);
int just_swap (struct Text *text, int i);

int FileWriter (struct Text *text, FILE *filewrite);

int error_prints (void);

