/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:03:16 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:46:11 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// int to ascii

int	ft_size_n(long n)
{
	int	counter;
	int	minus;

	counter = 0;
	minus = 0;
	if (n < 0)
		minus = -1;
	if (n == 0)
	{
		return (1);
	}
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	if (minus == -1)
		counter++;
	return (counter);
}

char	ft_process(long n, char *ptr, int size_n)
{
	int	holder;

	holder = size_n;
	while (n != 0)
	{
		ptr[--size_n] = n % 10 + '0';
		n = n / 10;
	}
	ptr[holder] = '\0';
	return (*ptr);
}

char	*ft_itoa(int n)
{
	int		size_n;
	char	*ptr;
	long	nb;

	nb = n;
	size_n = ft_size_n(nb);
	ptr = (char *) malloc (size_n + 1);
	if (ptr == NULL)
		return (NULL);
	if (nb == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
	}
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = nb * (-1);
	}
	if (nb > 0)
	{
		*ptr = ft_process(nb, ptr, size_n);
	}
	return (ptr);
}
