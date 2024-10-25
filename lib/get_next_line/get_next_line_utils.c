/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:06:36 by ymauk             #+#    #+#             */
/*   Updated: 2024/07/08 11:19:35 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	if (s != NULL)
	{
		while (*s != '\0')
		{
			if (*s == (char)c)
			{
				return ((char *)s);
			}
			s++;
		}
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (s1 == NULL)
		s1 = ft_strdup_gnl("");
	if (s2 == NULL)
		return (NULL);
	join = malloc (sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2)) + 1);
	if (join == NULL)
	{
		free (s1);
		free (s2);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1[j] != '\0')
		join[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		join[i++] = s2[j++];
	join[i] = '\0';
	free (s1);
	return (join);
}

int	ft_strlen_gnl(const char *value)
{
	int	counter;

	counter = 0;
	while (*value != '\0')
	{
		counter += 1;
		value += 1;
	}
	return (counter);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	i = 0;
	if (s == NULL)
		return (NULL);
	size = ft_strlen_gnl(s);
	if (start >= size)
		return (NULL);
	if (len > size - start)
		len = size - start;
	str = (char *) malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len && start < size)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_gnl(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(ft_strlen_gnl(s1) + 1);
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
