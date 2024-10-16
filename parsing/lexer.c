/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:31:26 by fforster          #+#    #+#             */
/*   Updated: 2024/10/16 17:15:46 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	search_command(char **pstr, char *estr, char **q, char **eq)
// {
// 	char	*str;
// 	char	ret;

// 	str = *pstr;
// 	while (str < estr && ft_isspace(*str))
// 	{
// 		str++;
// 		printf("str++\n");
// 	}
// 	if (q)
// 		*q = str;
// 	ret = *str;
// 	printf("3\n");
// 	ret = check_type(str);
// 	printf("ret %c\n", ret);
// 	while (str < estr && !ft_isspace(*str) && !ft_strchr("\'\"|()&<>$", *str))
// 	{
// 		str++;
// 		printf("str2++\n");
// 	}
// 	if (eq)
// 		*eq = str;
// 	while (str < estr && ft_isspace(*str))
// 	{
// 		str++;
// 		printf("str3++\n");
// 	}
// 	printf("4\n");
// 	*pstr = str;
// 	return (ret);
// }

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

static void	ft_tokenizer(t_token **token)
{
	if ((*token)->str[0] == '\"')
		(*token)->type = DOUBLE_Q;
}

void	start_lexer(char *input)
{
	t_token	*token;
	t_token	*token_top;
	size_t	i;
	size_t	l;
	char	**split;

	i = 0;
	l = 0;
	token = NULL;
	token_top = NULL;
	add_history(input);
	split = new_split(input);
	while (split[i])
	{
	// printf("hey\n");
		token = make_token();
		token->str = split[i];
		printf("%s", token->str);
		ft_tokenizer(&token);
		token_add_back(&token_top, token);
		i++;
	}
	print_token_data(token_top);
	f_free_split_strs(split);
	split = NULL;
	token_top = NULL;
}
