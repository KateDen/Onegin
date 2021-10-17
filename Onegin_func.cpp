#include "Str_func.h"


extern int error;

//============================================================================================


int text_Ctor(FILE *fileread, struct Text *text) {

    assert (fileread != nullptr);

    text -> file_size = file_sizer (fileread);

    text -> buffer = create_buffer (text, fileread);
    
    text -> num_lines = str_counter (text);  

    text -> lines = (struct Line*) calloc (text -> num_lines, sizeof (struct Line));
    
    if (text -> lines == nullptr) {
        error = CALLOC_ERR;
    } 

    init_strings (text);

    return 0;
}


//==============================================================================================


ssize_t file_sizer (FILE *fileread) {

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


//===============================================================================================


char* create_buffer (struct Text *text, FILE *fileread) {

    assert(fileread != nullptr);
    assert (text != nullptr);
        

    text -> buffer = (char *) calloc ((text -> file_size + 1), sizeof (char));

    if (text -> buffer == nullptr) {
        error = CALLOC_ERR;
    }                                                        

    int readsymb = fread (text -> buffer, sizeof (char), text -> file_size, fileread);

    assert (readsymb);

    text -> buffer[text -> file_size] = '\0';
    
    return text -> buffer;
}

//==================================================================================================


size_t str_counter (struct Text *text) {

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


//====================================================================================================


void init_strings (struct Text *text) {

    assert (text != nullptr);

    size_t i = 0;

    char *begin_str = text -> buffer;
    char *end_str   = nullptr;

    if (*text -> buffer == '\n') {
        ++begin_str;
    }

    while((end_str = strchr(begin_str, '\n')) != nullptr) {

        text -> lines[i].str    = begin_str;
        text -> lines[i].length = end_str - begin_str;
        
        if (*(end_str - 1) == '\r')
        {
            *(end_str - 1) = '\0';
            text -> lines[i].length--;
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

}


//=================================================================================================


void my_qsort (void *ptr, size_t num_el, size_t size_el, int (*comparator)(const void*, const void*)) {

    int left  = 0;
    int right = num_el - 1;

    //struct String *pointer = ptr;

    struct Line pilot = *((struct Line *) ((char *) ptr + size_el * (num_el / 2)));
    //printf ("pilot = \t\t\t%c\n", *(pilot.str));

    do
    {        
        //printf ("do!\n");
        
        while (comparator ((char *)ptr + size_el * left, &pilot) < 0) {
            ++left;
            //printf ("here left = %d\n", left);        
        }
        //printf ("here left = %d\n", left);
        while (comparator ((char *)ptr + size_el * right, &pilot) > 0 && right > 0) {
            --right;
            //printf ("here right = %d\n", right);        
        }

        if (left <= right) {
            swapper ((struct Line *)((char *) ptr + size_el * left), ((struct Line *)((char *) ptr + size_el * right)), size_el);

            ++left;
            --right;
        }
        
    } while (left <= right);
    
    if (right > 0) {
        my_qsort (ptr, right + 1, size_el, comparator);
    }

    if (left < num_el) {
        my_qsort (((char *) ptr + size_el * left), num_el - left, size_el, comparator);
    }


}


//=========================================================================================================


int comparator_1 (const void *el_1, const void *el_2) {                  
   
    assert (el_1 != nullptr);
    assert (el_2 != nullptr);

    //printf ("I'm in comparator_1\n");
    int i = 0, k = 0;

    char *str_1 = ((struct Line *) el_1)->str;
    char *str_2 = ((struct Line *) el_2)->str;

    //printf ("%c\t%c\n", *str_1,*str_2);
    

    while (!isalnum (str_1[i]) && str_1[i] != '\0') ++i;   
    while (!isalnum (str_2[k]) && str_2[k] != '\0') ++k;
    
    while (str_1[i] != '\0' && str_2[k] != '\0' && str_1[i] == str_2[k]) {  

        while (!isalnum (str_1[i]) && str_1[i] != '\0') ++i;   
        while (!isalnum (str_2[k]) && str_2[k] != '\0') ++k;
            
        ++i;
        ++k; 
    }

    // printf ("%d\t%d\n", i, k);
    // return strcmp (str_1, str_2);

    return str_1[i] - str_2[k];
}


//=================================================================================================


void swapper (void *el_1, void *el_2, size_t size_el) {            //??? ...-> str => жадный алгоритм? мы же меняем структуры
    //printf ("i'm in swapper!\n");

    // char *tmp    = {};
    // char *swap_1 = ((struct Line *) el_1) -> str;
    // char *swap_2 = ((struct Line *) el_2) -> str;
    // printf ("swap: %c\t\t%c\n", *swap_1,*swap_2);


    // tmp = swap_1;
    //       swap_1 = swap_2;
    //                swap_2 = tmp;

    struct Line tmp = {};
    struct Line *left_sw  = (struct Line *) el_1;
    struct Line *right_sw = (struct Line *) el_2;
            
    tmp = *left_sw;
          *left_sw = *right_sw;
                     *right_sw = tmp;
}

//===============================================================================================


void file_output (struct Text *text, FILE *filewrite) {     

    assert (text != nullptr);
    assert (filewrite != nullptr);

    for (size_t i = 0; i < text->num_lines; i++) {

        fputs(text->lines[i].str, filewrite);          //проверки тут?
        fputc('\n', filewrite);
    }
    printf ("outputed\n");
}


//===============================================================================================


void file_original_output (struct Text *text, FILE *filewrite) {

    assert (text != nullptr);
    assert (filewrite != nullptr);

    char *str = text -> buffer;

    for (size_t i = 0; i < text -> num_lines; i++) {

        fputs (str, filewrite);
        fputc ('\n', filewrite);
        // + 2
        str = strchr (str, '\0') + 1;

        if (*str == '\n')
        {
            ++str;
        }
    }
}


//===============================================================================================


void text_Dtor(struct Text *text) {

    assert (text != nullptr);

    free(text->lines);
    free(text->buffer);
    text->lines = nullptr;
    text->buffer = nullptr;
}

