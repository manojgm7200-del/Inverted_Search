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
    if(validate_arg(argv, &file) == FAILURE)
    {
        return FAILURE;
    }

    int option;
    Mainnode_t *arr[27] = {0};
    char word[30];
    int create_flag = 0, update_flag = 0;
    //printf("1. Create database\n2. Display database\n3. Search database\n4. Update database\n5. Save database\n6. Exit\n");
    while(1)
    {
        printf("\n1. Create database\n2. Display database\n3. Search database\n4. Update database\n5. Save database\n6. Exit\n");
        printf("\nEnter choice : ");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                if(create_flag == 0)
                {
                    create_database(file, arr);
                    create_flag = 1;
                }
                else
                {
                    printf("ERROR.... Database is already created\n");
                }
                break;
            case 2:
                display_database(arr);
                break;
            case 3:
                printf("Enter word you want to search : ");
                scanf("%s", word);
                search_database(word, arr);
                break;
            case 4:
                if(update_flag == 0)
                {
                    update_database(file, arr);
                    update_flag = 1;
                }
                else
                {
                    printf("ERROR.... Database is already updated\n");
                }
                break;
            case 5:
                save_database(arr);
                break;
            case 6:
                printf("Exiting....\n");
                return FAILURE;
                break;
            default:
                printf("Invalid choice....\n");   
        }
    }
}