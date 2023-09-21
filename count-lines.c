#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error: Too many or too few arguments\n");
        printf("Example: count-lines.exe my-file.txt\n");
        return -1;
    }


    const char *file_name = argv[1];
    unsigned int line_counter = 0;


    FILE *fp = fopen(file_name, "r");

    if (!fp)
    {
        printf("An error occured while trying to open: %s\n", file_name);
        return -2;
    }


    while (!feof(fp))
    {
        char byte = fgetc(fp);

        if (byte == '\n')
        {
            line_counter++;
        }
    }

    fclose(fp);

    printf("%s contains %d line(s).\n", file_name, line_counter);
    return 0;
}
