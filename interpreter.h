#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

enum returnValue
{
    INTERPRETER_ERROR = -1,
    INTERPRETER_CORRECT = 0
};

int fileOpenDp(const char *fileName, int flag);
returnValue fileCloseDp(int descriptor);

#endif
