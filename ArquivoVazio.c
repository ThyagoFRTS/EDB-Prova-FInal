#include<stdio.h>
#include<stdlib.h>
#include"structs.h"
#include<string.h>


int get_size(const char* file_name)
{
    FILE *file = fopen(file_name, "r");

    if(file == NULL){
        return 0;
    }
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}
