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
    HLT                = 0,
    PUSH               = 1,
    ADD                = 2,
    SUB                = 3,
    MUL                = 4,
    DIV                = 5,
    OUT_OF             = 6,
    POPr               = 7,
    JMP                = 8,
    REGISTER_PLACEMENT = 9, //TODO - выделить в отдельный enum
    AX                 = 10,
    BX                 = 11,
    CX                 = 12,
    DX                 = 13
};

enum returnValue
{
    PROGRAM_OVER        = -2,
    INTERPRETER_ERROR   = -1,
    INTERPRETER_CORRECT = 0
};

const int initialCapacity = 10;

#endif
