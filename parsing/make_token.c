/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:55:00 by fforster          #+#    #+#             */
/*   Updated: 2024/11/27 20:55:22 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_token(t_token **toktop, t_lexer *lexer)
{
	t_token	*node;
	t_token	*last_node;

	if (!toktop)
		return ;
	node = ft_calloc(sizeof(t_token), 1);
	if (!node)
		return ;
	node->str = get_str(lexer, toktop);
	if (node->str)
		node->len = ft_strlen(node->str);
	node->next = NULL;
	if (*toktop == NULL)
	{
		node->id = 0;
		*toktop = node;
		node->previous = NULL;
		return ;
	}
	last_node = find_last_token(*toktop);
	last_node->next = node;
	node->previous = last_node;
	set_token_types(node);
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
