#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <TXLib.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>

int Text_Ctor (FILE *fileread, struct Text *text);
int Text_Dtor(struct Text *text);

int FileReader (struct Text *text, FILE *fileread);
int Bufferizer (struct Text *text, FILE *fileread);
int InitStrings (struct Text *text);

int Sort1 (struct Text *text, int numlines);

int JustSwap (struct Text *text, int i);
                                                                        //merge sort - сортировка слиянием
int FileWriter (struct Text *text);

int ErrorPrints (void);

