#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

struct processor
{
    stack_t stk;
    stack_t returnStk;
    int RAM[100];
    int reg[5];
    int *code;
    size_t IP;
};

const int NUMBER_OF_FUNCTIONS = 21;

const int initialCapacity = 10;

returnValue processorDestroyer(processor *proc);

returnValue hlt(processor *proc);
returnValue push(processor *proc);
returnValue add(processor *proc);
returnValue sub(processor *proc);
returnValue mul(processor *proc);
returnValue div(processor *proc);
returnValue out(processor *proc);
returnValue pop(processor *proc);
returnValue pushr(processor *proc);
returnValue jmp(processor *proc);
returnValue ja(processor *proc);
returnValue jae(processor *proc);
returnValue jb(processor *proc);
returnValue jbe(processor *proc);
returnValue je(processor *proc);
returnValue jne(processor *proc);
returnValue in(processor *proc);
returnValue call(processor *proc);
returnValue ret(processor *proc);
returnValue pushm(processor *proc);
returnValue popm(processor *proc);

#endif
