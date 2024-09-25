/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:26:35 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:31:35 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
//Den Speicherbereich mit Null füllen
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n != 0)
	{
		*p = 0;
		n--;
		p++;
	}
}
