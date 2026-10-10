#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

struct processor
{
    stack_t stk;
    int register[4];
    int *code;
    int IP;
};

#endif
