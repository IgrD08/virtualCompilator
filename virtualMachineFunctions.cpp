#include "commands.h"
#include "stack.h"
#include "virtualMachine.h"

void push(processor *proc)
{
    proc->IP++;
    stackPush(&proc->stk, proc->code[proc->IP]);

    return;
}

void add(processor *proc)
{
    structEnum_t a = stackPop(&proc->stk);
    structEnum_t b = stackPop(&proc->stk);
    stackPush(&proc->stk, a + b);

    return;
}

void sub(processor *proc)
{
    proc->IP++;
    stackPush(&proc->stk, proc->code[proc->IP]);

    return;
}

void push(processor *proc)
{
    proc->IP++;
    stackPush(&proc->stk, proc->code[proc->IP]);

    return;
}

void push(processor *proc)
{
    proc->IP++;
    stackPush(&proc->stk, proc->code[proc->IP]);

    return;
}

void push(processor *proc)
{
    proc->IP++;
    stackPush(&proc->stk, proc->code[proc->IP]);

    return;
}

void push(processor *proc)
{
    proc->IP++;
    stackPush(&proc->stk, proc->code[proc->IP]);

    return;
}
