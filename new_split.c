/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:18 by fforster          #+#    #+#             */
/*   Updated: 2024/10/08 19:44:59 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "githubrepo/minishell.h"

// static char	*ex_substr(char const *s, unsigned int start, size_t len, bool p)
// {
// 	char	*sub;
// 	size_t	i;

// 	i = 0;
// 	if (start >= ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (len > ft_strlen(s) - start)
// 		len = ft_strlen(s) - start;
// 	sub = (char *)malloc(len + 1 * sizeof(const char));
// 	if (!sub)
// 		return (0);
// 	while (len > 0)
// 	{
// 		sub[i] = s[start];
// 		i++;
// 		start++;
// 		len--;
// 	}
// 	sub[i] = 0;
// 	if (p)
// 		free(sub);
// 	return (sub);
// }

static void	f_free_strs(char **split)
{
	size_t	k;

	k = 0;
	printf("FREED\n");
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
		if (!is_whitespc(s1[i]) && word_flag == 0)
		{
			word_flag = 1;
			count++;
		}
		else if (is_whitespc(s1[i]))
			word_flag = 0;
		if (s1[i] == '|')
			count++;
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
	// char	*tmp;

	i = 0;
	k = 0;
	while (s[i] != 0)
	{
		while (is_whitespc(s[i]) && s[i] != 0)
			i++;
		l = i;
		while (!is_whitespc(s[l]) && s[l] != 0 && s[l] != '|')
			l++;
		if (i < l)
		{
			// tmp = ft_substr(s, i, l - i);
			if (s[l] == '|' && !is_whitespc(s[l + 1]))
			{
				l++;
				split[k++] = ft_strdup("|");
			}
			split[k] = ft_substr(s, i, l - i);
			printf("%s\n", split[k]);
			if (split[k] == 0)
				return (f_free_strs(split), 0);
			k++;
		}
		i = l;
	}
	printf("uhhh\n");
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
		return (NULL);
	printf("filled\n");
	return (split);
}

int	main()
{
	size_t	i;
	char	**split;
	char *in = "one|asd | f";
	i = 0;

	split = new_split(in);
	printf("WTF");
	while (split[i])
	{
		printf("splt = %s\n", split[i]);
		i++;
	}
	
}

