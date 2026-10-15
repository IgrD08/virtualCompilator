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

    stackPush(&proc->stk, proc->code[proc->IP]);

    return INTERPRETER_CORRECT;
}

returnValue add(processor *proc)
{
    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);
    stackPush(&proc->stk, a + b);

    return INTERPRETER_CORRECT;
}

returnValue sub(processor *proc)
{
    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);
    stackPush(&proc->stk, b - a);

    return INTERPRETER_CORRECT;
}

returnValue mul(processor *proc)
{
    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);
    stackPush(&proc->stk, a * b);

    return INTERPRETER_CORRECT;
}

returnValue div(processor *proc)
{
    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);
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
    int value = stackPop(&proc->stk);
    printf("%d\n", value);

    return INTERPRETER_CORRECT;
}

returnValue pop(processor *proc)
{
    proc->IP++;

    if (proc->code[proc->IP] == AX)
        proc->reg[AX] = stackPop(&proc->stk);
    if (proc->code[proc->IP] == BX)
        proc->reg[BX] = stackPop(&proc->stk);
    if (proc->code[proc->IP] == CX)
        proc->reg[CX] = stackPop(&proc->stk);
    if (proc->code[proc->IP] == DX)
        proc->reg[DX] = stackPop(&proc->stk);

    return INTERPRETER_CORRECT;
}

returnValue pushr(processor *proc)
{
    proc->IP++;

    if (proc->code[proc->IP] == AX)
        stackPush(&proc->stk, proc->reg[AX]);
    else if (proc->code[proc->IP] == BX)
        stackPush(&proc->stk, proc->reg[BX]);
    else if (proc->code[proc->IP] == CX)
        stackPush(&proc->stk, proc->reg[CX]);
    else if (proc->code[proc->IP] == DX)
        stackPush(&proc->stk, proc->reg[DX]);

    return INTERPRETER_CORRECT;
}

returnValue jmp(processor *proc)
{
    proc->IP++;
    proc->IP = proc->code[proc->IP + 1];

    return INTERPRETER_CORRECT;
}
