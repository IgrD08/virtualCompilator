#include "commands.h"
#include "stack.h"
#include "virtualMachine.h"

returnValue processorDestroyer(processor *proc)
{
    stackDestroy(&proc->stk);
    stackDestroy(&proc->returnStk);

    free(proc->code);

    return INTERPRETER_CORRECT;
}

void processorDump(processor *proc, size_t codeLen)
{
    stackDump(&proc->stk, stdout);

    for (size_t i = 0; i < codeLen; i++)
    {
        printf("%d ", proc->code[i]);
    }

    printf("\n");

    for (size_t i = 0; i < 2 * proc->IP - 1; i++)
    {
        printf(" ");
    }

    printf("^\n");

    getchar();

    return;
}

returnValue hlt(processor *proc)
{
    processorDestroyer(proc);

    exit(EXIT_SUCCESS);

    return INTERPRETER_CORRECT;
}

returnValue push(processor *proc)
{
    int res = 0;
    int *args = &proc->code[proc->IP + 1];
    int commandCode = proc->code[proc->IP];

    if (commandCode & 0x20)
    {
        res += *args;
        args++;
        proc->IP++;
    }
    if (commandCode & 0x40)
    {
        res += proc->reg[*args];
        args++;
        proc->IP++;
    }
    if (commandCode & 0x80)
    {
        res = proc->RAM[res];
    }

    stackPush(&proc->stk, res);

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
    printf("<<%d>>\n", value);

    return INTERPRETER_CORRECT;
}

returnValue pop(processor *proc)
{
    int res = 0;
    int regIndex = -1;
    int *args = &proc->code[proc->IP + 1];
    int commandCode = proc->code[proc->IP];

    if (commandCode & 0x40)
    {
        regIndex = *args;

        res += proc->reg[regIndex];
        args++;
        proc->IP++;

    }
    if (commandCode & 0x20)
    {
        res += *args;
        args++;
        proc->IP++;
    }

    int valueToStore = stackPop(&proc->stk);

    if (commandCode & 0x80)
    {
        proc->RAM[res] = valueToStore;
    }
    else if (commandCode & 0x40)
    {
        proc->reg[regIndex] = valueToStore;
    }

    return INTERPRETER_CORRECT;
}

returnValue jmp(processor *proc)
{
    proc->IP = (size_t)proc->code[proc->IP + 1];

    proc->IP--;//возникает, так как в virtualMachine в цикле каждую итерацию proc->IP увеличивается на 1

    return INTERPRETER_CORRECT;
}

returnValue ja(processor *proc)
{
    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);

    if (a > b)
        jmp(proc);
    else
        proc->IP++;

    return INTERPRETER_CORRECT;
}

returnValue jae(processor *proc)
{
    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);

    if (a >= b)
        jmp(proc);
    else
        proc->IP++;

    return INTERPRETER_CORRECT;
}

returnValue jb(processor *proc)
{
    proc->IP++;

    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);

    if (a < b)
        jmp(proc);
    else
        proc->IP++;

    return INTERPRETER_CORRECT;
}

returnValue jbe(processor *proc)
{
    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);

    if (a <= b)
        jmp(proc);
    else
        proc->IP++;

    return INTERPRETER_CORRECT;
}

returnValue je(processor *proc)
{
    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);

    if (a == b)
        jmp(proc);
    else
        proc->IP++;

    return INTERPRETER_CORRECT;
}

returnValue jne(processor *proc)
{
    int a = stackPop(&proc->stk);
    int b = stackPop(&proc->stk);

    if (a != b)
        jmp(proc);
    else
        proc->IP++;

    return INTERPRETER_CORRECT;
}

returnValue in(processor *proc)
{
    int value = 0;

    if(scanf("%d", &value) == 1)
        stackPush(&proc->stk, value);
    else
        return INTERPRETER_ERROR;

    return INTERPRETER_CORRECT;
}

returnValue call(processor *proc)
{
    stackPush(&proc->returnStk, proc->IP + 1);

    jmp(proc);

    return INTERPRETER_CORRECT;
}

returnValue ret(processor *proc)
{
    proc->IP = (size_t)stackPop(&proc->returnStk);

    return INTERPRETER_CORRECT;
}

returnValue draw(processor *proc)
{
    proc->IP++;

    size_t size = proc->reg[proc->code[proc->IP]];

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            printf("[%c]", proc->RAM[size * i + j]);
        }

        printf("\n");
    }


    return INTERPRETER_CORRECT;
}
