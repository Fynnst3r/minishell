/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:14:08 by ymauk             #+#    #+#             */
/*   Updated: 2024/03/20 12:42:14 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// creating new list and using f function on every node of the new list
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*element;
	void	*current;

	new_list = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst != 0)
	{
		current = f(lst->content);
		element = ft_lstnew(current);
		if (element == NULL)
		{
			del(current);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, element);
		lst = lst->next;
	}
	return (new_list);
}
