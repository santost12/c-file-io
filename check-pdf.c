/*
The first five bytes of a PDF file
always contain the following hex values:

25 50 44 46 2D
*/

#include <stdio.h>


void print_signatures(const unsigned char *pdf_signature, unsigned char *inputFile_bytes)
{
    printf("PDF signature (hex):  ");
    for (int x = 0; x < 4; x++)
    {
        printf("%X ", pdf_signature[x]);
    }

    printf("\nInput file signature (hex):  ");
    for (int x = 0; x < 4; x++)
    {
        printf("%X ", inputFile_bytes[x]);
    }
}


int check_pdf_signature(const unsigned char *pdf_signature, unsigned char *inputFile_bytes)
{
    for (int x = 0; x < 4; x++)
    {
        if (pdf_signature[x] != inputFile_bytes[x])
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
        printf("Example: is-png.exe test.png\n");
        return -1;
    }

    const char *file_name = argv[1];
    const unsigned char pdf_signature[8] = {0x25, 0x50, 0x44, 0x46, 0x2D};
    unsigned char inputFile_bytes[4];

    FILE *fp = fopen(file_name, "rb");

    if (fp == NULL) {
        printf("An error occured while trying to open: %s\n", file_name);
        return -2;
    }


    fread(inputFile_bytes, 1, 4, fp);
    fclose(fp);

    print_signatures(pdf_signature, inputFile_bytes);


    if (check_pdf_signature(pdf_signature, inputFile_bytes) == 1) {
        printf("\n\n%s has a valid PDF signature.\n", file_name);
        return 1;
    } else {
        printf("\n\n%s does not have a valid PDF signature.\n", file_name);
        return 0;
    }

    return -3;
}
