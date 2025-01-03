/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:37 by fforster          #+#    #+#             */
/*   Updated: 2024/12/12 23:27:15 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	while (++i <= len && current_bag)
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

static void	ft_free_head(t_trashman *trashmen)
{
	t_trashnode		*tofree;

	tofree = trashmen->head;
	trashmen->head = trashmen->head->next;
	free(tofree->totrash);
	tofree->totrash = NULL;
	free(tofree);
	tofree = NULL;
	trashmen->worker_num--;
}

void	ft_free(void *pointer)
{
	t_trashman		*trashmen;
	t_trashnode		*tofree;
	t_trashnode		*current_bag;

	if (!pointer)
		return ;
	trashmen = get_workers();
	current_bag = trashmen->head;
	if (trashmen->head->totrash == pointer)
		return (ft_free_head(trashmen));
	while (current_bag != trashmen->tail)
	{
		if (current_bag->next->totrash == pointer)
		{
			tofree = current_bag->next;
			current_bag->next = current_bag->next->next;
			free(tofree->totrash);
			tofree->totrash = NULL;
			free(tofree);
			tofree = NULL;
			trashmen->worker_num--;
			return ;
		}
		current_bag = current_bag->next;
	}
}
