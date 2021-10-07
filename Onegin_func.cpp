#include "Str_func.h"

// везде принтфы и ассерты!
// обработать все ворнинги
//check all returns!
// nullptr
// print original text - find the place with this note, paste there



//-----------------------------------------------------------------------------


int text_Ctor(FILE *fileread, struct Text *text) {

    // rename - done
    text->file_size = file_sizer (fileread);

    text->buffer = create_buffer (text->file_size, fileread);
    
    text->num_lines = str_counter (&text); //что принимает?

    text->lines = (struct Line*) calloc (text->num_lines, sizeof (Line));
    
    assert(text->lines);

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

    if (fileread == nullptr) {
        //return FOPEN_ERR;          //?--
    }

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


int create_buffer (FILE *fileread) {

    assert(fileread != nullptr);

    text -> buffer = (char *) calloc ((text -> file_size + 1), sizeof (char));

    int readsymb = fread (text -> buffer, sizeof (char), text -> file_size, fileread);

    if (readsymb != (text -> file_size)) {
        return FREAD_ERR;
    }

    text -> buffer[text -> file_size] = '\0';


    if ((fclose (fileread)) != 0) {
        return FCLOSE_ERR;
    }

}

// new func - done 
size_t str_counter (struct Text *text) {

    assert (text != nullptr);

    char* begin_str = buffer;
    char* end_str   = buffer;
    size_t numb_str = 0;

    while((end_str = strchr(begin_str, '\n')) != nullptr) {

        ++numb_str;
        begin_str = end_str + 1;
    }

    // переделать - done
    if (begin_str != '\n') {

        ++numb_str;
    }

    return numb_str;
}


//-----------------------------------------------------------------------------


int init_strings (struct Text *text) {

    assert (text != nullptr);

    // delete
    size_t i = 0;

    // rename
    char * cor_symb = text->buffer;
    //assert (ch != NULL);          // so need?


    // почти копипаст функции подсчёта строк
    while (1) {

    
        if (*(cor_symb + i) == '\0') {

            if (i < text->file_size) {

                ++i;
                text->lines[k].str = (cor_symb + i);
                ++k;
            }

            else
                break;
        }
        ++i;
    }

    for (i = 0; i < text->num_lines; i++) {

        fputs (text->lines[k].str);
        fputc ('\n');
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

//rename
int FileWriter (struct Text *text, FILE *filewrite) {     

    // проверки
    for (int i = 0; i < text->num_lines; i++) {
        // strchr() fputs - much faster than putc
        fputs (text->lines[i].str, filewrite);
        fputc('\n', filewrite);
    }

    return 0;
}

// print original text 


//-----------------------------------------------------------------------------


/*int just_swap (struct , int i) {

    char *tmp = 0;

    tmp = Index [i];
    Index [i] = Index [i+1];
    Index [i+1] = tmp;

    return 0;
}*/
