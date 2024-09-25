/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:51:01 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:59:09 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
// //counting the number of words in s
size_t	ft_number_words(char const *s, char c)
{
	size_t	counter_words;
	size_t	i;

	counter_words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
		{
			counter_words++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (counter_words);
}
// finding the length for the correct calculation of the substring
// if there is no c found, the pointer to s at the start index gets returned
// if there is more then one word, the next c gets found and the size 
// of the word gets calculated by taking the point of start away from 
// the point of the c which is found

size_t	ft_end_substr(char const *s, char c, size_t start)
{
	char const	*found;

	found = ft_strchr(s + start, c);
	if (found == NULL)
		return (ft_strlen(&s[start]));
	else
		return (found - &s[start]);
}

// //freeing every part of the array if error
// //at the end freeing the array itself
void	*ft_free(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	start;
	size_t	i;

	start = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	array = malloc((ft_number_words(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (s[start] != '\0')
	{
		while (s[start] == c)
			start++;
		if (s[start] == '\0')
			break ;
		array[i] = ft_substr(s, start, ft_end_substr(s, c, start));
		if (array[i] == NULL)
			return (ft_free(array));
		i++;
		start += ft_end_substr(s, c, start);
	}
	array[i] = NULL;
	return (array);
}
