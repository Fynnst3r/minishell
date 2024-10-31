/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SPLIT_BACKUP.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:18 by fforster          #+#    #+#             */
/*   Updated: 2024/10/31 16:25:52 by fforster         ###   ########.fr       */
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

static void	skip_quote(const char *s, size_t *i, size_t *count)
{
	if (s[*i] == '\'')
	{
		// printf("HAAALLOOO\n");
		(*i)++;
		while (s[*i] != '\'' && s[*i])
			(*i)++;
		(*count)++;
		(*i)++;
		return ;
	}
	if (s[*i] == '\"')
	{
		// printf("HAaaaaLLOOO\n");
		(*i)++;
		while (s[*i] != '\"' && s[*i])
			(*i)++;
		(*count)++;
		(*i)++;
		return ;
	}
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
		else if (!ft_isspace(s[i]) && word_flag == 0)
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

static char	*fill_quote(char const *s, size_t *realL)
{
	size_t	i;
	size_t	l;
	char	*ret;

	i = 0;
	l = 0;
	while (s[i] != '\"' && s[i] != '\'')
		i++;
	l = i + 1;
	while (s[l] != '\"' && s[l] != '\'')
		l++;
	ret = ft_substr(s, i, l);
	*realL = l + 1;
	// printf("qupte = %s\n", ret);
	return (ret);
}

static int	fill_strings(char const *s, char **split, size_t i, size_t *l)
{
	size_t	k;

	k = 0;
	while (split[k])
		k++;
	// printf("fill string s = %s\n", &s[i]);
	// printf("fill string i = %zu\n", i);
	if (s[i] == '\'' || s[i] == '\"')
	{
		split[k] = fill_quote(s, l);
		printf("%s\n", split[k]);
			printf("XD\n");
		return (1);
	}
	split[k] = ft_substr(s, i, *l - i);
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
	bool	quote;
	// size_t	k;

	i = 0;
	while (s[i] != 0)
	{
		while ((ft_isspace(s[i])) && s[i] != 0)
			i++;
		l = i;
		while (!ft_isspace(s[l]) && s[l] != 0
			&& !((is_special_char(s[l]) && i < l)
				|| is_special_char(s[i]) && l != i))
			l++;
		if (i < l)
			if (!fill_strings(s, split, i, &l))
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

	word_count = f_count_words(s, -1, 0);
	// printf("wordc = %zu\n", word_count);
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

// int	main (void)
// {
// 	size_t	i;
// 	char	**split;
// 	char	*in;

// 	in = ft_strdup("echo \"echo ||<><  ceho\"");
// 	printf("input %s\n", in);
// 	split = new_split(in);
// 	printf("WTF IT SPLIT\n\n");
// 	i = 0;
// 	while (split[i])
// 	{
// 		printf("splt = %s\n", split[i]);
// 		i++;
// 	}
// 		printf("\nsplt = %s\n\nsplitcount %zu\n", split[i], i);
// 	// f_free_split_strs(split);
// 	// system("leaks a.out");
// }

// static bool	count_quotes(char const *s)
// {
// 	size_t	i;
// 	size_t	dq;
// 	size_t	sq;

// 	i = 0;
// 	dq = 0;
// 	sq = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'')
// 			sq++;
// 		if (s[i] == '\"')
// 			dq++;
// 		i++;
// 	}
// 	if (dq % 2 != 0 || sq % 2 != 0)
// 		return (false);
// 	return (true);
// }