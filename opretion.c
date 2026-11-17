#include "search.h"
#include<string.h>
#include<ctype.h>

int validate_arg(char *argv[], int index)
{
    //File extension
    char *dot = strrchr(argv[index], '.');
    if(dot == NULL || strcmp(dot, ".txt") != 0)
    {
        printf("ERROR...Extension must be '.txt'\n");
        return FAILURE;
    }

    //File present or not
    FILE *fptr = fopen(argv[index], "r");
    if(fptr == NULL)
    {
        printf("File does not exist\n");
        return FAILURE;
    }

    //Check the content present or not
    if(fgetc(fptr) == EOF)
    {
        printf("File is empty\n");
        fclose(fptr);
        return FAILURE;
    }
    fclose(fptr);

    //Check duplicate or not
    for(int i = 1; i < index; i++)
    {
        if(strcmp(argv[index], argv[i]) == 0)
        {
            printf("ERROR... Duplicate file found\n");
            return FAILURE;
        }
    }
    return SUCCESS;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int insert_at_last(Slist **head, char *file_name)
{
    Slist *newNode = malloc(sizeof(Slist));
    if(newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return FAILURE;
    }
    
    strcpy(newNode -> fname, file_name);
    newNode -> link = NULL;
    if(*head == NULL)
    {
        *head = newNode;
        return SUCCESS;
    }
    Slist *temp = *head;
    while(temp -> link != NULL)
    {
        temp = temp -> link;
    }
    temp -> link = newNode;
    return SUCCESS;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
void print_list(Slist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
        printf("\nhead -> ");
	    while (head != NULL)		
	    {
		    printf("%s -> ", head -> fname);
		    head = head -> link;
	    }

	    printf("NULL\n\n");
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
int insert_word(char *fname, char *word, mainnode_t *arr[])
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

    if(arr[index] == NULL)
    {
        //Creating memory for subnode
        subnode_t *S_newNode = malloc(sizeof(subnode_t));
        if(S_newNode == NULL)
        {
            printf("Memory allocation for subnode is failed\n");
            return FAILURE;
        }
        strcpy(S_newNode -> filename, fname);
        S_newNode -> word_count = 1;
        S_newNode -> link = NULL;

        //Creating memory for mainnode
        mainnode_t *M_newNode = malloc(sizeof(mainnode_t));
        if(M_newNode == NULL)
        {
            printf("Memory allocation for mainnode is failed\n");
            return FAILURE;
        }
        strcpy(M_newNode -> word, word);
        M_newNode -> file_count = 1;
        M_newNode -> sublink = S_newNode;
        M_newNode -> link = NULL;

        arr[index] = M_newNode;
        return SUCCESS;
    }
            
    mainnode_t *M_temp = arr[index];
    mainnode_t *M_prev = NULL;

    while(M_temp != NULL)
    {
        if(strcmp(M_temp -> word, word) == 0)
        {
            subnode_t *S_temp = M_temp -> sublink;
            subnode_t *S_prev = NULL;
            while(S_temp != NULL)
            {
                if(strcmp(S_temp -> filename, fname) == 0)
                {
                    (S_temp -> word_count)++;
                    return SUCCESS;
                }
                S_prev = S_temp;
                S_temp = S_temp -> link;
            }
            subnode_t *S_newNode = malloc(sizeof(subnode_t));
            if(S_newNode == NULL)
            {
                printf("Memory allocation for subnode is failed\n");
                return FAILURE;
            }
            strcpy(S_newNode -> filename, fname);
            S_newNode -> word_count = 1;
            S_newNode -> link = NULL;

            S_prev -> link = S_newNode;
            (M_temp -> file_count)++;
        }
        M_prev = M_temp;
        M_temp = M_temp -> link;
    }
    //Creating memory for subnode
    subnode_t *S_newNode = malloc(sizeof(subnode_t));
    if(S_newNode == NULL)
    {
        printf("Memory allocation for subnode is failed\n");
        return FAILURE;
    }
    strcpy(S_newNode -> filename, fname);
    S_newNode -> word_count = 1;
    S_newNode -> link = NULL;

    //Creating memory for mainnode
    mainnode_t *M_newNode = malloc(sizeof(mainnode_t));
    if(M_newNode == NULL)
    {
        printf("Memory allocation for mainnode is failed\n");
        return FAILURE;
    }
    strcpy(M_newNode -> word, word);
    M_newNode -> file_count = 1;
    M_newNode -> sublink = S_newNode;
    M_newNode -> link = NULL;

    M_prev -> link = M_newNode;
    return SUCCESS;
}