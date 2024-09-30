/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:29:41 by fforster          #+#    #+#             */
/*   Updated: 2024/09/30 18:34:27 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_last_token(t_token *t)
{
	t_token	*tmp;

	if (!t)
		return (NULL);
	tmp = t;
	while (tmp->next != 0)
		tmp = tmp->next;
	return (tmp);
}

void	make_token(t_token **token, char *str, int flag, int id)
{
	t_token	*new;
	t_token	*last;

	if (!token)
		return ;
	// printf("make T start\n");
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->str = str;
	new->id = id;
	// probably needs to be freed!!
	new->flag = flag;
	new->next2 = NULL;
	if (*token == NULL)
	{
		new->previous = NULL;
		*token = new;
	// printf("make T first\n");
		return ;
	}
	// printf("make T MORE\n");
	last = find_last_token(*token);
	last->next = new;
	new->previous = last;
}
