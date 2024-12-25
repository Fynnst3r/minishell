/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:46:56 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/25 22:07:39 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtins(t_data *data, char **cmd)
{
	if (!*cmd)
		return (1);
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		exec_echo(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		exec_pwd(data);
	}
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		exec_env(data);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		exec_export(data, cmd);
	else if (strncmp(cmd[0], "unset", 6) == 0)
		exec_unset(data, cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		exec_cd(data, cmd);
	else
		return (0);
	// else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		// exec_exit();
	return (1);
}

// void	exec_exit(void)
// {
// 	ft_putstr_fd("exit\n", 2);
// 	ft_error(NULL, 1, NULL);
// }

void	exec_env(t_data *data)
{
	t_list		*current;
	t_env_entry	*entry;

	current = data->env_list;
	while (current != NULL)
	{
		if (current->content)
			entry = (t_env_entry *)current->content;
		if (entry->name && entry->value)
			printf("%s=%s\n", entry->name, entry->value);
		current = current->next;
	}
}

void	exec_pwd(t_data *data)
{
	char	*pwd;

	(void)data;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_error("Malloc FAIL!", 44, NULL);
	// ft_putstr_fd(pwd, STDOUT_FILENO);
	// ft_putstr_fd("\n", STDOUT_FILENO);
	printf("%s\n", pwd);
	free(pwd);
}
