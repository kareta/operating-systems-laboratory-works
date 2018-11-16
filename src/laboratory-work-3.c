#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) 
{ 
    if (argc < 2) {
        puts("missing argument");
        exit(-1);
    }

    char* filename = argv[1]; 
    puts(filename);
    return 0;
}
