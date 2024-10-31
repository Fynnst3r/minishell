/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alternate_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:18 by fforster          #+#    #+#             */
/*   Updated: 2024/10/31 16:23:53 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

static bool	isemptystring(const char *s)
{
	while (*s)
	{
		if (!ft_isspace(*s))
			return (0);
		s++;
	}
	return (1);
}

static void	skip_quote(const char *s, size_t *i, size_t *count)
{
	if (s[*i] == '\'')
	{
		(*i)++;
			// printf("\'i++ = %zu\n", *i);
		while (s[*i] != '\'' && s[*i])
		// {
			(*i)++;
		// 	printf("\'i++ = %zu\n", *i);
		// }
			// printf("\'COUNT++\n");
		(*count)++;
		(*i)++;
			// printf("\'i++ = %zu\n", *i);
		return ;
	}
	if (s[*i] == '\"')
	{
		(*i)++;
		// printf("\"i++ = %zu\n", *i);
		while (s[*i] != '\"' && s[*i])
		// {
			(*i)++;
			// printf("\"i++ = %zu\n", *i);
		// }
		(*count)++;
			// printf("\" COUNT++\n");
		(*i)++;
			// printf("\"i++ = %zu\n", *i);
		return ;
	}
	// printf("endi++ = %zu\n", *i);
	(*i)++;
	(*count)++;
}

static size_t	f_count_words(const char *s, size_t i, size_t count)
{
	int		word_flag;

	word_flag = 0;
	if (isemptystring(s))
		return (0);
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			skip_quote(s, &i, &count);
		else if ((!ft_isspace(s[i])) && word_flag == 0)
		{
			word_flag = 1;
			// printf("space count++\n");
			if (!is_special_char(s[i]))
				count++;
		}
		else if (ft_isspace(s[i]))
			word_flag = 0;
		if (is_special_char(s[i]))
		{
			// printf("specialchar++\n");
			count++;
			word_flag = 0;
		}
		// printf("i++ = %zu\n", i);
	}
	return (count);
}

// int main()
// {
// 	size_t count = f_count_words("echo \'hey\"$fART\"sex'\"", -1, 0);
// 	printf("%zu\n", count);
// }
// static int	fill_strings(char const *s, char **split, size_t i, size_t l)
// {
// 	size_t	k;

// 	k = 0;
// 	while (split[k])
// 		k++;
// 	// if (catch_dollar_num(s))
// 	// 	split[*k] = found_dollar_signs(s);
// 	// else
// 	split[k] = ft_substr(s, i, l - i);
// 	// printf("filled = %s\n", split[k]);
// 	// (*k)++;
// 	if (split[k] == 0)
// 		return (f_free_split_strs(split), 0);
// 	return (1);
// }

// static int	prepare_fill(char const *s, char **split)
// {
// 	size_t	i;
// 	size_t	l;
// 	bool	quote;
// 	// size_t	k;
// 	// k = 0;
// 	i = 0;
// 	quote = false;
// 	while (s[i] != 0)
// 	{
// 		while ((ft_isspace(s[i]) || quote) && s[i] != 0)
// 		{
// 			quote = in_quote(s[i++], quote);
// 			printf("i = %zu\n", i);
// 		}
// 		l = i;
// 		while (!ft_isspace(s[l] || !quote) && s[l] != 0
// 			&& !((is_special_char(s[l], quote) && i < l)
// 				|| is_special_char(s[i], quote) && l != i))
// 		{
// 			quote = in_quote(s[l++], quote);
// 			printf("l = %zu\n", l);
// 		}
// 		if (i < l)
// 			if (!fill_strings(s, split, i, l))
// 				return (0);
// 		i = l;
// 	}
// 	return (1);
// }

// char	**new_split(char const *s)
// {
// 	char	**split;
// 	size_t	word_count;
// 	// size_t	i;

// 	word_count = f_count_words(s);
// 	printf("wordc = %zu\n", word_count);
// 	split = ft_calloc(word_count + 1, sizeof(char *));
// 	if (!split)
// 		return (NULL);
// 	if (!(prepare_fill(s, split)))
// 		return (NULL);
// 	// REALLOC SPLIT ARRAY AND THEN FREE OLD ONE
// 	// i = 0;
// 	// while (word_count + 1 != i)
// 	// {
// 	// 	free(split[i]);
// 	// 	split[i++] = NULL;
// 	// }
// 	return (split);
// }
// WORDCOUNT COUNTS TOO MANY DUE TO $, sadly $$ is an valid env var... and you can chain like this $test$test2 
// int	main(void)
// {
// 	size_t	i;
// 	char	**split;
// 	char	*in;

// 	// in = "\"|\'| ls|| ls c\\$&\n(< >)at \"|\'|$cat$echo <  < << > > >>||\" echo kill||kill ||why||\"";
// 	// in = "\"|\'| ls|| ls c\\&\n(< >)at \"|\'|catecho <  < << > > >>||\" echo kill||kill ||why||\"";
// 	// in = "$ e cho $asd$asd  $$ $";
// 	in = " $ $$sdfgdsf $? asdasd$ada $$ $$$ ";
// 	printf("input %s\n", in);
// 	i = 0;
// 	split = new_split(in);
// 	printf("WTF IT SPLIT\n");
// 	while (split[i])
// 	{
// 		printf("splt = %s\n", split[i]);
// 		i++;
// 	}
// 		printf("splt = %s\nsplitcount %zu\n", split[i], i);
// 	f_free_split_strs(split);
// 	// system("leaks a.out");
// }
