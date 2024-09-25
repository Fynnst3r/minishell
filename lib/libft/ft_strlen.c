/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:59:26 by ymauk             #+#    #+#             */
/*   Updated: 2024/07/18 18:41:47 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *value)
{
	int	counter;

	if (value == NULL)
		return (0);
	counter = 0;
	while (*value != '\0')
	{
		counter += 1;
		value += 1;
	}
	return (counter);
}
