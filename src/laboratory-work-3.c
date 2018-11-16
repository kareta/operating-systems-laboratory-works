#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverse_string(char* str);

void validate_arguments_number();

void validate_file_opened(FILE* file);

long get_file_length(FILE* file);

int main(int argc, char* argv[]) 
{ 
    validate_arguments_number(argc);

    const char* filename = argv[1]; 
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
    
    char* reversed_buffer = reverse_string(buffer);
    puts(reversed_buffer);

    return 0;
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
