#include "search.h"
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int do_operation(File_t **file, Mainnode_t *arr[])
{
    int option;
    char word[30];
    int create_flag = 0, update_flag = 0;
    
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
                    create_database(*file, arr);
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
                    if(create_flag == 1)
                    {
                        printf("Database is not possible to update after create database\n");
                    }
                    else
                    {
                        update_database(file, arr);
                        update_flag = 1;
                    }
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
                return SUCCESS;
                break;
            default:
                printf("Invalid choice....\n");   
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int create_database(File_t *file, Mainnode_t *arr[])
{
    char word[30];
    if(file == NULL)
    {
        printf("ERROR... Unable to create database\n");
        return FAILURE;
    }

    File_t *temp = file;
    while(temp != NULL)
    {
        FILE *fptr = fopen(temp -> fname, "r");
        if(fptr == NULL)
        {
            printf("ERROR... Unable to open %s file\n", temp -> fname);
            temp = temp -> link;
            continue;
        }
        while(fscanf(fptr, "%s", word) == 1)
        {
            if(insert_word(temp -> fname, word, arr) == FAILURE)
            {
                fclose(fptr);
                return FAILURE;
            }
        }
        fclose(fptr);
        temp = temp -> link;
    }
    printf("Database created successfully....\n");
    return SUCCESS;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int display_database(Mainnode_t *arr[])
{
    int check = 0;
    for(int i = 0; i < 27; i++)
    {
        if(arr[i] == NULL)
        {
            continue;
        }
        check = 1;
        Mainnode_t *M_temp = arr[i];
        while(M_temp != NULL)
        {
            printf("%-5d\t%-5s\t%-5d\t", i, M_temp -> word, M_temp -> file_count);
            Subnode_t *S_temp = M_temp -> sublink;
            while(S_temp != NULL)
            {
                printf("%-5s\t%-5d\t", S_temp -> filename, S_temp -> word_count);
                S_temp = S_temp -> link;
            }
            printf("\n");
            M_temp = M_temp -> link;  
        }
    }
    if(check == 0)
    {
        printf("No database found to display\n");
        return FAILURE;
    }
    return SUCCESS;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int search_database(char *word, Mainnode_t *arr[])
{
    int index;
    if(islower(word[0]))
    {
        index = word[0] - 'a';
    }
    else if(isupper(word[0]))
    {
        index = word[0] - 'A';
    }
    else
    {
        index = 26;
    }

    Mainnode_t *M_temp = arr[index];
    while(M_temp != NULL)
    {
        if(strcmp(M_temp -> word, word) == 0)
        {
            printf("\nWord %s is present in %d files\n", word, M_temp -> file_count);
            Subnode_t *S_temp = M_temp -> sublink;
            while(S_temp != NULL)
            {
                printf("In %s = %d times\n", S_temp -> filename, S_temp -> word_count);
                S_temp = S_temp -> link;
            }
            return SUCCESS;
        }
        M_temp = M_temp -> link;  
    }
    printf("Word %s is not found...\n", word);
    return FAILURE;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int update_database(File_t **file, Mainnode_t *arr[])
{
    char fname[30], word[30];
    int index, file_count, word_count;
    
    printf("Enter the backup file: ");
    scanf("%s", fname);

    if(valid_backupfile(fname) == FAILURE)
    {
        printf("Invalid backup file...Please enter the valid backup file name\n");
        return FAILURE;
    }

    FILE *fptr = fopen(fname, "r");
    if(fptr == NULL)
    {
        return FAILURE;
    }

    while(fscanf(fptr, " #%d;%[^;];%d;", &index, word, &file_count) == 3)
    {
        Mainnode_t *M_newNode = malloc(sizeof(Mainnode_t));
        if(M_newNode == NULL)
        {
            fclose(fptr);
            return FAILURE;
        }

        strcpy(M_newNode -> word, word);
        M_newNode -> file_count = file_count;
        M_newNode -> sublink = NULL;
        M_newNode -> link = NULL;

        if(arr[index] == NULL)
        {
            arr[index] = M_newNode;
        }
        else
        {
            Mainnode_t *M_temp = arr[index];
            while(M_temp -> link != NULL)
            {
                M_temp = M_temp -> link;
            }
            M_temp -> link = M_newNode;
        }

        for(int i = 0; i < file_count; i++)
        {
            if(fscanf(fptr, "%[^;];%d;", fname, &word_count) != 2)
            {
                fclose(fptr);
                return FAILURE;
            }
            remove_duplicate_file(file, fname);
            Subnode_t *S_newNode = malloc(sizeof(Subnode_t));
            if(S_newNode == NULL)
            {
                fclose(fptr);
                return FAILURE;
            } 

            strcpy(S_newNode -> filename, fname);
            S_newNode -> word_count = word_count;
            S_newNode -> link = NULL;

            if(M_newNode -> sublink == NULL)
            {
                M_newNode -> sublink = S_newNode;
            }
            else
            {
                Subnode_t *S_temp = M_newNode -> sublink;
                while(S_temp -> link != NULL)
                {
                    S_temp = S_temp -> link;
                }
                S_temp -> link = S_newNode;
            }
        }
        fscanf(fptr, "#");
    }
    fclose(fptr);
    printf("Database updated successfully....\n");
    return SUCCESS;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int save_database(Mainnode_t *arr[])
{
    int check = 0;
    char fname[30];
    printf("Enter the backup file name to save the database : ");
    scanf("%s", fname);

    char *dot = strrchr(fname, '.');
    if(dot == NULL || strcmp(dot, ".txt") != 0)
    {
        printf("ERROR... File extension must be '.txt'\n");
        return FAILURE;
    }
    FILE *fptr = fopen(fname, "w+");
    if(fptr == NULL)
    {
        printf("ERROR... Unable to open %s file\n", fname);
        return FAILURE;
    }

    for(int i = 0; i < 27; i++)
    {
        if(arr[i] == NULL)
        {
            continue;
        }
        check = 1;
        Mainnode_t *M_temp = arr[i];
        while(M_temp != NULL)
        {
            fprintf(fptr,"#%d;%s;%d;", i, M_temp -> word, M_temp -> file_count);
            Subnode_t *S_temp = M_temp -> sublink;
            while(S_temp != NULL)
            {
                fprintf(fptr, "%s;%d;", S_temp -> filename, S_temp -> word_count);
                S_temp = S_temp -> link;
            }
            fprintf(fptr, "#\n");
            M_temp = M_temp -> link;  
        }
    }
    if(check == 0)
    {
        fclose(fptr);
        printf("No database found to save\n");
        return FAILURE;
    }
    fclose(fptr);
    printf("Database saved successfully....\n");
    return SUCCESS;
}