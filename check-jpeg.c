/*

JPEG magic number ff d8 ff

*/

#include <stdio.h>

void print_signatures(const unsigned char *jpeg_signature, unsigned char *inputFile_bytes)
{
    printf("JPEG signature (hex):  ");
    for (int x = 0; x < 3; x++)
    {
        printf("%X ", jpeg_signature[x]);
    }

    printf("\nInput file signature (hex):  ");
    for (int x = 0; x < 3; x++)
    {
        printf("%X ", inputFile_bytes[x]);
    }
}


int check_jpeg_signature(const unsigned char *jpeg_signature, unsigned char *inputFile_bytes)
{
    for (int x = 0; x < 3; x++)
    {
        if (jpeg_signature[x] != inputFile_bytes[x])
        {
            return 0;
        }
    }

    return 1;
}


int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Error: Too many or too few arguments\n");
        printf("Example: %s test.jpeg\n", argv[0]);
        return -1;
    }

    const char *file_name = argv[1];
    const unsigned char jpeg_signature[3] = {0xFF, 0xD8, 0xFF};
    unsigned char inputFile_bytes[3];


    FILE *fp = fopen(file_name, "rb");

    if (fp == NULL) {
        printf("An error occured while trying to open: %s\n", file_name);
        return -2;
    }


    fread(inputFile_bytes, 1, 3, fp);
    fclose(fp);

    print_signatures(jpeg_signature, inputFile_bytes);


    if (check_jpeg_signature(jpeg_signature, inputFile_bytes) == 1) {
        printf("\n\n%s has a valid JPEG signature.\n", file_name);
        return 1;
    } else {
        printf("\n\n%s does not have a valid JPEG signature.\n", file_name);
        return 0;
    }

    return -3;
}
