/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:23:39 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:46:39 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
// copying n bytes from src into dst
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_char;
	const char	*src_char;
	size_t		i;

	dst_char = (char *)dst;
	src_char = (char *)src;
	i = 0;
	if (dst_char == NULL && src_char == NULL)
		return (NULL);
	while (i < n)
	{
		dst_char[i] = src_char[i];
		i++;
	}
	return (dst);
}
