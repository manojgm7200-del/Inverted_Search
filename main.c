#include <stdio.h>
#include "search.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("ERROR... No input files provided\n");
        return FAILURE;
    }
    File_t *file = NULL;
    Mainnode_t *arr[27] = {0};
    if(validate_arg(argv, &file) == FAILURE)
    {
        return FAILURE;
    }
    do_operation(&file, arr);
    return SUCCESS;
}