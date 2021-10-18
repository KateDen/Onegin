#include "Str_func.h"

int error = 0;

// русский (желательно, но не обязательно)

int main (int argc, const char *argv[]) {

    setlocale (LC_ALL, "ru_RU.cp1251");

    const char *inputf  = "Hamlet_example.txt";
    const char *outputf = "Hamlet_sort.txt";

    if (argc == 3) {
        inputf  = argv[1];
        outputf = argv[2];
    }

    struct Text text  = {};
    
    FILE *fileread = fopen (inputf, "rb");

    if (!fileread) {
        printf ("%p \t fread err here\n", fileread);
        return error_prints (FREAD_ERR);
    }

    error = text_Ctor(fileread, &text);

    if (fclose(fileread) == EOF) {
        return error_prints (FCLOSE_ERR);
    }

    my_qsort (text.lines, text.num_lines, sizeof (struct Line), comparator_1);
    
    FILE *filewrite = fopen (outputf, "wb");

    if (!filewrite) {
        return error_prints (FOPEN_ERR);
    }

    file_output (&text, filewrite);

    fputs ("\n\n!!!!!!!********PTPTPTPTPPTPTPTPTPTPTPTPTPTPTPPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPPTPTPTPTPTPTPTPTPT********!!!!!!!\n\n", filewrite);

    my_qsort (text.lines, text.num_lines, sizeof (struct Line), comparator_2);

    file_output (&text, filewrite);

    fputs ("\n\n!!!!!!!********PTPTPTPTPPTPTPTPTPTPTPTPTPTPTPPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPTPPPTPTPTPTPTPTPPTPT********!!!!!!!\n\n", filewrite);

    file_original_output (&text, filewrite);

    text_Dtor (&text);

    error_prints (error);

    return 0;
}


//-----------------------------------------------------------------------------


int error_prints (int error) {

    if (!error) return 0;

    switch (error)     
    {
        case FOPEN_ERR:
            perror ("File opening error");
            break;

        case PTR_ERR:
            fprintf (stderr, "Wrong pointer!\n");
            break;

        case FREAD_ERR:
            perror ("Fread error");
            break;

        case FSEEK_ERR:
            perror ("File seek error");
            break;

        case FCLOSE_ERR:
            perror ("File close error");
            break;

        case SWAP_ERR:
            fprintf (stderr, "Swap error!\n");
            break;

        case CALLOC_ERR:
            fprintf (stderr, "File writing error!\n");
            break;

        default:
            perror("Undefined error");
    }

    return error;
}
