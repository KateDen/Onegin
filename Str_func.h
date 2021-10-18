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
    PTR_ERR      = 2,
    FREAD_ERR    = 3,
    FSEEK_ERR    = 4,
    FCLOSE_ERR   = 5,
    SWAP_ERR     = 6,
    FTELL_ERR    = 7,
    CALLOC_ERR   = 8
};


struct Text
{
    char *buffer = nullptr;
    size_t file_size;

    size_t num_lines;
    struct Line *lines = nullptr;
};

struct Line
{
    char *str = nullptr;
    size_t length;
};

//==================================================================================


int text_Ctor (FILE *fileread, struct Text *text);
void text_Dtor(struct Text *text);

ssize_t file_sizer (FILE *fileread);
char* create_buffer (struct Text *text, FILE *fileread);
size_t str_counter (struct Text *text);
void init_strings (struct Text *text);

int comparator_1 (const void *el_1, const void *el_2); 
int comparator_2 (const void *el_1, const void *el_2);                               
void my_qsort (void *ptr, size_t num_el, size_t size_el, int (*comparator)(const void*, const void*));
void swapper (void *el_1, void *el_2, size_t size_el);                                               

int Sort1 (struct Text *text, int numlines);
int just_swap (struct Text *text, int i);

void file_output (struct Text *text, FILE *filewrite);
void file_original_output (struct Text *text, FILE *filewrite);

int error_prints (int error);
