/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:37:15 by fforster          #+#    #+#             */
/*   Updated: 2024/11/21 18:46:07 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

bool	isemptystring(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	skip_quote(const char *s, size_t *i)
{
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] != '\'' && s[*i])
			(*i)++;

		if (s[*i] == 0)
		{
			printf("FALSCH!!!!!!!!!!!!!!one \' too much man!!!!!!!!!!!!\n");
			exit(1);
		}
		return ;
	}
	if (s[*i] == '\"')
	{
		(*i)++;
		while (s[*i] != '\"' && s[*i])
			(*i)++;
		if (s[*i] == 0)
		{
			printf(ANSI_RED"FALSCH!!!!!!!!!!!!!!one \" too much man!!!!!!!!!!!!\n"ANSI_RESET);
			exit(1);
		}
		return ;
	}
}
// makes extra token for special char and sets lex position to next unspecial char
int	handle_special(char *input, t_lexer *lex, t_token **toktop, size_t start)
{
	printf("\n\nc %c\nl %zu\n\n", input[start], start);
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
	printf("strlen %zu\n", ft_strlen(input));
	printf("\n\nRETURN 1 at c %c\nl %zu\n\n", input[lex->position], lex->position);
	printf(ANSI_RED"TOO MANY << OR >>\n"ANSI_RESET);
	return (1);
}

	// while (input[l] == '>' && input[l])
	// 	l++;
	// if (input[l] == '>' && l != lex->position)
	// 	return (make_special_token(toktop, ">>"), lex->position = l, 0);
	// else if (input[l] == '>')
	// 	return (make_special_token(toktop, ">"), lex->position = l, 0);
	// while (input[l] == '<' && input[l])
	// 	l++;
	// if (input[l] == '<' && l != lex->position)
	// 	return (make_special_token(toktop, "<<"), lex->position = l, 0);
	// else if (input[l] == '>')
	// 	return (make_special_token(toktop, "<"), lex->position = l, 0);
// char	*ft_strndup(char *s, size_t n)
// {
// 	char	*dup;
// 	size_t	i;

// 	i = 0;
// 	if (n > ft_strlen(s))
// 		n = ft_strlen(s);
// 	dup = ft_malloc(sizeof(char) * (ft_strlen(s) + 1 - n));
// 	while (n != 0 && s[i])
// 	{
// 		dup[i] = s[i];
// 		n--;
// 		i++;
// 	}
// 	dup[i] = 0;
// 	return (dup);
// }

// // char	*ft_strnjoin(char *s1, char *s2, size_t n)
// // {
// // 	size_t	i;
// // 	size_t	l;
// // 	char	*dup;

// // 	i = 0;
// // 	l = 0;
// // 	dup = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1 - n));
// // 	if (!dup)
// // 		return (NULL);
// // 	while (s1[i] && n != 0)
// // 	{
// // 		dup[i] = s1[i];
// // 		i++;
// // 		n--;
// // 	}
// // 	while (s2[l] && n != 0)
// // 	{
// // 		dup[i] = s2[l];
// // 		i++;
// // 		l++;
// // 		n--;
// // 	}
// // 	dup[i] = 0;
// // 	return (dup);
// // }

char	*ft_strjoin_at(char *s1, char *s2, size_t start)
{
	size_t	i;
	size_t	l;
	char	*join;

	i = 0;
	l = 0;
	if (!s1 || !s2)
		return (NULL);
	join = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1 - start));
	if (!join)
		return (NULL);
	while (s1[i] && i != start - 1)
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[l])
	{
		join[i] = s2[l];
		i++;
		l++;
	}
	free(s1);
	free(s2);
	join[i] = 0;
	return (join);
}

// char	*found_dollar_sign(char *s, size_t k)
// {
// 	size_t	i;
// 	size_t	l;
// 	char	*value;
// 	char	*new;
// 	char	*tmp;
// 	// char *env = "PATH";
// 	i = 0;
// 	l = 0;
// 	new = NULL;
// 	while (s[i] != 0)
// 	{
// 		while (s[i] != '$' && s[i])
// 			i++;
// 		i++;
// 	printf("scan found = %zu\n", i);
// 		l = i;
// 		while (s[l] != '$' && s[l])
// 			l++;
// 	printf("end scan = %zu\n", l);
// 		tmp = ft_substr(s, i, l - i);
// 	printf("substr = %s\n", tmp);
// 		if (l == i)
// 		{
// 		printf("KILL\n");
// 			value = getenv("$$");
// 			l++;
// 		}
// 		else
// 			value = getenv(tmp);
// 		printf("value = %s\n", value);
// 		while (value[k])
// 			k++;
// 		free(tmp);
// 		tmp = NULL;
// 		if (value != NULL)
// 		{
// 		printf("getenv = %s\n", value);
// 			if (!new)
// 				new = ft_strjoin_at(s, value, i);
// 			else
// 				new = ft_strjoin_at(new, value, i + k);
// 		printf("join at = %s\n", new);
// 		}
// 		i = l;
// 		k = 0;
// 	}
// 	printf("finished\n");
// 	printf("%s", new);
// 	return (new);
// }

// int	catch_dollar_num(char *s)
// {
// 	if (ft_strnstr(s, "$$", ft_strlen(s)))
// 		return (2);
// 	if (ft_strnstr(s, "$", ft_strlen(s)))
// 		return (1);
// 	return (0);
// }

// int main()
// {
// 	char *s =  "ONE $DOLLAR";
// 	char *s2 = "TWO $$ DOLLAR$";
// 	char *s3 = "THREE $ $$ DOLLAR";
// 	int i = 0;
// 	char *tmp;
// // 	tmp = ft_strjoin_at(s, s2, 3);
// // 	printf("%s", tmp)
// // ;	free(tmp);
// 	char *env = "string$USER$USER";
// 	tmp = found_dollar_sign(env, 0);
// 	printf("\n\nres = %s\n\n", tmp);
// 	free(tmp);
// 	tmp = NULL;
// 	system("leaks a.out");
// }
	// printf("%s", ft_strndup("HEY I JUST MET YOU, AND THIS IS CRAZY ", 450));
	// if (ft_strnstr("WOW A $$", "$$", ft_strlen("WOW A $$")))
	// 	printf("I AM CRAZY\n");
	// if (catch_dollar_num(&s[2]) == 1)
	// 	printf("1 NICE1\n");
	// if (catch_dollar_num(&s[8]) == 0)
	// 	printf("2 NICE it FAILED1\n");

	// if (catch_dollar_num(&s2[2]) == 2)
	// 	printf("3 NICE2\n");
	// if (catch_dollar_num(&s2[8]) == 1)
	// 	printf("4 NICE it FAILED2\n");
	// if (catch_dollar_num(&s2[4]) == 1)
	// 	printf("5 not good2\n");

	// if (catch_dollar_num(&s3[0]) == 1)
	// 	printf("6 caught ONE");
	// if (catch_dollar_num(&s3[0]) == 2)
	// 	printf("7 caught TWO");
	// if (catch_dollar_num(&s3[0]) == 0)
	// 	printf("8 caught ZERO");