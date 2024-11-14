/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:29:41 by fforster          #+#    #+#             */
/*   Updated: 2024/11/14 18:56:51 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token_data(t_token *top)
{
	t_token		*tmp;
	static int	count = 0;

	tmp = top;
	while (tmp)
	{
		printf("STRING[%d]=%s\n", count, tmp->str);
		printf("TYPE[%d]=%d\n\n", count, tmp->type);
		count++;
		tmp = tmp->next;
	}
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

void	make_token(t_token **tok, t_lexer *lexer)
{
	t_token	*node;
	t_token	*last_node;

	if (!tok)
		return ;
	node = ft_malloc(sizeof(t_token));
	if (!node)
		return ;
	ft_bzero(node, sizeof(t_token));
	node->str = get_str(lexer);
	if (node->str)
		node->len = ft_strlen(node->str);
	node->next = NULL;
	if (*tok == NULL)
	{
		*tok = node;
		node->previous = NULL;
		return ;
	}
	last_node = find_last_token(*tok);
	last_node->next = node;
	node->previous = last_node;
}

// t_token	*make_token(void)
// {
// 	t_token	*new;

// 	new = ft_malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	return (new);
// }

// void	token_add_back(t_token **last, t_token *new)
// {
// 	t_token	*tmp;

// 	// printf("\n7\n");
// 	tmp = NULL;
// 	if (!last || !new)
// 	{
// 		// printf("this bitch empty\n");	
// 		return ;
// 	}
// 	if (*last == NULL)
// 	{
// 		*last = new;
// 		// printf("\nfirsttoken\n");
// 		return ;
// 	}
// 	tmp = *last;
// 	// printf("WHY\n");
// 	tmp = find_last_token(*last);
// 	tmp->next = new;
// 	// printf("\nadded back\n");
// }
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