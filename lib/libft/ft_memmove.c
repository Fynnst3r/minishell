/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:04:04 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/20 12:49:10 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// same as memcpy, but handels memory overlaping differently
//checking of dst memory area comes in front of src memory area,
// copying from behind
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*char_dst;
	char	*char_src;

	char_dst = (char *)dst;
	char_src = (char *)src;
	if (dst == src)
		return (dst);
	if (char_src < char_dst)
	{
		while (len > 0)
		{
			len--;
			char_dst[len] = char_src[len];
		}
	}
	else
	{
		ft_memcpy(char_dst, char_src, len);
	}
	return (char_dst);
}
