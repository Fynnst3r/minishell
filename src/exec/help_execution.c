/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:58:19 by ymauk             #+#    #+#             */
/*   Updated: 2025/01/04 21:51:53 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	check_env_builtins(t_data *data, char **cmd)
{
	if (!*cmd)
		return ;
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		exec_export(data, cmd);
	else if (strncmp(cmd[0], "unset", 6) == 0)
		exec_unset(data, cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		exec_cd(data, cmd);
}

void	extra_exec(t_data *data, t_cmd *st_node)
{
	t_red	*red_node;
	t_herd	*herd_node;
	t_exec	*exec_node;

	if (st_node->type == RED)
	{
		red_node = (t_red *)st_node;
		extra_exec(data, (t_cmd *)red_node->cmd);
		return ;
	}
	if (st_node->type == HEREDOC)
	{
		herd_node = (t_herd *)st_node;
		extra_exec(data, (t_cmd *)herd_node->cmd);
		return ;
	}
	if (st_node->type == EXECUTE)
	{
		exec_node = (t_exec *)st_node;
		check_env_builtins(data, exec_node->argv);
	}
}

static char	**init_env_array(t_list *env_list)
{
	t_list		*current;
	size_t		i;
	char		**ret;

	i = 0;
	current = env_list;
	while (current != NULL)
	{
		if (current->content)
			i++;
		current = current->next;
	}
	ret = ft_calloc(sizeof(char *), i + 1);
	return (ret);
}

char	**env_list_to_array(t_data *data)
{
	char		**ret;
	char		*tmp;
	t_list		*current;
	t_env_entry	*entry;
	size_t		i;

	i = 0;
	current = data->env_list;
	ret = init_env_array(data->env_list);
	while (current != NULL)
	{
		if (current->content)
			entry = (t_env_entry *)current->content;
		if (entry->name)
		{
			tmp = ft_strjoin(entry->name, "=");
			ret[i] = ft_strjoin(tmp, entry->value);
			ft_free(tmp);
			i++;
		}
		current = current->next;
	}
	return (ret);
}
