/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:37:15 by fforster          #+#    #+#             */
/*   Updated: 2025/01/01 21:48:43 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lexer	init_lex(char *input)
{
	t_lexer	lex;

	lex.str = input;
	lex.position = 0;
	lex.read = 0;
	lex.ignore_quotes = false;
	lex.keepempty = false;
	return (lex);
}

// special chars are '|' '>' '<' returns 1 if so
int	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\n')
		return (1);
	return (0);
}

int	skip_quote(const char *s, size_t *i)
{
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] != '\'' && s[*i])
			(*i)++;

		if (s[*i] == 0)
			return (printf("One \' too much!\n"), 1);
		return (0);
	}
	if (s[*i] == '\"')
	{
		(*i)++;
		while (s[*i] != '\"' && s[*i])
			(*i)++;
		if (s[*i] == 0)
		{
			return (printf("One \" too much!\n"), 1);
		}
		return (0);
	}
	return (0);
}

// makes extra token for special char 
// and sets lex position to next unspecial char
int	handle_special(char *input, t_lexer *lex, t_token **toktop, size_t start)
{
	if (input[lex->position] == '|')
		return (make_special_token(toktop, "|", T_PIPE), lex->position += 1, 0);
	if (input[lex->position] == '>')
	{
		lex->position++;
		while (input[lex->position] == '>' && input[lex->position])
			lex->position++;
		if (lex->position == start + 1)
			return (make_special_token(toktop, ">", T_OUT), 0);
		else if (lex->position == start + 2)
			return (make_special_token(toktop, ">>", T_APP), 0);
	}
	if (input[lex->position] == '<')
	{
		lex->position++;
		while (input[lex->position] == '<' && input[lex->position])
			lex->position++;
		if (lex->position == start + 1)
			return (make_special_token(toktop, "<", T_IN), 0);
		else if (lex->position == start + 2)
			return (make_special_token(toktop, "<<", T_HERE), 0);
	}
	return (1);
}
