/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:41:49 by fforster          #+#    #+#             */
/*   Updated: 2024/12/03 23:01:09 by fforster         ###   ########.fr       */
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
void	start_lexer(char *input, t_data *data)
{
	t_token	*token_top;
	t_lexer	lexer;
	bool	skip;

	token_top = NULL;
	add_history(input);
	lexer = init_lex(input);
	skip = false;
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
	expand_tokens(&token_top, data->exit_status);
	set_token_id(token_top);
	// print_token_data(token_top);
	if (evaluator(token_top))
		ft_error("Failed", 1, &token_top);
	make_ast2(data, &token_top);
	// if (data->st_node->type == EXECUTE)
		// print_exec((t_exec *)data->st_node);
	// ft_error("test test", 0, &token_top);
	// token_top = NULL; //put at end of token use (and free them)
}
	// start makin ast nodes "s_node"
	// scan for pipes
	// assign type and scan for args and redirs
	// ?check syntax?