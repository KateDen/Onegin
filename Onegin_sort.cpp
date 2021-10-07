#include "Str_func.h"

int main () {

    struct Text text  = {};
    struct Line lines = {};

    FILE *fileread = fopen ("Hamlet_example.txt", "rb");

    if (!fileread) {
        return FOPEN_ERR;
    }

    text_Ctor(fileread, &text);

    //Sort - вызов

    FILE *filewrite = fopen ("Hamlet_sort.txt", "wb");


    if (!filewrite) {
        return error_prints(FOPEN_ERR);
    }


    FileWriter (&text, filewrite);

    text_Dtor (&text);

    error_prints();

    return 0;
}


//-----------------------------------------------------------------------------


int error_prints (int error) {

    if (!error) return 0;

    switch (error)
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
            perror("Undefined error");
    }

    return error;
}
