#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "laboratory-work-3.h"

int main(int argc, char* argv[]) 
{ 
    validate_arguments_number(argc);

    char* filename = argv[1]; 
    char* buffer = read_file(filename);
    
    char* reversed_buffer = reverse_string(buffer);
    write_file(filename, reversed_buffer);

    return 0;
}

void write_file(char* filename, char* content)
{
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fputs(content, file);
        fclose(file);
    }
}

char* read_file(char* filename)
{
    FILE* file = fopen(filename, "rb");
    validate_file_opened(file);

    long length = get_file_length(file);
    char* buffer = malloc(length);
    if (!buffer) {
        puts("could not create a buffer");
        fclose(file);
        exit(-1);
    }

    fread(buffer, 1, length, file);
    fclose(file);
    return buffer;
}

long get_file_length(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    return length;
}

void validate_file_opened(FILE* file)
{
    if (!file) {
        puts("could not open the file");
        exit(-1);
    }
}

void validate_arguments_number(int argc)
{
    if (argc < 2) {
        puts("missing argument");
        exit(-1);
    }
}

char* reverse_string(char* string_to_reverse)
{ 
    if (!string_to_reverse || !*string_to_reverse) {
        return string_to_reverse;
    }
      
    char* start_pointer = string_to_reverse;
    char* end_pointer = string_to_reverse + strlen(string_to_reverse) - 1;
 
    while (end_pointer > start_pointer) {
        *start_pointer ^= *end_pointer;
        *end_pointer ^= *start_pointer;
        *start_pointer ^= *end_pointer;
        start_pointer++;
        end_pointer--;
    }

    return string_to_reverse;
}
