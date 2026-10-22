#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H



struct processor
{
    stack_t stk;
    stack_t returnStk;
    int RAM[3600];
    int reg[5];
    int *code;
    size_t IP;
};

const int initialCapacity = 10;

returnValue processorDestroyer(processor *proc);
void processorDump(processor *proc, size_t codeLen);

returnValue hlt(processor *proc);
returnValue push(processor *proc);
returnValue add(processor *proc);
returnValue sub(processor *proc);
returnValue mul(processor *proc);
returnValue div(processor *proc);
returnValue out(processor *proc);
returnValue pop(processor *proc);
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
returnValue draw(processor *proc);

#endif
