/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:36:32 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/21 11:31:41 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// "Allocate and Clear" Funktion
void	*ft_calloc(size_t count, size_t size)
{
	size_t	size_required;
	void	*ptr;
	int		null;

	size_required = count * size;
	ptr = malloc(size_required);
	null = 0;
	if (ptr != 0)
	{
		ft_memset(ptr, null, size_required);
	}
	return (ptr);
}
