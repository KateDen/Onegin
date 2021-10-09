#include "Str_func.h"

// везде принтфы и ассерты!
// обработать все ворнинги
//check all returns!
// nullptr
// print original text - find the place with this note, paste there
// assert -> if in create buffer


extern int error;

//-----------------------------------------------------------------------------


int text_Ctor(FILE *fileread, struct Text *text) {

    PRINT_LINE;
    PRINT_PTR(fileread);
    assert (fileread != nullptr);

    // rename - done
    text -> file_size = file_sizer (fileread);

    text -> buffer = create_buffer (text, fileread);
    
    text -> num_lines = str_counter (text);  

    text -> lines = (struct Line*) calloc (text -> num_lines, sizeof (Line));
    
    PRINT_LINE;
    PRINT_PTR(text->lines);
    assert (text->lines);

    init_strings (text);

    return 0;
}

void text_Dtor(struct Text *text) {

    PRINT_LINE;
    PRINT_PTR(text);
    assert (text != nullptr);

    free(text->lines);
    free(text->buffer);
    text->lines = nullptr;
    text->buffer = nullptr;
}


//-----------------------------------------------------------------------------

// rename - done
ssize_t file_sizer (FILE *fileread) {

    PRINT_LINE;
    PRINT_PTR(fileread);
    assert (fileread != nullptr);


    if ((fseek (fileread, 0, SEEK_END)) == -1) {
        return error_prints (FSEEK_ERR);
    }

    ssize_t file_size = ftell (fileread);
    
    if (file_size == -1) {
        return error_prints (FTELL_ERR);
    }

    if ((fseek (fileread, 0, SEEK_SET)) == -1) {
        return error_prints (FSEEK_ERR);
    }

    return file_size;
}


//-----------------------------------------------------------------------------

//хранить переменную кода ошибки в ctore и передавать ее в функции
char* create_buffer (struct Text *text, FILE *fileread) {

    PRINT_LINE;
    PRINT_PTR(fileread);
    assert(fileread != nullptr);
    PRINT_LINE;
    PRINT_PTR(text);
    assert (text != nullptr);
        

    text -> buffer = (char *) calloc ((text -> file_size + 1), sizeof (char));
    assert (text -> buffer);                                                         //if!!

    int readsymb = fread (text -> buffer, sizeof (char), text -> file_size, fileread);

    //в ассерте вызвать fread? not good
    PRINT_LINE;
    assert (readsymb);

    text -> buffer[text -> file_size] = '\0';
    
    return text -> buffer;
}

//==================================================================================================

// new func - done 
size_t str_counter (struct Text *text) {

    PRINT_LINE;
    PRINT_PTR(text);
    assert (text != nullptr);

    char* begin_str = text -> buffer;         
    char* end_str   = text -> buffer;
    size_t numb_str = 0;

    while((end_str = strchr(begin_str, '\n')) != nullptr) {

        ++numb_str;
        begin_str = end_str + 1;
    }
  
    if (*begin_str != '\0') {

        ++numb_str;
    }

    return numb_str;
}


//-----------------------------------------------------------------------------


void init_strings (struct Text *text) {

    PRINT_LINE;
    PRINT_PTR(text);
    assert (text != nullptr);

    size_t i = 0;

    char *begin_str = text->buffer;
    char *end_str   = nullptr;

    // if (*text->buffer == '\n')

    while((end_str = strchr(begin_str, '\n')) != nullptr) {

        text -> lines[i].str    = begin_str;
        text -> lines[i].length = end_str - begin_str;
        
        // проверка на end_str > text->buffer
        if (*(end_str - 1) == '\r')
        {
            *(end_str - 1) = '\0';
        }
        else 
        {
            *end_str = '\0';
        }

        begin_str = end_str + 1;
        ++i;
    }

    if (*begin_str != '\0') {

        text -> lines[i].str = begin_str;
        text -> lines[i].length = text->buffer + text->file_size - begin_str;
    }

    for (i = 0; i < text->num_lines; i++) {

        // EOF == ?
        fputs (text->lines[i].str, stdout);       //проверки тут?
        fputc ('\n', stdout);
    }
}

//-----------------------------------------------------------------------------

//rename - done

// print original text - 1
// strchr() fputs - much faster than putc

void file_output (struct Text *text, FILE *filewrite) {     

    assert (text != nullptr);
    assert (filewrite != nullptr);

    for (size_t i = 0; i < text->num_lines; i++) {

        fputs(text->lines[i].str, filewrite);          //проверки тут?
        fputc('\n', filewrite);
    }
}


//===================================================================================


void file_original_output (struct Text *text, FILE *filewrite) {

    assert (text != nullptr);
    assert (filewrite != nullptr);

    char *str = text -> buffer;

    for (size_t i = 0; i < text -> num_lines; i++) {

        fputs (str, filewrite);                            //проверки тут?
        fputc ('\n', filewrite);
        // + 2
        str = strchr (str, '\0') + 1;

        if (*str == '\n')
        {
            ++str;
        }
    }
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
