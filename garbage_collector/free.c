/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:37 by fforster          #+#    #+#             */
/*   Updated: 2024/10/20 16:27:22 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_trash(void)
{
	size_t			i;
	size_t			len;
	t_trashnode		*next_bag;
	t_trashnode		*current_bag;
	t_trashman		*trashmen;

	i = 0;
	trashmen = get_workers();
	current_bag = trashmen->head;
	len = trashmen->worker_num;
	while (i <= len && current_bag)
	{
		next_bag = current_bag->next;
		free(current_bag->totrash);
		current_bag->next = NULL;
		free(current_bag);
		current_bag = NULL;
		current_bag = next_bag;
	}
	trashmen = NULL;
}

void	free_tokens(t_token **t)
{
	t_token	*tmp;
	int		count = 0;

	if (!*t)
		return ;
	printf("free start\n");
	tmp = *t;
	while (tmp->next != NULL)
	{
		printf("count %d", count);
		count++;
		tmp = tmp->next;
		free(tmp->previous);
	}
	printf("free end\n");
	free(tmp);
	*t = NULL;
}

void	f_free_split_strs(char **split)
{
	size_t	k;

	k = 0;
	printf("\n!ATTEMPTING SPLIT FREE!\n");
	while (split[k] != NULL)
	{
		free(split[k]);
		k++;
	}
	free(split);
}