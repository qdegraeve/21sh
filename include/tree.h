#ifndef TREE_H
#define TREE_H

#include "shell.h"

typedef struct s_infos
{
	char *token;
	char priority;
}				t_infos;

typedef struct s_btree
{
	void			*data;
	struct s_btree *left;
	struct s_btree *right;
}				t_btree;

/*
** Tools
*/
t_btree *btree_create_node(void *data);
void btree_apply_infix(t_btree *root, void (*applyf)(void *));
t_infos *create_infos(char *token, char priority);
void print_data(void *data);
void btree_insert_data(t_btree **root, void *item);

/*
** LEXER
*/
char	get_io(char *str);
t_btree *lexer(char *str);
#endif
