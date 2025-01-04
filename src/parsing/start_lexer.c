/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:41:49 by fforster          #+#    #+#             */
/*   Updated: 2025/01/04 18:18:29 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	empty_tokens(t_token *t)
{
	size_t	count;

	count = 0;
	while (t)
	{
		if (t->type != T_SKIP)
			count++;
		t = t->next;
	}
	if (count == 0)
		return (1);
	return (0);
}

// scans input str using lex position,
// stops when there is a space and skips them when there is a quote
// The return is an allocated string with ft_malloc
int	get_str(t_lexer *lex, t_token **tofill)
{
	char	*ret;
	size_t	l;

	l = lex->position;
	ret = NULL;
	while (lex->str[l])
	{
		if (lex->str[l] == '\'' || lex->str[l] == '\"')
			if (skip_quote(lex->str, &l))
				return (1);
		l++;
		if (is_special_char(lex->str[l]) || ft_isspace(lex->str[l]))
			break ;
	}
	if (!ret && l != lex->position)
		ret = ft_substr(lex->str, lex->position, l - lex->position);
	while (ft_isspace(lex->str[l]))
		l++;
	lex->position = l;
	(*tofill)->str = ret;
	return (0);
}

// lexer who scans string and calls functions when it finds a token to make it
int	start_lexer(char *input, t_data *data)
{
	t_token	*token_top;
	t_lexer	lexer;
	bool	skip;

	token_top = data->token_top;
	add_history(input);
	lexer = init_lex(input);
	skip = false;
	while (input[lexer.position])
	{
		while (is_special_char(input[lexer.position]))
		{
			skip = true;
			if (handle_special(input, &lexer, &token_top, lexer.position))
				return (printf("YM_FF_SHELL: too many `<' or `>'.\n"),
					free_tokens(&token_top), data->e_status = 2, 1);
		}
		while (ft_isspace(input[lexer.position]))
			lexer.position++;
		if (!skip && input[lexer.position] != 0)
			if (make_token(&token_top, &lexer, data))
				return (ft_clean(NULL, data, &token_top), 1);
		skip = false;
	}
	return (start_parser(data, token_top));
}

int	start_parser(t_data *data, t_token *token_top)
{
	t_lexer	lexer;

	lexer = init_lex(NULL);
	expand_tokens(&token_top, lexer, data);
	if (evaluator(token_top))
		return (data->e_status = 2, ft_clean(NULL, data, &token_top), 1);
	if (empty_tokens(token_top))
		return (ft_clean(NULL, data, &token_top), 1);
	set_token_id(token_top);
	make_ast2(data, &token_top);
	if (data->st_node == NULL)
		return (ft_clean(NULL, data, &token_top), 1);
	// if (data->st_node->type == EXECUTE)
		// print_exec((t_exec *)data->st_node);
	// free_tokens(&token_top);
	return (0);
}

// set_token_id(token_top);
// 	// print_token_data(token_top);

// if (data->st_node == NULL)
// 		return (ft_error(NULL, 0, &token_top), 1);
// 	// if (data->st_node->type == EXECUTE)
// 		// print_exec((t_exec *)data->st_node);
// 	// free_tokens(&token_top);
