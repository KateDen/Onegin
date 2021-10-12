#include "Str_func.h"

// везде принтфы и ассерты!
// обработать все ворнинги
//check all returns!
// nullptr
// print original text - find the place with this note, paste there
// assert -> if in create buffer


extern int error;

//============================================================================================


int text_Ctor(FILE *fileread, struct Text *text) {

    assert (fileread != nullptr);

    //int error = 0;
    text -> file_size = file_sizer (fileread);

    text -> buffer = create_buffer (text, fileread);
    
    text -> num_lines = str_counter (text);  

    text -> lines = (struct Line*) calloc (text -> num_lines, sizeof (Line));
    
    if (text -> lines == nullptr) {
        error = CALLOC_ERR;
    } 

    init_strings (text);

   // my_qsort ((void *) text -> lines, text -> num_lines, sizeof (text -> lines), comparator_1);     

    return 0;
}

//=========================================================================================================

void my_qsort (void *ptr, size_t num_el, size_t size_el, int (*comparator_1)(const void*, const void*)) {

    char *first_str = (char *) ptr;

    char *left = ((struct Line *) ptr) -> str; 
    char *right = ((struct Line *) ptr + num_el - 1) -> str; 
    char *middle = ((struct Line *) (num_el / 2)) -> str;  

        do
        {
           while (comparator_1 (left, middle) < 0) {
                ++left;
             }
            while  (comparator_1 (right, middle) > 0)
                --right;
                
            if (left <= right) {
                swapper (left, right);
            }

        } while (left <= right);

        if (right > first_str) {
            my_qsort ((void *) right, num_el, size_el, comparator_1);
        }

        if ((size_t) left < num_el) {
            my_qsort ((void *) left, num_el, size_el, comparator_1);
        }
}


//=========================================================================================================


// void my_qsort (void *ptr, size_t num_el, size_t size_el, int (*comp)(const void *, const void *)) {

//     int i = 0;

//     char *left = ((struct Line *) ptr) -> str; 
//     char *right = ((struct Line *) ptr + num_el - 1) -> str; 
//     char *middle = ((struct Line *) num_el / 2) -> str;          
//     //char *last = 0;  ?

//     if (left >= right) {                     // if 2 elements in an arrow
//         return;
//     }

//     swapper (right, (right - left) / 2);                 //redo

//     char *last = left;                                             //for what?

//     whle (left <= right) {
//         if (comparator_1 ((const void *) left, (const void *) middle) > 0) {          //to be continued
//             ++left;
//         }

//         if (comparator_1 ((const void *) left, (const void *) middle) < 0) {          //to be continued
//             --right;
//         }

//         if (comparator_1 ((const void *) left, (const void *) middle) == 100 || comparator_1 ((const void *) left, (const void *) right) == -100) {          //to be continued

//         }


//     for (i = left + 1; i <= right; ++i) {                      // redo
//         if (v[i] < v[left]) {
//             swapper (++last, i);
//         }

//         swapper (left, last);

//         my_qsort ();
//         my_qsort (last + 1, right);
//     }

// }



int comparator_1 (const void *el_1, const void *el_2) {                    // almost done
    
    assert (el_1 != nullptr);
    assert (el_2 != nullptr);

    char *str_1 = ((struct Line *) el_1) -> str;
    char *str_2 = ((struct Line *) el_1) -> str;

    while (*str_1 != '\0' || *str_2 != '\0') {
        
        if (isalnum (*str_1) == 0) ++str_1;

        if (isalnum (*str_2) == 0) ++str_2;

        return str_1 - str_2;            
    }

    printf ("1\n");

    if (*str_1 == '\0') {
        ++str_1;
    } 

    if (*str_2 == '\0') {
        ++str_2;
    }

    return 0;
}


char *is_alnum (char *str) {                    //done

    while (1) {
        if (isalnum (*str) != 0) {

            return str;
        }

        else
            ++str;
    }
}


int sort_1 (struct Text *text, int error) {                // -> qsort 2
    
    return 0;
}


void swapper (void *left, void *right) {

    char *tmp = 0;

    char *left_sw = (char *) left;
    char *right_sw = (char *) right;

    tmp = left_sw;
    left_sw = right_sw;
    right_sw = tmp;
}


//===============================================================================================


void text_Dtor(struct Text *text) {

    assert (text != nullptr);

    free(text->lines);
    free(text->buffer);
    text->lines = nullptr;
    text->buffer = nullptr;
}


//===============================================================================================


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

//хранить переменную кода ошибки в ctore и передавать ее в функции
char* create_buffer (struct Text *text, FILE *fileread) {

    assert(fileread != nullptr);
    assert (text != nullptr);
        

    text -> buffer = (char *) calloc ((text -> file_size + 1), sizeof (char));

    if (text -> buffer == nullptr) {
        error = CALLOC_ERR;
    }                                                        

    int readsymb = fread (text -> buffer, sizeof (char), text -> file_size, fileread);

    //PRINT_LINE;
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
        
        // проверка на end_str > text->buffer - done
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

    // for (i = 0; i < text->num_lines; i++) {

    //     // EOF == ?
    //     fputs (text->lines[i].str, stdout);       //проверки тут?
    //     fputc ('\n', stdout);
    // }
}

//=================================================================================================

//=================================================================================================


void file_output (struct Text *text, FILE *filewrite) {     

    assert (text != nullptr);
    assert (filewrite != nullptr);

    for (size_t i = 0; i < text->num_lines; i++) {

        fputs(text->lines[i].str, filewrite);          //проверки тут?
        fputc('\n', filewrite);
    }
}


//===============================================================================================


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


