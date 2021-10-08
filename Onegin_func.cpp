#include "Str_func.h"

// везде принтфы и ассерты!
// обработать все ворнинги
//check all returns!
// nullptr
// print original text - find the place with this note, paste there



//-----------------------------------------------------------------------------


int text_Ctor(FILE *fileread, struct Text *text) {

    assert (fileread != nullptr);

    // rename - done
    text->file_size = file_sizer (fileread);

    text->buffer = create_buffer (text, fileread);
    
    text->num_lines = str_counter (text); //что принимает?

    text->lines = (struct Line*) calloc (text->num_lines, sizeof (Line));
    
    assert (text->lines);

    init_strings (text);

    return 0;
}

int text_Dtor(struct Text *text) {

    free(text->lines);
    free(text->buffer);
    text->lines = nullptr;
    text->buffer = nullptr;
    return 0;
}


//-----------------------------------------------------------------------------

// rename - done
ssize_t file_sizer (FILE *fileread) {

    assert (fileread != nullptr);

    if ((fseek (fileread, 0, SEEK_END)) == -1) {
        return FSEEK_ERR;
    }

    ssize_t file_size = ftell (fileread);
    
    if (file_size == -1) {
        return FTELL_ERR;
    }

    if ((fseek (fileread, 0, SEEK_SET)) == -1) {
        return FSEEK_ERR;
    }

    return file_size;
}


//-----------------------------------------------------------------------------


char* create_buffer (struct Text *text, FILE *fileread) {

    assert(fileread != nullptr);        

    text -> buffer = (char *) calloc ((text -> file_size + 1), sizeof (char));

    int readsymb = fread (text -> buffer, sizeof (char), text -> file_size, fileread);

    //в ассерте вызвать fread?
    assert (readsymb != 0);
    /*if (readsymb != (text -> file_size)) {   //ф-я не возвращает int
        return FREAD_ERR;
    }*/

    text -> buffer[text -> file_size] = '\0';
    
    return text -> buffer;
}

// new func - done 
size_t str_counter (struct Text *text) {

    assert (text != nullptr);

    char* begin_str = text -> buffer;         
    char* end_str   = text -> buffer;
    size_t numb_str = 0;

    while((end_str = strchr(begin_str, '\n')) != nullptr) {

        ++numb_str;
        begin_str = end_str + 1;
    }

    // переделать - done
    if (*begin_str != '\n') {

        ++numb_str;
    }

    return numb_str;
}


//-----------------------------------------------------------------------------


int init_strings (struct Text *text) {

    assert (text != nullptr);

    size_t i = 0;

    // rename - done
    char *begin_str = text->buffer;
    char *end_str = text->buffer;

    // почти копипаст функции подсчёта строк - done

    while((end_str = strchr(begin_str, '\0')) != nullptr) {

        text -> lines[i].str = begin_str;
        text -> lines[i].length = end_str - begin_str;
        begin_str = end_str + 1;
        ++i;
    }

    // переделать - done
    if (*begin_str != '\n') {

        *(text -> lines[i].str) = '\n';
    }

    for (i = 0; i < text->num_lines; i++) {

        fputs (text->lines[i].str, stdout);
        fputc ('\n', stdout);
    }

    return 0;
}

//-----------------------------------------------------------------------------

//rename - done

// print original text - 1
// strchr() fputs - much faster than putc

int file_output (struct Text *text, FILE *filewrite) {     

    assert (filewrite != 0);
    // проверки - done
    for (size_t i = 0; i < text->num_lines; i++) {

        fputs (text->lines[i].str, filewrite);          //проверки тут?
        fputc('\n', filewrite);
    }

    return 0;
}

int file_original_output (struct Text *text, FILE *filewrite) {

    assert (filewrite != nullptr);

    char *str = text -> buffer;

    for (size_t i = 0; i <= text -> num_lines; ) {

        fputs (str, filewrite);
        fputc ('\n', filewrite);
        str = strchr (str, '\0') + 1;
 
    }
    return 0;
}


//-----------------------------------------------------------------------------
/*qsort(buffer, n, sizeof(int), comp);

int comp(const void*, const void*);

my_qsort(struct Text* text, int (*comp) (const void*, const void*))    
{
    q_sort(text->buffer, text->nline, sizeof(Line), comp);
}


q_sort(buffer, n, sizeof(line), comp_lr);
 */

/*int Sort1 (char **Index, int num_lines)
{
    printf ("Sort1 started.\n\n");

    int counter = 1, i = 0, str_comp_res = 0, strlen = 0;

    while (counter != 0)
    {
        counter = 0;

        for (int k = 0; k < num_lines - 1; ++k)
        {
            for (i = 0; i < num_lines; ++i)
            {
                str_comp_res = strcmp (Index [i], Index [i+1]);

                if (str_comp_res > 0)
                {
                    if (JustSwap (Index, i) == 0)
                    {
                        counter = 1;
                    }

                    else return SWAP_ERR;
                }
            }
        }
    }

    printf ("111111111111111111111111111111111111\n\n");

    for (i = 0; i < num_lines; ++i)
        puts (Index [i]);


    return 0;
}  */

//-----------------------------------------------------------------------------


/*int just_swap (struct , int i) {

    char *tmp = 0;

    tmp = Index [i];
    Index [i] = Index [i+1];
    Index [i+1] = tmp;

    return 0;
}*/
