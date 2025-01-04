/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:59:04 by ymauk             #+#    #+#             */
/*   Updated: 2025/01/03 19:59:00 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_for_shlvl(t_data *data)
{
	t_list		*current;
	t_env_entry	*entry;
	char		*tmp[3];

	entry = NULL;
	current = data->env_list;
	data->e_status = 0;
	if (current == NULL)
		data->e_status = 1;
	while (current != NULL)
	{
		if (current->content)
			entry = (t_env_entry *)current->content;
		if (entry->name)
			if (!ft_strncmp(entry->name, "SHLVL", 6))
				return ;
		current = current->next;
	}
	tmp[0] = "export";
	tmp[1] = "SHLVL=1";
	tmp[2] = NULL;
	exec_export(data, tmp);
}

void	handle_shlvl(t_env_entry *entry)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strncmp(entry->name, "SHLVL", 6) && *entry->value)
	{
		tmp = ft_strdup(entry->value);
		ft_free(entry->value);
		entry->value = NULL;
		entry->value = ft_itoa(ft_atoi(tmp) + 1);
		ft_free(tmp);
		tmp = NULL;
	}
	else if (!ft_strncmp(entry->name, "SHLVL", 6))
	{
		ft_free(entry->value);
		entry->value = NULL;
		entry->value = ft_strdup("1");
	}
}

void	fill_env_list(t_data *data, char **env)
{
	size_t		i;
	char		*equal_sign;
	t_list		*new_node;
	t_env_entry	*entry;

	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			entry = ft_malloc(sizeof(t_env_entry));
			entry->name = ft_substr(env[i], 0, equal_sign - env[i]);
			entry->value = ft_strdup(equal_sign + 1);
			if (!ft_strncmp(entry->name, "SHLVL", 6))
				handle_shlvl(entry);
			new_node = ft_lstnew(entry);
			if (!new_node)
				free_env_entry(entry);
			ft_lstadd_back(&data->env_list, new_node);
		}
		i++;
	}
	check_for_shlvl(data);
}
