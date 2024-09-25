/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:01:06 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/18 13:26:22 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// auf jedes Zeichen wird f angewendet, aber neuer string
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	size;

	i = 0;
	j = 0;
	size = 0;
	if (s == 0)
		return (NULL);
	while (s[size] != '\0')
	{
		size++;
	}
	ptr = (char *) malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr[j] = f(i, s[i]);
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
