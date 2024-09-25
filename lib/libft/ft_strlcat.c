/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:14:28 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:52:26 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// eine Quell-Zeichenkette (src) an das Ende (dest) anzuhängen
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dst;
	size_t	bytes_left;

	i = 0;
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (size == 0)
		return (len_src);
	if (size <= len_dst)
		return (size + len_src);
	bytes_left = size - len_dst -1;
	while (i < bytes_left && src[i] != '\0')
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
