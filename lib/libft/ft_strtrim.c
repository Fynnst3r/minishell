/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:41:17 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:53:22 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_is_char(char c, const char *set)
{
	int	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		s_begin;
	int		s_end;
	int		i;

	i = 0;
	s_end = ft_strlen(s1);
	s_begin = 0;
	if (set == NULL || s1 == NULL)
		return (NULL);
	while (s1[s_begin] != '\0' && ft_is_char(s1[s_begin], set))
		s_begin++;
	while (s_end > s_begin && ft_is_char(s1[s_end - 1], set))
		s_end--;
	ptr = (char *) malloc(s_end - s_begin + 1);
	if (ptr == NULL)
		return (NULL);
	while (s_begin < s_end)
		ptr[i++] = s1[s_begin++];
	ptr[i] = '\0';
	return (ptr);
}
