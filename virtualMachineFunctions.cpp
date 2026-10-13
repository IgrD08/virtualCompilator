#include "commands.h"
#include "stack.h"
#include "virtualMachine.h"

returnValue hlt(processor *proc)
{
    return PROGRAM_OVER;
}
//TODO - СДЕЛАТЬ ДВОЙНОЙ ПРОХОД
returnValue push(processor *proc)
{
    proc->IP++;

    if (proc->code[proc->IP] == AX)
        stackPush(&proc->stk, proc->reg[AX - REGISTER_PLACEMENT]);
    else if (proc->code[proc->IP] == BX)
        stackPush(&proc->stk, proc->reg[BX - REGISTER_PLACEMENT]);
    else if (proc->code[proc->IP] == CX)
        stackPush(&proc->stk, proc->reg[CX - REGISTER_PLACEMENT]);
    else if (proc->code[proc->IP] == DX)
        stackPush(&proc->stk, proc->reg[DX - REGISTER_PLACEMENT]);
    else
        stackPush(&proc->stk, proc->code[proc->IP]);

    return INTERPRETER_CORRECT;
}

returnValue add(processor *proc)
{
    structEnum_t a = stackPop(&proc->stk);
    structEnum_t b = stackPop(&proc->stk);
    stackPush(&proc->stk, a + b);

    return INTERPRETER_CORRECT;
}

returnValue sub(processor *proc)
{
    structEnum_t a = stackPop(&proc->stk);
    structEnum_t b = stackPop(&proc->stk);
    stackPush(&proc->stk, b - a);

    return INTERPRETER_CORRECT;
}

returnValue mul(processor *proc)
{
    structEnum_t a = stackPop(&proc->stk);
    structEnum_t b = stackPop(&proc->stk);
    stackPush(&proc->stk, a * b);

    return INTERPRETER_CORRECT;
}

returnValue div(processor *proc)
{
    structEnum_t a = stackPop(&proc->stk);
    structEnum_t b = stackPop(&proc->stk);
    if (a != 0)
    {
        stackPush(&proc->stk,  b / a);
    }
    else
    {
        fprintf(stderr, "Unable operation\n");

        return INTERPRETER_ERROR;
    }

    return INTERPRETER_CORRECT;
}

returnValue out(processor *proc)
{
    structEnum_t value = stackPop(&proc->stk);
    printf(SPEC"\n", value);

    return INTERPRETER_CORRECT;
}

returnValue pop(processor *proc)
{
    proc->IP++;

    if (proc->code[proc->IP] == AX)
        proc->reg[AX - REGISTER_PLACEMENT] = stackPop(&proc->stk);
    if (proc->code[proc->IP] == BX)
        proc->reg[BX - REGISTER_PLACEMENT] = stackPop(&proc->stk);
    if (proc->code[proc->IP] == CX)
        proc->reg[CX - REGISTER_PLACEMENT] = stackPop(&proc->stk);
    if (proc->code[proc->IP] == DX)
        proc->reg[DX - REGISTER_PLACEMENT] = stackPop(&proc->stk);

    return INTERPRETER_CORRECT;
}

returnValue jmp(processor *proc)
{
    proc->IP++;
    proc->IP = proc->code[proc->IP];

    return INTERPRETER_CORRECT;
}
