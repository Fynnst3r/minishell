/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:18 by fforster          #+#    #+#             */
/*   Updated: 2024/09/30 18:17:18 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	f_free_strs(char **split)
{
	size_t	k;

	k = 0;
	while (split[k] != NULL)
	{
		free(split[k]);
		k++;
	}
	free(split);
}

static int	is_whitespc(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
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
		if (is_whitespc(s1[i]) && word_flag == 0)
		{
			word_flag = 1;
			count++;
		}
		else if (!is_whitespc(s1[i]))
			word_flag = 0;
		i++;
	}
	printf("cnt = %zu\n", count);
	return (count);
}


static int	f_fill_str(char const *s, char **split)
{
	size_t	i;
	size_t	l;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != 0)
	{
		while (is_whitespc(s[i]) && s[i] != 0)
			i++;
		l = i;
		while (is_whitespc(s[l]) && s[l] != 0)
			l++;
		if (i < l)
		{
			split[k] = ft_substr(s, i, l - i);
			if (split[k] == 0)
				return (f_free_strs(split), 0);
			k++;
		}
	// printf("uhhh\n");
		i = l;
	}
	return (1);
}

char	**new_split(char const *s)
{
	char	**split;
	size_t	word_count;

	word_count = f_count_words(s);
	printf("counted\n");
	split = ft_calloc(word_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	if (!(f_fill_str(s, split)))
	printf("filled\n");
		return (NULL);
	return (split);
}

// int	main()
// {
// 	size_t	i;
// 	char	**split;
// 	char *in = "HEY	";
// 	i = 0;

// 	split = new_split(in);
// 	while (split[i])
// 	{
// 		printf("splt = %s", split[i]);
// 		i++;
// 	}
	
// }

// useless