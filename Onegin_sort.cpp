

#include "Str_func.h"




int main () {

    struct Text text = {};
    struct Line lines = {};

    FILE *fileread = fopen ("Hamlet_example.txt", "rb");

    if (!fileread) {

        return FOPEN_ERR;
    }


    Text_Ctor(fileread, &text);

    //Sort1 (&text);

    FILE *filewrite = fopen ("Hamlet_sort.txt", "wb");


    if (!filewrite) {

        return FOPEN_ERR;
    }


    FileWriter (&text,filewrite);

    Text_Dtor(&text);

    ErrorPrints();

    return 0;
}


//-----------------------------------------------------------------------------


int ErrorPrints (void) {

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
