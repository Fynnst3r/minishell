/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:18 by fforster          #+#    #+#             */
/*   Updated: 2024/10/16 16:46:50 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f_free_split_strs(char **split)
{
	size_t	k;

	k = 0;
	printf("\n!ATTEMPTING SPLIT FREE!\n");
	while (split[k] != NULL)
	{
		free(split[k]);
		k++;
	}
	free(split);
}

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
			if (s1[i] != '|')
				count++;
		}
		else if (ft_isspace(s1[i]))
			word_flag = 0;
		if (s1[i] == '|')
		{
			count++;
			word_flag = 0;
		}
		i++;
	}
	return (count);
}

static int	fill_strings(char const *s, char **split, size_t i, size_t *l)
{
	size_t	k;

	k = 0;
	while (split[k])
		k++;
	split[k] = ft_substr(s, i, *l - i);
	if (s[*l] == '|')
	{
		split[++k] = ft_strdup("|");
		(*l)++;
	}
	if (split[k] == 0)
		return (f_free_split_strs(split), 0);
	// printf("fillmeupbabey k = %zu\n", k);
	return (1);
}

static int	prepare_fill(char const *s, char **split)
{
	size_t	i;
	size_t	l;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != 0)
	{
		while (ft_isspace(s[i]) && s[i] != 0)
			i++;
		l = i;
		while (!ft_isspace(s[l]) && s[l] != 0
			&& !((s[l] == '|' && i < l) || s[i] == '|' && l != i))
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

	// i = 0;
	word_count = f_count_words(s);
	split = ft_calloc(word_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	if (!(prepare_fill(s, split)))
		return (NULL);
	// while (split[i])
	// 	i++;
	// printf("count %zu\ni %zu\n", word_count, i);
	// split[word_count + 1] = NULL;
	return (split);
}

// int	main(void)
// {
// 	size_t	i;
// 	char	**split;
// 	char	*in;

// 	in = "\"|\'| ls|| ls c\\$&\n()at \"|\'|cat echo ||\" echo kill||kill ||why||\"";
// 	i = 0;
// 	split = new_split(in);
// 	printf("WTF IT SPLIT\n");
// 	while (split[i])
// 	{
// 		printf("splt = %s\n", split[i]);
// 		i++;
// 	}
// 	f_free_split_strs(split);
// 	system("leaks a.out");
// }