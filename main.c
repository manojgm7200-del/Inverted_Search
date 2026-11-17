#include<stdio.h>
#include"search.h"

int main(int argc, char *argv[])
{
    Slist *head = NULL;
    for(int i = 1; i < argc; i++)
    {
        if(validate_arg(argv, i) == FAILURE)
            continue;
        else
            insert_at_last(&head, argv[i]);
    }
    print_list(head);
    //printf("File is opened successfully\n");
    if(head == NULL)
    {
        return FAILURE;
    }

    int option;
    mainnode_t *arr[27] = {0};
    char word[30];
    printf("1. Create database\n2. Display database\n3. Search database\n4. Update database\n5. Save database\n6. Exit\n");
    while(1)
    {
        printf("\nEnter choice : ");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                create_database(head, arr);
                printf("Created database successfully....\n");
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
                update_database();
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