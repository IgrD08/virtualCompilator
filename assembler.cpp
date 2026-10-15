#include "commands.h"
#include "stack.h"
#include "assembler.h"

int main(int argc, char *argv[])
{
    fileInfoStruc_t fileToReadInfo = {NULL, "data.asm", NULL, 0, NULL};

    if (fileProc(&fileToReadInfo) == INTERPRETER_ERROR)
        return 1;

    int value = 0;
    char command[10] = {};
    char regist[10] = {};

    int *data = NULL;
    int dataIndex = 0;
    int labels[20] = {};//заполнять -1

    if ((data = (int *)calloc(fileToReadInfo.numberOfLines * 2, sizeof(int))) == NULL)
        return 1;

    for (int i = 0; i < fileToReadInfo.numberOfLines; i++)
    {
        command[0] = '\0';
        regist[0] = '\0';
        value = 0;

        if (sscanf(fileToReadInfo.individualLines[i], "%s", command) <= 0)
            continue;

        switch (command[0])
        {
            case 'P':
                if (!strcmp(command, "PUSH"))
                {
                    if (sscanf(fileToReadInfo.individualLines[i], "%*s %s", regist) <= 0)
                        break;

                    if (atoi(regist) == 0)
                    {
                        data[dataIndex] = PUSHr;
                        dataIndex++;

                        if (!strcmp(regist, "AX"))
                        data[dataIndex] = AX;
                    else if (!strcmp(regist, "BX"))
                        data[dataIndex] = BX;
                    else if (!strcmp(regist, "CX"))
                        data[dataIndex] = CX;
                    else if (!strcmp(regist, "DX"))
                        data[dataIndex] = DX;
                    else
                        printf("Register does not found");

                        dataIndex++;
                    }
                    else
                    {
                        value = atoi(regist);
                        data[dataIndex] = PUSH;
                        dataIndex++;
                        data[dataIndex] = value;
                        dataIndex++;
                    }
                }

                if (!strcmp(command, "POPr"))
                {
                    if (sscanf(fileToReadInfo.individualLines[i], "%*s %s", regist) <= 0)
                        break;

                    data[dataIndex] = POPr;
                    dataIndex++;

                    if (!strcmp(regist, "AX"))
                        data[dataIndex] = AX;
                    else if (!strcmp(regist, "BX"))
                        data[dataIndex] = BX;
                    else if (!strcmp(regist, "CX"))
                        data[dataIndex] = CX;
                    else if (!strcmp(regist, "DX"))
                        data[dataIndex] = DX;
                    else
                        printf("Register does not found");

                    dataIndex++;
                }

                break;

            case 'A':

                if (!strcmp(command, "ADD"))
                {
                    data[dataIndex] = ADD;
                    dataIndex++;
                }

                break;

            case 'S':

                if (!strcmp(command, "SUB"))
                {
                    data[dataIndex] = SUB;
                    dataIndex++;
                }

                break;

            case 'M':

                if (!strcmp(command, "MUL"))
                {
                    data[dataIndex] = MUL;
                    dataIndex++;
                }

                break;

            case 'D':

                if (!strcmp(command, "DIV"))
                {
                    data[dataIndex] = DIV;
                    dataIndex++;
                }

                break;

            case 'O':

                if (!strcmp(command, "OUT_OF"))
                {
                    data[dataIndex] = OUT_OF;
                    dataIndex++;
                }

                break;

            case 'J':

                if (!strcmp(command, "JMP"))
                {
                    if (sscanf(fileToReadInfo.individualLines[i], "%*s %s", &regist) <= 0)
                        break;

                    data[dataIndex] = JMP;
                    dataIndex++;

                    if (regist[0] == ':')
                    {
                        if ((value = atoi(&regist[1])) == 0)
                            break;

                        data[dataIndex] = labels[value];
                        dataIndex++;
                    }
                    else
                    {
                        data[dataIndex] = value;
                        dataIndex++;
                    }
                }

                break;

            case 'H':

                if (!strcmp(command, "HLT"))
                {
                    data[dataIndex] = HLT;
                    dataIndex++;
                }

                break;

            case ':':

                if ((value = atoi(&command[1])) == 0)
                    break;

                labels[value] = dataIndex;

                break;

            default:
                fprintf(stderr, "No such command");

                break;
        }
    }
    // for (int i = 0; i < dataIndex; i++)
    // {
    //     printf("%d ", data[i]);
    // }

    FILE *filePointerWrite = NULL;
    if (fileOpening(&filePointerWrite, "numericData.asm", "wb") == 1)
        return 1;

    fwrite(data, sizeof(int), dataIndex, filePointerWrite);//TODO - байтовый uint8-t

    free(data);
    free(fileToReadInfo.individualLines);
    free(fileToReadInfo.buffer);

    if (closeFile(&filePointerWrite) == 1)
        return 1;

    return 0;
}
