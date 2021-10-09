#include "Str_func.h"

int error = 0;

int main () {

    struct Text text  = {};
//errno = o; - обнулять перед системными вызовами, следить чтобы не сохранялся код старой ошибки

    FILE *fileread = fopen ("Hamlet_example.txt", "rb");

    if (!fileread) {
        printf ("%p \t fread err here\n", fileread);
        return error_prints (FREAD_ERR);
    }

    error = text_Ctor(fileread, &text);

    if (fclose(fileread) == EOF) {
        return error_prints (FCLOSE_ERR);
    }

    //Sort - вызов

    FILE *filewrite = fopen ("Hamlet_sort.txt", "wb");

    if (!filewrite) {
        return error_prints (FOPEN_ERR);
    }

    file_output (&text, filewrite);

    file_original_output (&text, filewrite);

    text_Dtor (&text);

    error_prints(error);

    return 0;
}


//-----------------------------------------------------------------------------


int error_prints (int error) {

    if (!error) return 0;

    switch (error)         //мб всю печать ошибок через perror?
    {
        case FOPEN_ERR:
            fprintf (stderr, "File opening error!\n");     //fprintf ("%s\n", stderr(errno));
            break;

        case PTR_ERR:
            fprintf (stderr, "Wrong pointer!\n");          //perror ("error"); - только для системных функций
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

        case FPUT_ERR:
            fprintf (stderr, "File writing error!\n");
            break;

        default:
            perror("Undefined error");
    }

    return error;
}
