/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:44:20 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:46:26 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// looking for c in the memory and giving it back
void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (n != 0)
	{
		if (str[i] == (char)c)
		{
			return ((void *)str + i);
		}
		i++;
		n--;
	}
	return (NULL);
}
