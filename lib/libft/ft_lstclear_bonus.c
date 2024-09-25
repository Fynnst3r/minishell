/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:04:17 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/20 12:37:23 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// delete all elements of list
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*next;

	if (lst == NULL || *lst == NULL)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		next = ptr->next;
		del(ptr->content);
		free (ptr);
		ptr = next;
	}
	ptr = NULL;
	*lst = ptr;
}
