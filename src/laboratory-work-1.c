#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "laboratory-work-1.h"

#define CURRENT_DIRECTORY "./"

int main() 
{ 
    const int file_count = get_file_count(CURRENT_DIRECTORY);
    struct dirent* directory_entries = get_directory_content(CURRENT_DIRECTORY);
    for (int i = 0; i < file_count; i++) {
        puts(directory_entries[i].d_name);   
    }

    return 0;
}

struct dirent* get_directory_content(const char* directory_path)
{
    DIR *directory = opendir(directory_path);
    if (directory == NULL) {
        perror("Couldn't open the directory");
        return NULL;
    }

    const int dirent_size = sizeof(struct dirent);
    const int file_count = get_file_count(directory_path);
    const int directory_entries_size = dirent_size * file_count;

    struct dirent* directory_entries = malloc(directory_entries_size);
    for (int i = 0; i < file_count; i++) {
        directory_entries[i] = *readdir(directory);
    }
    
    closedir(directory);

    return directory_entries;
}

int get_file_count(const char* directory_path) 
{
    DIR *directory = opendir(directory_path);
    if (directory == NULL) {
        perror("Couldn't open the directory");
        return -1;
    } 
    
    int file_count = 0;
    while (readdir(directory)) {
        file_count++;   
    }

    closedir(directory);

    return file_count;
}
