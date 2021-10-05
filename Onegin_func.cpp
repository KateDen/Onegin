
#include "Str_func.h"



int Text_Ctor(FILE *fileread, struct Text *text) {

    text->file_size = FileReader (text, fileread);

    text->lines = (struct Line*) calloc (text->num_lines, sizeof (Line));

    //char* begin_str = text->lines[i].str;          ///////////////////////////////////////

    InitStrings (text);
}

int Text_Dtor(struct Text *text) {

    free(text->lines);
    free(text->buffer);
    text->lines = nullptr;
    text->buffer = nullptr;
    return 0;
}


//-----------------------------------------------------------------------------


int FileReader (struct Text *text, FILE *fileread) {

    int size_of_element = sizeof (char);


    if (fileread == NULL) {

        return FOPEN_ERR;
    }

    if ((fseek (fileread, 0, SEEK_END)) != 0) {

        return FSEEK_ERR;
    }

    text -> file_size = ftell (fileread);

    if ((fseek (fileread, 0, SEEK_SET)) != 0) {

        return FSEEK_ERR;
    }

    return 0;
}


//-----------------------------------------------------------------------------


int Bufferizer (struct Text *text, FILE *fileread) {

    text -> buffer = (char *) calloc ((text -> file_size + 1), sizeof (char));

    int readsymb = fread (text -> buffer, sizeof (char), (text -> file_size + 1), fileread);

    if (readsymb != (text -> file_size)) {

        return FREAD_ERR;
    }

    text -> buffer[text -> file_size] = '\0';


    if ((fclose (fileread)) != 0) {

        return FCLOSE_ERR;
    }


    int counter = 0, k = 0;
    char symbol = 0;
    char *inl = 0;

    for (; k <= text -> file_size;) {

        inl = strchr((const char*)*(text -> buffer + (int)(inl - text -> buffer)), '\n'); //?

        if (!inl) {     //???

            ++counter;
            ++inl;
            ++k;
        }
    }

    if (*(text -> buffer + (int)(inl - text -> buffer))!= '\n') {        // Обработка символа на конце буффера

        text -> num_lines = (counter + 1);
    }

    else text -> num_lines = (counter);


    /*while (*(text -> buffer + symbol) != '\0') {      //strchr()

        if (*(text -> buffer + symbol) == '\n')
        {
            *(text -> buffer + symbol) = '\0';
            counter++;
        }

        ++symbol;
    } */

    //printf ("counter = %d\n", counter);

    return 0;
}


//-----------------------------------------------------------------------------


int InitStrings (struct Text *text) {

    //printf ("Initstrings started.\n");
    assert (text != NULL);

    int k = 1;
    int i = 0;

    char *ch = text->buffer;
    assert (ch != NULL);


    text->lines[i].str = ch;
    // strtok

    while (1) {

        if (*(ch + i) == '\0') {

            if (i < text->file_size) {

                ++i;
                text->lines[k].str = (ch + i);
                ++k;
            }

            else
                break;
        }
        ++i;
    }

    for (i = 0; i < text->num_lines; i++) {

        puts (text->lines[k].str);
    }

    free (text -> buffer);
    return 0;
}


//-----------------------------------------------------------------------------
/*qsort(buffer, n, sizeof(int), comp);

int comp(const void*, const void*);

my_qsort(struct Text* text, int (*comp) (const void*, const void*))     //оболочка example
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


int FileWriter (struct Text *text, FILE *filewrite) {          //////////////////////////////////

    for (int i = 0; i < text->num_lines; i++) {

        fputs (text->lines[i].str, filewrite);
    }

    fclose (filewrite);

    return 0;
}


//-----------------------------------------------------------------------------


int JustSwap (char **Index, int i) {

    char *tmp = 0;

    tmp = Index [i];
    Index [i] = Index [i+1];
    Index [i+1] = tmp;
    return 0;
}
