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
}File_t;

typedef struct s_node
{
	char filename[30];
	int word_count;
	struct s_node *link;
}Subnode_t;

typedef struct m_node
{
	char word[30];
	int file_count;
	Subnode_t *sublink;
	struct m_node *link;
}Mainnode_t;

int duplicate_file(char *argv, File_t *file);
int validate_arg(char *argv[], File_t **file);
int insert_at_last(File_t **file, char *filename);
int display_file(File_t *file);
int insert_word(char *fname, char *word, Mainnode_t *arr[]);
int valid_backupfile(char *filename);
int remove_duplicate_file(File_t **file, char *fname);

int create_database(File_t *head, Mainnode_t *arr[]);
int display_database(Mainnode_t *arr[]);
int search_database(char *word, Mainnode_t *arr[]);
int update_database(File_t *head, Mainnode_t *arr[]);
int save_database(Mainnode_t *arr[]);

#endif