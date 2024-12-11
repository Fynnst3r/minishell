/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:59:04 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/11 14:40:17 by ymauk            ###   ########.fr       */
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
				exit(1);
			entry->name = ft_substr(env[i], 0, equal_sign - env[i]);
			entry->value = ft_strdup(equal_sign + 1);
			new_node = ft_lstnew(entry);
			if (!new_node)
			{
				ft_free(entry->name);
				ft_free(entry->value);
				ft_free(entry);
				exit(1);
			}
			ft_lstadd_back(&data->env_list, new_node);
		}
		i++;
	}
}
