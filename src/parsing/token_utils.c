/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:29:41 by fforster          #+#    #+#             */
/*   Updated: 2024/09/25 17:35:57 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	make_token(t_token **token)
{
	t_token	*new;
	t_token	*last;

	if (!token)
		return ;
	// printf("make T start\n");
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->str = NULL;
	new->flag = 0;
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
