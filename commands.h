#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "stack.h"

enum commands
{
    HLT = 0,
    PUSH = 1,
    POPr = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    OUT_OF = 7,
    PUSHr = 8,
    AX = 9,
    BX = 10,
    CX = 11,
    DX = 12
};

enum returnValue
{
    INTERPRETER_ERROR = -1,
    INTERPRETER_CORRECT = 0
};

const int initialCapacity = 10;

#endif
