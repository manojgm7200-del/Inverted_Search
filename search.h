#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
	char fname[30];
	struct node *link;
}Slist;

typedef struct s_node
{
	char filename[30];
	int word_count;
	struct s_node *link;
}subnode_t;

typedef struct m_node
{
	char word[30];
	int file_count;
	subnode_t *sublink;
	struct m_node *link;
}mainnode_t;

int validate_arg(char *argv[], int index);
void print_list(Slist *head);
int insert_at_last(Slist **head, char *filename);
int insert_word(char *fname, char *word, mainnode_t *arr[]);

int create_database(Slist *head, mainnode_t *arr[]);
int display_database(mainnode_t *arr[]);
int search_database(char *word, mainnode_t *arr[]);
int update_database();
int save_database(mainnode_t *arr[]);

#endif