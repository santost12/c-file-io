/*
The first eight bytes of a PNG file
always contain the following (decimal) values:

137, 80, 78, 71, 13, 10, 26, 10

These decimal values in hexadecimal are:

89, 50, 4E, 47, D, A, 1A, A
*/

#include <stdio.h>


void print_signatures(const unsigned char *png_signature, unsigned char *inputFile_bytes)
{
    printf("PNG signature (hex):  ");
    for (int x = 0; x < 8; x++)
    {
        printf("%X ", png_signature[x]);
    }

    printf("\nInput file signature (hex):  ");
    for (int x = 0; x < 8; x++)
    {
        printf("%X ", inputFile_bytes[x]);
    }
}


int check_png_signature(const unsigned char *png_signature, unsigned char *inputFile_bytes)
{
    for (int x = 0; x < 8; x++)
    {
        if (png_signature[x] != inputFile_bytes[x])
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
        printf("Example: %s test.png\n", argv[0]);
        return -1;
    }

    const char *file_name = argv[1];
    const unsigned char png_signature[8] = {0x89, 0x50, 0x4E, 0x47, 0xD, 0xA, 0x1A, 0xA};
    unsigned char inputFile_bytes[8];


    FILE *fp = fopen(file_name, "rb");

    if (fp == NULL) {
        printf("An error occured while trying to open: %s\n", file_name);
        return -2;
    }


    fread(inputFile_bytes, 1, 8, fp);
    fclose(fp);

    print_signatures(png_signature, inputFile_bytes);


    if (check_png_signature(png_signature, inputFile_bytes) == 1) {
        printf("\n\n%s has a valid PNG signature.\n", file_name);
        return 1;
    } else {
        printf("\n\n%s does not have a valid PNG signature.\n", file_name);
        return 0;
    }

    return -3;
}
