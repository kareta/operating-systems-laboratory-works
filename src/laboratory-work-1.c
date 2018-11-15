#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include "laboratory-work-1.h"

#define CURRENT_DIRECTORY "./"

int main() 
{ 
    const int file_count = get_file_count(CURRENT_DIRECTORY);
    struct dirent* directory_entries = get_directory_content(CURRENT_DIRECTORY);
    int dirent_size = sizeof(struct dirent);
    qsort(directory_entries, file_count, dirent_size, &compare_files);
    struct stat file_stat;
    for (int i = 0; i < file_count; i++) {
        const char* file_name = directory_entries[i].d_name;
        if (is_directory(file_name)) {
            printf("d ");
        } else {
            printf("f ");
        }
        int file_creation_time = get_file_creation_time(file_name);
        printf("%d %s\n", file_creation_time, file_name);   
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

int get_file_creation_time(const char* file_name)
{
    struct stat file_stat;
    stat(file_name, &file_stat);
    return file_stat.st_ctime;   
}

int is_directory(const char *file_name) 
{
   struct stat file_stat;
   stat(file_name, &file_stat);
   return S_ISDIR(file_stat.st_mode);
}

int compare_files(const void* first_file, const void* second_file)
{
    const char* first_file_name = ((struct dirent*) first_file)->d_name;
    const char* second_file_name = ((struct dirent*) second_file)->d_name;

    int first_file_creation_time = get_file_creation_time(first_file_name);
    int second_file_creation_time = get_file_creation_time(second_file_name);
    
    if (is_directory(first_file_name) && !is_directory(second_file_name)) {
        return 1;
    }

    if (!is_directory(first_file_name) && is_directory(second_file_name)) {
        return -1;
    }

    return second_file_creation_time - first_file_creation_time;
}
