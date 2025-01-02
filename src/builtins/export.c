/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:03:24 by fforster          #+#    #+#             */
/*   Updated: 2025/01/01 16:42:24 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_valid_name(char *s, t_data *data)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			printf("YM_FF_SHELL: export: `%s': not a valid identifier\n", s);
			data->e_status = 2;
			return (1);
		}
		if (s[i] == '=')
			break ;
		i++;
	}
	if (i == 0)
	{
		printf("YM_FF_SHELL: export: `%s': not a valid identifier\n", s);
		data->e_status = 2;
		return (1);
	}
	return (0);
}

t_list	*find_name(t_list **top, t_env_entry *newentry)
{
	t_list		*curr;
	t_env_entry	*tocheck;

	curr = *top;
	while (curr)
	{
		tocheck = curr->content;
		if (!ft_strncmp(tocheck->name, newentry->name,
				ft_strlen(tocheck->name) + 1))
		{
			free_env_entry(curr->content);
			curr->content = newentry;
			return (curr);
		}
		curr = curr->next;
	}
	return (NULL);
}

void	add_or_replace_entry(t_data *data, char *cmd, char *equal_sign)
{
	t_list		*list_node;
	t_env_entry	*entry;

	entry = ft_malloc(sizeof(t_env_entry));
	if (!entry)
		ft_error("Malloc fail for env entry", 42, NULL);
	entry->name = ft_substr(cmd, 0, equal_sign - cmd);
	entry->value = ft_strdup(equal_sign + 1);
	list_node = find_name(&data->env_list, entry);
	if (!list_node)
	{
		list_node = ft_lstnew(entry);
		ft_lstadd_back(&data->env_list, list_node);
	}
	if (!list_node)
	{
		free_env_entry(entry);
		ft_error("Malloc fail for list node", 42, NULL);
	}
}

void	exec_export(t_data *data, char **cmd)
{
	char		*equal_sign;
	size_t		i;

	i = 1;
	data->e_status = 0;
	while (cmd[i])
	{
		equal_sign = ft_strchr(cmd[i], '=');
		if (equal_sign && !check_valid_name(cmd[i], data))
		{
			add_or_replace_entry(data, cmd[i], equal_sign);
		}
		i++;
	}
}
