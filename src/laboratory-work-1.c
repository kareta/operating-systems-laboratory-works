#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "laboratory-work-1.h"

#define CURRENT_DIRECTORY "./"

int main() 
{ 
    const int file_count = get_file_count(CURRENT_DIRECTORY);
    printf("%i", file_count);

    return 0;
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

    return file_count;
}
