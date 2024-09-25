/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:37 by fforster          #+#    #+#             */
/*   Updated: 2024/09/24 18:46:54 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_split(char **split)
// {
// 	size_t	i;

// 	i = 0;
// 	while (split[i])
// 	{
// 		free(split[i]);
// 		split[i] = NULL;
// 		i++;
// 	}
// 	free(split);
// 	split = NULL;
// }

void	free_tokens(t_token **t)
{
	t_token	*tmp;
	int count = 0;
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
