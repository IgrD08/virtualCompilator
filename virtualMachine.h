#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

struct processor
{
    stack_t stk;
    int reg[5];
    int *code;
    int IP;
};

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

#endif
