/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:29:39 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/20 12:43:25 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// number of elements in the list
int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	if (lst == 0)
		return (0);
	while (lst != 0)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
