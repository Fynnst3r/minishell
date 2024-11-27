/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:41:49 by fforster          #+#    #+#             */
/*   Updated: 2024/11/27 21:07:39 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// scans input str using lex position,
// stops when there is a space and skips them when there is a quote
// The return is an allocated string with ft_malloc
char	*get_str(t_lexer *lex, t_token **toktop)
{
	char	*ret;
	size_t	l;

	l = lex->position;
	ret = NULL;
	while (lex->str[l])
	{
		lex->curr_c = lex->str[l];
		if (lex->str[l] == '\'' || lex->str[l] == '\"')
			skip_quote(lex->str, &l, toktop);
		lex->last_c = lex->str[l];
		l++;
		if (is_special_char(lex->str[l]) || ft_isspace(lex->str[l]))
			break ;
	}
	if (!ret && l != lex->position)
		ret = ft_substr(lex->str, lex->position, l - lex->position);
	while (ft_isspace(lex->str[l]))
		l++;
	lex->position = l;
	return (ret);
}

// lexer who scans string and calls functions when it finds a token to make it
t_ast	*start_lexer(char *input)
{
	t_token	*token_top;
	t_lexer	lexer;
	t_ast	*ast;
	bool	skip;

	token_top = NULL;
	add_history(input);
	lexer = init_lex(input);
	skip = false;
	ast = NULL;
	while (input[lexer.position])
	{
		while (is_special_char(input[lexer.position]))
		{
			skip = true;
			if (handle_special(input, &lexer, &token_top, lexer.position))
				ft_error("TOO MANY << OR >>", 1, &token_top);
		}
		while (ft_isspace(input[lexer.position]))
			lexer.position++;
		if (!skip)
			make_token(&token_top, &lexer);
		skip = false;
	}
	set_token_id(token_top);
	expand_tokens(&token_top); //$? is not handled yet.
	print_token_data(token_top);
	ast = make_ast(&token_top);
	ft_error("test test", 0, &token_top);
	// token_top = NULL; //put at end of token use (and free them)
	return (ast);
}
	// start makin ast nodes "s_node"
	// scan for pipes
	// assign type and scan for args and redirs
	// ?check syntax?