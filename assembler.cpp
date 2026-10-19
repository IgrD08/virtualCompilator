#include "commands.h"
#include "stack.h"
#include "assembler.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Insufficient files\n");

        return 1;
    }

    fileInfoStruc_t fileToReadInfo = {NULL, argv[1], NULL, 0, NULL};

    if (readFromFile(&fileToReadInfo) != INTERPRETER_CORRECT)
        return 1;

    dataStruc_t data = {};
    memset(&data.labels[0], -1, NUMBER_OF_LABELS);

    readItemsStruc_t enteredData = {};

    if ((data.data = (int *)calloc((size_t)fileToReadInfo.numberOfLines * 2, sizeof(int))) == NULL)
        return 1;

    for (int i = 0; i < 2; i++)
    {
        rewriteTextIntoNumber(&fileToReadInfo, &data, &enteredData);

        if (i == 0)
            data.dataIndex = 0;
    }

    if (writeToFile(&data, argv[2]) != INTERPRETER_CORRECT)
        return 1;

    // for (int i = 0; i < data.dataIndex; i++)
    // {
    //     printf("%d ", data.data[i]);
    // }
    // printf("\n%d %d %d %d\n", data.labels[0], data.labels[1], data.labels[2], data.labels[3]);

    assemblerDestroyer(&fileToReadInfo, &data);

    return 0;
}
