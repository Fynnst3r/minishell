/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:29:41 by fforster          #+#    #+#             */
/*   Updated: 2024/12/03 22:56:50 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token_data(t_token *top)
{
	t_token		*tmp;
	int			count;

	count = 0;
	tmp = top;
	printf(ANSI_ITALIC"*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n"ANSI_RESET);
	while (tmp)
	{
		if (tmp->previous)
			printf("PREVSTR[%d]=			%s	TYPE[%d]=%d\n", count, tmp->previous->str, count - 1, tmp->previous->type);
		printf(ANSI_BOLD ANSI_GREEN"STRING[%d]=	%s\n"ANSI_RESET, count, tmp->str);
		if (tmp->next)
			printf("NEXTSTRING[%d]=			%s	TYPE[%d]=%d\n", count, tmp->next->str, count + 1, tmp->next->type);
		printf(ANSI_YELLOW"LEN[%d]=%zu\n"ANSI_RESET, count, tmp->len);
		printf(ANSI_RED"TYPE[%d]=%d\n"ANSI_RESET, count, tmp->type);
		printf(ANSI_BLUE"ID	[%d]=%i\n\n"ANSI_RESET, count, tmp->id);
		count++;
	printf(ANSI_ITALIC"-----------END OF TOK [%d]---------------------\n\n"ANSI_RESET, count);
		tmp = tmp->next;
	}
	printf(ANSI_ITALIC"*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n"ANSI_RESET);
}

void	remove_token(t_token *to_del)
{
	if (to_del->previous != NULL)
		to_del->previous->next = to_del->next;
	if (to_del->next != NULL)
		to_del->next->previous = to_del->previous;
	if (to_del->str)
		ft_free(to_del->str);
	to_del->str = NULL;
	ft_free(to_del);
	to_del = NULL;
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

t_token	*find_id(t_token *t, int find)
{
	t_token	*tmp;

	if (!t)
		return (NULL);
	tmp = t;
	while (tmp && find != tmp->id)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	set_token_id(t_token *t)
{
	t_token	*tmp;
	int		id;

	if (!t)
		return ;
	tmp = t;
	id = 0;
	while (tmp)
	{
		id++;
		tmp->id = id;
		tmp = tmp->next;
	}
}

// sets all non redirection types to word type.
// PATH has been set in handle_special and make_special_token
void	set_token_types(t_token *t)
{
	if (!t)
		return ;
	if (t->str)
		t->type = WORD;
	if (t->previous)
	{
		if (t->previous->type == T_OUT || t->previous->type == T_IN
			|| t->previous->type == T_APP || t->previous->type == T_HERE)
		{
			t->type = PATH;
		}
	}
}
				// printf("curr str = %s\nprev str = %s\nprev type %i\n\n", t->str, t->previous->str, t->previous->type);

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