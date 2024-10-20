/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:18 by fforster          #+#    #+#             */
/*   Updated: 2024/10/19 18:52:27 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '\"' || c == '\'')
		return (1);
	return (0);
}

// static size_t	f_count_words(char const *s)
// {
// 	size_t	counter;
// 	size_t	i;

// 	counter = 0;
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		while (ft_isspace(s[i]) && s[i] != '\0')
// 			i++;
// 		if (s[i] != '\0')
// 		{
// 			counter++;
// 			while (!ft_isspace(s[i]) && s[i] != '\0')
// 			{
// 				if (is_special_char(s[i]) || (s[i] == '$' && s[i + 1] == '$'))
// 					counter++;
// 				i++;
// 			}
// 		}
// 	}
// 	return (counter);
// }

static size_t	f_count_words(const char *s1)
{
	size_t	i;
	size_t	count;
	int		word_flag;

	i = 0;
	count = 0;
	word_flag = 0;
	while (s1[i])
	{
		if (!ft_isspace(s1[i]) && word_flag == 0)
		{
			word_flag = 1;
			if (!is_special_char(s1[i]))
				count++;
		}
		else if (ft_isspace(s1[i]))
			word_flag = 0;
		if (is_special_char(s1[i]))
		{
			count++;
			word_flag = 0;
		}
		i++;
	}
	return (count);
}

static int	fill_strings(char const *s, char **split, size_t i, size_t l)
{
	size_t	k;

	k = 0;
	while (split[k])
		k++;
	// if (catch_dollar_num(s))
	// 	split[*k] = found_dollar_signs(s);
	// else
	split[k] = ft_substr(s, i, l - i);
	// printf("filled = %s\n", split[k]);
	// (*k)++;
	if (split[k] == 0)
		return (f_free_split_strs(split), 0);
	return (1);
}

static int	prepare_fill(char const *s, char **split)
{
	size_t	i;
	size_t	l;
	// size_t	k;

	i = 0;
	// k = 0;
	while (s[i] != 0)
	{
		while (ft_isspace(s[i]) && s[i] != 0)
			i++;
		l = i;
		while (!ft_isspace(s[l]) && s[l] != 0
			&& !((is_special_char(s[l]) && i < l)
				|| is_special_char(s[i]) && l != i))
			l++;
		if (i < l)
			if (!fill_strings(s, split, i, l))
				return (0);
		i = l;
	}
	return (1);
}

char	**new_split(char const *s)
{
	char	**split;
	size_t	word_count;
	// size_t	i;

	word_count = f_count_words(s);
	printf("wordc = %zu\n", word_count);
	split = ft_calloc(word_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	if (!(prepare_fill(s, split)))
		return (NULL);
	// REALLOC SPLIT ARRAY AND THEN FREE OLD ONE
	// i = 0;
	// while (word_count + 1 != i)
	// {
	// 	free(split[i]);
	// 	split[i++] = NULL;
	// }
	return (split);
}
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
