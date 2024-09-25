/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:48:13 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/22 10:19:58 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_if_pos(int number, int fd)
{
	char	array[20];
	int		i;

	i = 0;
	while (number != 0)
	{
		array[i++] = number % 10 + '0';
		number = number / 10;
	}
	i--;
	while (i >= 0)
	{
		ft_putchar(array[i], fd);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		ft_putchar('0', fd);
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', fd);
		n = n * (-1);
	}
	if (n > 0)
	{
		ft_if_pos(n, fd);
	}
}
