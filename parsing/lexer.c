/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:31:26 by fforster          #+#    #+#             */
/*   Updated: 2024/10/08 18:17:58 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_type2(char *s)
{
	if (*s == '<')
	{
		if (*(s + 1) == '<')
			return ('e');
		else
			return ('<');
	}
	else if (*s == '>')
	{
		if (*(s + 1) == '>')
			return ('+');
		else
			return ('>');
	}
	else if (*s == '$')
		return ('$');
	else if (*s == '\'')
		return ('\'');
	else if (*s == '\"')
		return ('\"');
	else
		return (*s);
}

static char	check_type(char *s)
{
	if (*s == '\0')
		return (0);
	else if (*s == '|')
		return ('|');
	else if (*s == '(')
		return ('(');
	else if (*s == ')')
		return (')');
	else if (*s == '&')
		return ('&');
	return (check_type2(s));
}

static int	search_command(char **pstr, char *estr, char **q, char **eq)
{
	char	*str;
	char	ret;

	str = *pstr;
	while (str < estr && ft_isspace(*str))
	{
		str++;
		printf("str++\n");
	}
	if (q)
		*q = str;
	ret = *str;
	printf("3\n");
	ret = check_type(str);
	printf("ret %c\n", ret);
	while (str < estr && !ft_isspace(*str) && !ft_strchr("\'\"|()&<>$", *str))
	{
		str++;
		printf("str2++\n");
	}
	if (eq)
		*eq = str;
	while (str < estr && ft_isspace(*str))
	{
		str++;
		printf("str3++\n");
	}
	printf("4\n");
	*pstr = str;
	return (ret);
}

void	start_lexer(char *input, size_t end)
{
	t_token	*token;
	t_token	*token_top;
	size_t	i;
	char	*q;
	char	*eq;

	q = NULL;
	i = 0;
	while (input[end])
		end++;
	token = NULL;
	add_history(input);
	while (*input)
	{
		token = make_token();
		token->type = search_command(&input, &input[end], &q, &eq);
		while (!ft_isspace(q[i]))
			i++;
		token->str = ft_substr(q, 0, i - 1);
		printf("5\n");
		// token->str = (ft_strdup("DUP\n"));
		printf("%s", token->str);
		token_add_back(&token_top, token);
	}
	// print_token_data(token_top);
	token_top = NULL;
}
