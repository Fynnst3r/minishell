/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:55:00 by fforster          #+#    #+#             */
/*   Updated: 2025/01/03 13:59:41 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	make_token(t_token **toktop, t_lexer *lexer, t_data *data)
{
	t_token	*node;
	t_token	*last_node;

	if (!toktop)
		return (1);
	node = ft_calloc(sizeof(t_token), 1);
	if (!node)
		return (1);
	if (get_str(lexer, &node))
		return (data->e_status = 2, 1);
	if (node->str)
		node->len = ft_strlen(node->str);
	node->next = NULL;
	if (*toktop == NULL)
	{
		node->id = 0;
		*toktop = node;
		node->previous = NULL;
		return (0);
	}
	last_node = find_last_token(*toktop);
	last_node->next = node;
	node->previous = last_node;
	set_token_types(node);
	return (0);
}

void	make_special_token(t_token **toktop, char *str, int e_flag)
{
	t_token	*node;
	t_token	*last_node;

	if (!toktop)
		return ;
	node = ft_calloc(sizeof(t_token), 1);
	if (!node)
		return ;
	ft_bzero(node, sizeof(t_token));
	node->str = ft_strdup(str);
	node->type = e_flag;
	if (node->str)
		node->len = ft_strlen(node->str);
	node->next = NULL;
	if (*toktop == NULL)
	{
		*toktop = node;
		node->previous = NULL;
		return ;
	}
	last_node = find_last_token(*toktop);
	last_node->next = node;
	node->previous = last_node;
}
