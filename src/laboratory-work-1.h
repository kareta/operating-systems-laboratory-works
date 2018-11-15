#ifndef HEADER_FILE
#define HEADER_FILE

#include <dirent.h>

struct dirent* get_directory_content(const char* directory_path);

int get_file_count(const char* directory_path);

#endif


