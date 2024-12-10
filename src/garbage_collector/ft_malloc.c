/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:50:45 by fforster          #+#    #+#             */
/*   Updated: 2024/12/09 20:13:33 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_trashnode	*create_trash_node(void *pointer)
{
	t_trashnode	*newnode;

	newnode = malloc(sizeof(t_trashnode));
	if (!newnode)
		return (NULL);
	newnode->totrash = pointer;
	return (newnode);
}

void	add_trash_top(void *pointer)
{
	t_trashnode	*new;
	t_trashman	*trashman;

	if (!pointer)
		return ;
	trashman = get_workers();
	new = create_trash_node(pointer);
	if (!new)
		ft_error("Malloc FAIL!", 42, NULL);
	if (trashman->head == NULL)
	{
		new->next = NULL;
		trashman->head = new;
		trashman->tail = new;
	}
	else
	{
		new->next = (trashman->head);
		trashman->head = new;
	}
	trashman->worker_num++;
}

void	*ft_malloc(size_t size)
{
	void	*pointer;

	pointer = malloc(size);
	if (!pointer)
		return (NULL);
	add_trash_top(pointer);
	return (pointer);
}
