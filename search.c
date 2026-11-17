#include "search.h"
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int create_database(Slist *head, mainnode_t *arr[])
{
    char word[30];
    if(head == NULL)
    {
        printf("ERROR.... Unable to open faile\n");
        return FAILURE;
    }

    Slist *temp = head;
    while(temp != NULL)
    {
        FILE *fptr = fopen(temp -> fname, "r");
        if(fptr == NULL)
        {
            printf("ERROR.... Unable to open %s file\n", temp -> fname);
            temp = temp -> link;
            continue;
        }
        while(fscanf(fptr, "%s", word) != EOF)
        {
            insert_word(temp -> fname, word, arr);
        }
        fclose(fptr);
        temp = temp -> link;
    }
    return SUCCESS;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int display_database(mainnode_t *arr[])
{
    for(int i = 0; i < 27; i++)
    {
        if(arr[i] == NULL)
        {
            continue;
        }
        mainnode_t *M_temp = arr[i];
        while(M_temp != NULL)
        {
            printf("%-5d\t%-5s\t%-5d\t", i, M_temp -> word, M_temp -> file_count);
            subnode_t *S_temp = M_temp -> sublink;
            while(S_temp != NULL)
            {
                printf("%-5s\t%-5d\t", S_temp -> filename, S_temp -> word_count);
                S_temp = S_temp -> link;
            }
            printf("\n");
            M_temp = M_temp -> link;  
        }
    }
    return SUCCESS;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int search_database(char *word, mainnode_t *arr[])
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

    mainnode_t *M_temp = arr[index];
    while(M_temp != NULL)
    {
        if(strcmp(M_temp -> word, word) == 0)
        {
            printf("\nWord %s is present in %d files\n", word, M_temp -> file_count);
            subnode_t *S_temp = M_temp -> sublink;
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
int update_database()
{
    return SUCCESS;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int save_database(mainnode_t *arr[])
{
    FILE *fptr = fopen("save.csv","w+");
    if(fptr == NULL)
    {
        printf("ERROR... Unable to open save.csv\n");
        return FAILURE;
    }

    for(int i = 0; i < 27; i++)
    {
        if(arr[i] == NULL)
        {
            continue;
        }
        mainnode_t *M_temp = arr[i];
        while(M_temp != NULL)
        {
            fprintf(fptr,"#%d;%s;%d;", i, M_temp -> word, M_temp -> file_count);
            subnode_t *S_temp = M_temp -> sublink;
            while(S_temp != NULL)
            {
                fprintf(fptr, "%s;%d;", S_temp -> filename, S_temp -> word_count);
                S_temp = S_temp -> link;
            }
            fprintf(fptr, "#\n");
            M_temp = M_temp -> link;  
        }
    }
    printf("Database saved successfully....\n");
    return SUCCESS;
}