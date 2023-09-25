#include <stdio.h>
#include <stdlib.h>


unsigned long get_file_size_bytes(char *file_name)
{
    FILE* fp = fopen(file_name, "rb");

    if (fp == NULL)
    {
        printf("An error occurred while trying to open: %s\n", file_name);
        exit(-2);
    }

    fseek(fp, 0L, SEEK_END);
    unsigned long size = ftell(fp);
    fclose(fp);

    return size;
}


void read_file_bytes(char *file_name, unsigned long file_size, char *ptr_file_bytes)
{
    FILE* fp = fopen(file_name, "rb");

    if (fp == NULL)
    {
        printf("An error occurred while trying to open: %s\n", file_name);
        exit(-2);
    }

    fread(ptr_file_bytes, 1, file_size, fp);
    fclose(fp);
}


void flip_bits(unsigned long file_size, char *ptr_file_bytes)
{
    for (unsigned long x = 0; x < file_size; x++)
    {
        ptr_file_bytes[x] = ~(ptr_file_bytes[x]);
    }
}


void write_file_bytes(char *file_name, unsigned long file_size, char *ptr_file_bytes)
{
    FILE* fp = fopen(file_name, "wb");

    if (fp == NULL)
    {
        printf("An error occurred while trying to open: %s\n", file_name);
        exit(-2);
    }

    fwrite(ptr_file_bytes, 1, file_size, fp);
    fclose(fp);
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error: Too many or too few arguments\n");
        printf("Example: flip-bits.exe test.txt\n");
        return -1;
    }

    char *file_name = argv[1];
    unsigned long file_size = get_file_size_bytes(file_name);

    char *ptr_file_bytes = malloc(file_size);

    if (ptr_file_bytes == NULL) {
        printf("An error occurred. Unable to allocate memory.\n");
        return -1;
    }

    read_file_bytes(file_name, file_size, ptr_file_bytes);

    flip_bits(file_size, ptr_file_bytes);

    write_file_bytes(file_name, file_size, ptr_file_bytes);

    free(ptr_file_bytes);
    return 0;
}
