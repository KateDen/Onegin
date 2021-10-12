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

    FILE *filewrite = fopen ("Hamlet_sort.txt", "wb");

    if (!filewrite) {
        return error_prints (FOPEN_ERR);
    }

    my_qsort (&text, text.num_lines, sizeof (char *), comparator_1);

    file_output (&text, filewrite);

    file_original_output (&text, filewrite);

    text_Dtor (&text);

    error_prints(error);

    return 0;
}


//-----------------------------------------------------------------------------


int error_prints (int error) {

    if (!error) return 0;

    switch (error)     
    {
        case FOPEN_ERR:
            perror ("File opening error");     //fprintf ("%s\n", stderr(errno));
            break;

        case PTR_ERR:
            fprintf (stderr, "Wrong pointer!\n");          //perror ("error"); - только для системных функций
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
