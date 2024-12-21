/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:59:04 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/20 20:41:57 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_env_list(t_data *data, char **env)
{
	int			i;
	char		*equal_sign;
	t_list		*new_node;
	t_env_entry	*entry;

	data->env_list = NULL;
	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			entry = ft_malloc(sizeof(t_env_entry));
			if (!entry)
				ft_error("Malloc fail for env entry", 42, NULL);
			entry->name = ft_substr(env[i], 0, equal_sign - env[i]);
			entry->value = ft_strdup(equal_sign + 1);
			new_node = ft_lstnew(entry);
			if (!new_node)
			{
				free_env_entry(entry);
				ft_error("Malloc fail for env entry", 42, NULL);
			}
			ft_lstadd_back(&data->env_list, new_node);
		}
		i++;
	}
}
