/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:29:41 by fforster          #+#    #+#             */
/*   Updated: 2024/10/01 20:39:17 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\n')
		return (1);
	return (0);
}

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

t_token	*make_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	return (new);
}

void	token_add_back(t_token **last, t_token *new)
{
	t_token	*tmp;

	if (!*last)
	{
		(*last)->next = new;
		return ;
	}
	if (!last || !new)
		return ;
	tmp = *last;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
// void	make_token(t_token **token, char *str, int flag, int id)
// {
// 	t_token	*new;
// 	t_token	*last;

// 	if (!token)
// 		return ;
// 	// printf("make T start\n");
// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 		return ;
// 	new->str = str;
// 	new->id = id;
// 	// probably needs to be freed!!
// 	new->flag = flag;
// 	new->next2 = NULL;
// 	if (*token == NULL)
// 	{
// 		new->previous = NULL;
// 		*token = new;
// 	// printf("make T first\n");
// 		return ;
// 	}
// 	// printf("make T MORE\n");
// 	last = find_last_token(*token);
// 	last->next = new;
// 	new->previous = last;
// }

// void	assign_token_type(char *solo_split, t_token **t)
// {
// 	size_t	i = 0;
// 	size_t	l = 0;
// 	int		flag;

// 	flag = OTHER;
// 	while (solo_split[i])
// 	{
// 		if (solo_split[i] == '(')
// 			flag = O_PARANT;
// 		if (solo_split[i] == ')')
// 			flag = C_PARANT;
// 		if (solo_split[i] == '|')
// 			flag = PIPE;
// 		if (ft_isdigit(solo_split[i]))
// 			flag = NUMBER;

// 	}
// 		make_token(t, solo_split, flag, i)
// }