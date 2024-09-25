/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:20:29 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:46:30 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
// comparing two storage areas
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*char_s1;
	const unsigned char	*char_s2;
	int					i;

	char_s1 = s1;
	char_s2 = s2;
	i = 0;
	while (n != 0)
	{
		if (char_s1[i] != char_s2[i])
		{
			return (char_s1[i] - char_s2[i]);
		}
		i++;
		n--;
	}
	return (0);
}
