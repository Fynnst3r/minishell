/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:18 by fforster          #+#    #+#             */
/*   Updated: 2024/11/03 21:54:53 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (!is_special_char(s[i]))
				count++;
		}
		else if (ft_isspace(s[i]))
			word_flag = 0;
		if (is_special_char(s[i]))
		{
			count++;
			word_flag = 0;
		}
	}
	return (count);
}

static char	*fill_quote(char const *s, size_t *pl, char q)
{
	size_t	i;
	size_t	l;
	char	*ret;

	i = 0;
	l = 0;
	while (s[i] != q && s[i])
		i++;
	l = i + 1;
	while (s[l] != q && s[l])
		l++;
	if (s[i] == 0 || s[l] == 0)
	{
		printf("WHOOOOPS!\n");
		exit(1);
	}
	ret = ft_substr(s, i, l);
	*pl = l + 1;
	return (ret);
}

static int	fill_strings(char const *s, char **split, size_t i, size_t *l)
{
	size_t	k;

	k = 0;
	printf("fill it up\n");
	while (split[k])
		k++;
	if (s[i] == '\'' || s[i] == '\"')
	{
		printf("here\n");
		printf("str = %s\n", &s[i]);
		split[k] = fill_quote(s, l, s[i]);
		if (s[*l] == '\'' || s[*l] == '\"')
		{
			i = *l;
			fill_strings(s, split, i, l);
		}
		return (1);
	}
	split[k] = ft_substr(s, i, *l - i);
	if (split[k] == 0)
		return (f_free_split_strs(split), 0);
	return (1);
}

static int	prepare_fill(char const *s, char **split)
{
	size_t	i;
	size_t	l;
	bool	quote;

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

	word_count = f_count_words(s, -1, 0);
	printf("wc = %zu\n", word_count);
	// exit(1);
	split = ft_calloc(word_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	if (!(prepare_fill(s, split)))
		return (NULL);
	return (split);
}
// cant fill but count string when quoted after quoted happens
int	main (void)
{
	size_t	i;
	char	**split;
	char	*in;

	init_garbage_collector();
	in = ft_strdup("echo \"why ist \'es\' not\" ass \'  ");
	printf("input %s\n", in);
	split = new_split(in);
	printf("WTF IT SPLIT\n\n");
	i = 0;
	while (split[i])
	{
		printf("splt = %s\n", split[i]);
		i++;
	}
	printf("\nsplt = %s\n\nsplitcount %zu\n", split[i], i);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	// system("leaks a.out");
}
