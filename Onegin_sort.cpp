#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>                                         ///!!!!!!! buffer was declared as array => memory error!!!
#include <TXLib.h>
                                                   /*
                                                   github desktop + файл .gitignore где прописано,
                                                   что игнорить при сохранении на гитхаб - более профессионально
                                                   и требует commit summary
                                                   *.layout  - расположение окон кодблокса
                                                   *.bmarks - закладки в больших проектах
                                                   fprintf str err - писать в поток для вывода ошибок
                                                   (сообщение об ошибке + подсказки, как пользоваться программой)
                                                   специальная опция /? или (--h --help - linux) - написать как пользоваться
                                                   и выйти из программы - новый код ошибки для запроса помощи REQUEST_HELP
                                                   rewind (только для потока-файла) - установка позиции файла в 0 быстро!
                                                   */

#include <sys/types.h>
#include <assert.h>
#include <errno.h>

int FileBufferize (struct text *txtStructPtr);
int IndexFiller (char **Index, char *buffer);      //initstrings
int Sort1 (char **Index, int MAXLINES);
int ErrorPrints (void);                                           //merge sort - сортировка слиянием
                                                                  //лучше самостоятельно написать сортировку,
                                                                  //потом работать над скоростью и другими сортировками
                                                                  // - так и говорить менторам
FILE *FileWriter (int MAXLINES, char **Index);

enum error_consts {
    FOPEN_ERR = 1,
    EOF_READ_ERR,
    FREAD_ERR,
    FSEEK_ERR,
    FCLOSE_ERR,

    BUFFERR
};


struct text
{
    char *buffer;                                              /// написать функции для работы со структурой
                                                               /// для чтения структуры и для разрушения структуры
    int MAXLINES;                                              /// код быквы ё 241
    int MAXLETTERS;                                            /// функции как заменять \n на \0
};

int n = 0;


#include "Onegin_func.h"
#include "Onegin_errors.h"


int main ()
{
    /**setlocale (LC_ALL, "Russian");
    qsort (void *getlines, MAXLINES, size_t MAXWORDS, strcmp (*line1, *line2)); */
    struct text Text;
    struct text *txtStructPtr = &Text;
    //int a;
    //int* a = (int*) calloc(1, sizeof(int));

    n = FileBufferize (txtStructPtr);

    ErrorPrints ();

    char *Index [txtStructPtr -> MAXLINES];

    IndexFiller (Index, txtStructPtr -> buffer);

    Sort1 (Index, txtStructPtr -> MAXLINES);

    FileWriter (txtStructPtr -> MAXLINES, Index);

    //qsort ();


    return 0;
}


//-----------------------------------------------------------------------------


int ErrorPrints (void)
{
    switch (n)
    {
        case FOPEN_ERR:
            printf ("File opening error!\n");
            break;

        case EOF_READ_ERR:
            printf ("EOF error!\n");
            break;

        case FREAD_ERR:
            printf ("Fread error!\n");
            break;

        case FSEEK_ERR:
            printf ("File seek error!\n");
            break;

        case FCLOSE_ERR:
            printf ("File close error!\n");
            break;

        default: return 0;
    }
}
