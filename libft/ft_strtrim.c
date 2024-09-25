/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:53:45 by fforster          #+#    #+#             */
/*   Updated: 2024/04/04 19:10:40 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_check_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trimmed;
	size_t		i;
	size_t		l;
	size_t		k;

	i = 0;
	l = ft_strlen(s1);
	k = 0;
	while (s1[i] && f_check_set(s1[i], set))
		i++;
	while (f_check_set(s1[l - 1], set) && l > i)
		l--;
	trimmed = (char *)malloc((l - i + 1) * sizeof(char));
	if (trimmed == 0)
		return (0);
	while (i < l)
	{
		trimmed[k] = s1[i];
		i++;
		k++;
	}
	trimmed[k] = 0;
	return (trimmed);
}

// #include<stdio.h>
// int main()
// {
// 	const char *s = "saaas";
// 	const char *c = "s";
// 	printf("%s", ft_strtrim(s, c));
// }