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
    PUSHr              = 8,
    JMP                = 9,
    JA                 = 10,
    JAE                = 11,
    JB                 = 12,
    JBE                = 13,
    JE                 = 14,
    JNE                = 15,
    IN_OF              = 16,
    CALL               = 17,
    RET                = 18,
    PUSHm              = 19,
    POPm               = 20,
};

enum registerEnum
{
    AX                 = 1,
    BX                 = 2,
    CX                 = 3,
    DX                 = 4
};

enum returnValue
{
    PROGRAM_OVER        = -2,
    INTERPRETER_ERROR   = -1,
    INTERPRETER_CORRECT = 0
};

#endif
