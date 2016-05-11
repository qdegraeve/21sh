#include "tree.h"

t_btree *btree_create_node(void *data)
{
	t_btree *tmp;

	tmp = (t_btree*)malloc(sizeof(t_btree));
	if (tmp)
	{
		tmp->data = data;
		tmp->left = NULL;
		tmp->right = NULL;
	}
	else
		exit(0);
	return (tmp);
}

t_infos *create_infos(char *token, int priority)
{
	t_infos *tmp;

	tmp = (t_infos*)malloc(sizeof(t_infos));
	if (tmp)
	{
		tmp->token = token;
		tmp->priority = priority;
		tmp->id = generate_unique_id();
	}
	else
		exit(0);
	return (tmp);
}

void btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root->left != NULL)
		btree_apply_infix(root->left, applyf);
	applyf(root);
	if (root->right != NULL)
		btree_apply_infix(root->right, applyf);
}
#include <stdio.h>
void print_data(void *data)
{
	t_infos *tmp;

	tmp = ((t_btree*)data)->data;
	ft_printf("\nCMDS %s -> %d\n", tmp->token, tmp->priority);
	printf("\nCMDS %s -> %d\n", tmp->token, tmp->priority);
	ft_putstr("\nCMDS ");
	ft_putstr(tmp->token);
	ft_putstr("-> ");
	ft_putnbr(tmp->priority);
	ft_putstr("\n");
}

int	generate_unique_id()
{
	static int id;

	id = 0;
	return (id += 1);
}
void btree_insert_data(t_btree **root, void *item)
{
	t_btree *tmp;
	t_infos *data;
	t_infos *data2;

	tmp = *root;
	data = tmp->data;
	data2 = item;
	if (tmp->left != NULL)
		btree_insert_data(&tmp->left, item);
	if (tmp->right != NULL)
		btree_insert_data(&tmp->right, item);
//	ft_printf(" root = %d item = %d", data->id, data2->id);
//	ft_putnbr(data->id);
//	ft_putnbr(data2->id);
	if (data->id == data2->id - 1)
	{
		ft_putstr("ici");
		return ;
	//	if (tmp->left == NULL && priority)
	//		tmp->left = btree_create_node(item);
	//	else (tmp->right == NULL)
	//	if (tmp->right == NULL)
	//		tmp->right = btree_create_node(item);
	//	else
	}
}
