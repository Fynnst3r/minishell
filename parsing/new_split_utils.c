/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:37:15 by fforster          #+#    #+#             */
/*   Updated: 2024/10/20 18:55:56 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(char *s, size_t n)
{
	char	*dup;
	size_t	i;

	i = 0;
	if (n > ft_strlen(s))
		n = ft_strlen(s);
	dup = malloc(sizeof(char) * (ft_strlen(s) + 1 - n));
	while (n != 0 && s[i])
	{
		dup[i] = s[i];
		n--;
		i++;
	}
	dup[i] = 0;
	return (dup);
}

// char	*ft_strnjoin(char *s1, char *s2, size_t n)
// {
// 	size_t	i;
// 	size_t	l;
// 	char	*dup;

// 	i = 0;
// 	l = 0;
// 	dup = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1 - n));
// 	if (!dup)
// 		return (NULL);
// 	while (s1[i] && n != 0)
// 	{
// 		dup[i] = s1[i];
// 		i++;
// 		n--;
// 	}
// 	while (s2[l] && n != 0)
// 	{
// 		dup[i] = s2[l];
// 		i++;
// 		l++;
// 		n--;
// 	}
// 	dup[i] = 0;
// 	return (dup);
// }

char	*ft_strjoin_at(char *s1, char *s2, size_t start)
{
	size_t	i;
	size_t	l;
	char	*join;

	i = 0;
	l = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1 - start));
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
	join[i] = 0;
	return (join);
}

char	*found_dollar_sign(char *s, size_t k)
{
	size_t	i;
	size_t	l;
	char	*value;
	char	*new;
	char	*tmp;
	// char *env = "PATH";
	i = 0;
	l = 0;
	new = NULL;
	while (s[i] != 0)
	{
		while (s[i] != '$' && s[i])
			i++;
		i++;
	printf("scan found = %zu\n", i);
		l = i;
		while (s[l] != '$' && s[l])
			l++;
	printf("end scan = %zu\n", l);
		tmp = ft_substr(s, i, l - i);
	printf("substr = %s\n", tmp);
		if (l == i)
		{
		printf("KILL\n");
			value = getenv("$$");
			l++;
		}
		else
			value = getenv(tmp);
		printf("value = %s\n", value);
		while (value[k])
			k++;
		free(tmp);
		tmp = NULL;
		if (value != NULL)
		{
		printf("getenv = %s\n", value);
			if (!new)
				new = ft_strjoin_at(s, value, i);
			else
				new = ft_strjoin_at(new, value, i + k);
		printf("join at = %s\n", new);
		}
		i = l;
		k = 0;
	}
	printf("finished\n");
	printf("%s", new);
	return (new);
}

int	catch_dollar_num(char *s)
{
	if (ft_strnstr(s, "$$", ft_strlen(s)))
		return (2);
	if (ft_strnstr(s, "$", ft_strlen(s)))
		return (1);
	return (0);
}

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