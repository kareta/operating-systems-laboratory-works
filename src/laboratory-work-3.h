#ifndef LABORATORY_WORK_3_H
#define LABORATORY_WORK_3_H

char* reverse_string(char* str);

void validate_arguments_number();

void validate_file_opened(FILE* file);

long get_file_length(FILE* file);

char* read_file(char* filename);

void write_file(char* filename, char* content);

#endif


