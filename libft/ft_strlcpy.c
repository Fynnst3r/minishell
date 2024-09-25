/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:19:17 by fforster          #+#    #+#             */
/*   Updated: 2024/03/14 20:19:43 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	while (*src && dstsize - 1 > 0)
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	if (dstsize != 0)
		*dst = 0;
	return (srclen);
}
// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char a[] = "123";
// 	const char b[] = "456";
// 	size_t s = 4;
// 	printf("mine %lu\nofic %lu", ft_strlcpy(a, b, s), strlcpy(a, b, s));
// 	printf("\n%s\n%s",a ,b);
// }