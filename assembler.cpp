#include "commands.h"
#include "stack.h"
#include "assembler.h"

int main(int argc, char *argv[])
{
    fileInfoStruc_t fileToReadInfo = {NULL, "data.asm", NULL, 0, NULL};

    if (readFromFile(&fileToReadInfo) == INTERPRETER_ERROR)
        return 1;

    dataStruc_t data = {};
    memset(&data.labels[0], -1, NUMBER_OF_LABELS);

    readItemsStruc_t enteredData = {};

    if ((data.data = (int *)calloc(fileToReadInfo.numberOfLines * 2, sizeof(int))) == NULL)
        return 1;

    for (int i = 0; i < 2; i++)
    {
        rewriteTextIntoNumber(&fileToReadInfo, &data, &enteredData);
        if (i == 0)
            data.dataIndex = 0;
    }

    FILE *filePointerWrite = NULL;
    if (fileOpening(&filePointerWrite, "numericData.asm", "wb") == 1)
        return 1;

    fwrite(data.data, sizeof(int), data.dataIndex, filePointerWrite);//TODO - байтовый uint8-t

    if (closeFile(&filePointerWrite) == 1)
        return 1;
// 
//     for (int i = 0; i < data.dataIndex; i++)
//     {
//         printf("%d ", data.data[i]);
//     }
//     printf("\n%d %d %d %d", data.labels[0], data.labels[1], data.labels[2], data.labels[3]);

    //TODO - сделать destroyer
    free(data.data);
    free(fileToReadInfo.individualLines);
    free(fileToReadInfo.buffer);

    return 0;
}
