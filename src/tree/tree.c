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

void print_data(void *data)
{
	t_infos *tmp;

	tmp = ((t_btree*)data)->data;
//	ft_printf("\nCMDS %s -> %d\n", tmp->token, tmp->priority); Quentin WTF ??
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
	return (++id);
}
void btree_insert_data(t_btree **root, void *item)
{
	t_btree *tmp;
	t_infos *data;
	t_infos *data2;

	tmp = *root;
	data = tmp->data;
	data2 = ((t_infos*)item);
	if (data->id < data2->id)
	{
		if (tmp->left == NULL)
			tmp->left = btree_create_node(item);
		else
			btree_insert_data(&tmp->left, item);
	}
	else
	{
		if (tmp->right == NULL)
			tmp->right = btree_create_node(item);
		else
			btree_insert_data(&tmp->right, item);
	}
}
