/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:11:54 by fforster          #+#    #+#             */
/*   Updated: 2024/11/21 20:43:37 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_lexer	init_lexs(char *input)
{
	t_lexer	lex;

	lex.str = input;
	lex.position = 0;
	lex.read = 0;
	lex.last_c = 0;
	lex.curr_c = 0;
	return (lex);
}

char	*get_expanded(char *s, int type)
{
	if (type == WORD || PATH)
		expand
}

char	*expand_str(t_token **toktop)
{
	t_token	*tmp;

	tmp = *toktop;
	while (tmp)
	{
		if (tmp->type == SINGLE_Q || DOUBLE_Q || WORD || PATH)
			tmp->str = get_expanded(tmp->str, tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

// go through string until $
// then continue scanning until its ' ' or \0 or $,
// take that scan and put it in getenv
// insert getenv str into $position, not losing what is behind it
// continue looking for the end or more $ i.e. repeat loop

// if a path has something like hey'$USER'wassup, it ends up like this  hey'$USER'wassup...
// WORD can also have a string with quotes!!!!!!!!!!!! which is why the DOUBLE_Q and S_Q types are useless
// "hi"'$USER'"come here" = argc + 1 but $USER will be handled individually since its not in the "" part...

int main()
{
	char	*test = ft_strdup("\'$USER\'");
	
	printf("test %s\n",  expand_quote(test, DOUBLE_Q));
}