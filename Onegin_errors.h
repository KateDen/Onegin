#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <TXLib.h>
#include <assert.h>
#include <errno.h>

/*enum error_consts {
    FOPEN_ERR,
    EOF_READ_ERR,
    FREAD_ERR,
    FSEEK_ERR,
    FCLOSE_ERR,

    BUFFERR
};

int FileReadErr (char* buffer)
{
    //int err_state = FileBufferize (txtStructPtr);
    //switch (err_state)

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

    return 0;
}    */
