/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:16:18 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:51:57 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
// filling a given Memeory area with a certain value
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	value;

	p = (unsigned char *)b;
	value = (unsigned char)c;
	while (len != 0)
	{
		*p = value;
		len--;
		p++;
	}
	return (b);
}
