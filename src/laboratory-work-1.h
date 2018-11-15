#ifndef HEADER_FILE
#define HEADER_FILE

#include <dirent.h>

struct dirent* get_directory_content(const char* directory_path);

int get_file_count(const char* directory_path);

int compare_files(const void* first_file, const void* second_file);

int get_file_creation_time(const char* file_name);

int is_directory(const char *file_name);

#endif


