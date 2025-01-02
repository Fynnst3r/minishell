/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:36:55 by ymauk             #+#    #+#             */
/*   Updated: 2025/01/01 21:47:28 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env_entry(t_env_entry *entry)
{
	ft_free(entry->name);
	ft_free(entry->value);
	entry->name = NULL;
	entry->value = NULL;
	ft_free(entry);
	entry = NULL;
}

int	remove_entry(t_list **top, t_env_entry *entry, t_list *to_del)
{
	t_list	*tmp;

	if (!*top)
		return (1);
	if ((*top)->content == entry)
	{
		to_del = *top;
		(*top) = (*top)->next;
	}
	else
	{
		tmp = *top;
		while (tmp->next != NULL)
		{
			if (tmp->next->content == entry)
			{
				to_del = tmp->next;
				tmp->next = tmp->next->next;
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (ft_free(to_del), to_del = NULL, free_env_entry(entry), 0);
}

void	exec_unset(t_data *data, char **cmd)
{
	t_list		*curr;
	t_env_entry	*enventry;
	size_t		i;

	if (!cmd)
		return ;
	i = 1;
	while (cmd[i])
	{
		curr = data->env_list;
		while (curr && cmd[i])
		{
			enventry = (t_env_entry *)curr->content;
			if (!ft_strncmp(cmd[i], enventry->name,
					ft_strlen(enventry->name) + 1))
			{
				curr = curr->next;
				if (remove_entry(&data->env_list, enventry, NULL))
					data->e_status = 1;
			}
			else
				curr = curr->next;
		}
		i++;
	}
}
