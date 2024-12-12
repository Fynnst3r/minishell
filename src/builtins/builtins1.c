/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:46:56 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/12 17:32:17 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtins(t_data *data, char **cmd)
{
	data->argc = 3;
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		exec_echo(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		exec_pwd(data);
	}
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		exec_env(data);
	else
		return (0);
	// else if (ft_strncmp(cmd[0], "unset", 6) == 0)
	// 	exec_unset(data, cmd);
	// else if (ft_strncmp(cmd[0], "cd", 3) == 0)
	// 	exec_cd(cmd);
	// else if (ft_strncmp(cmd[0], "export", 7) == 0)
	// 	exec_export(data, cmd);
	// else if (ft_strncmp(cmd[0], "exit", 5) == 0)
	// 	exec_exit(cmd);
	return (1);
}

// void	exec_exit(char **cmd) // unklar ob das stimmt
// {
// 	ft_putstr_fd("exit\n", 2);
// 	exit(0);
// }

void	exec_env(t_data *data)
{
	t_list		*current;
	t_env_entry	*entry;

	current = data->env_list;
	while (current != NULL)
	{
		entry = (t_env_entry *)current->content;
		printf("%s=%s\n", entry->name, entry->value);
		current = current->next;
	}
}

void	exec_pwd(t_data *data)
{
	char	*pwd;

	data->argc = 1;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(1);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_free(pwd);
}

void	exec_echo(char **cmd)
{
	int	i;
	int	j;
	int	newline;
	int	n_flag;

	i = 1;
	newline = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 2;
		n_flag = 1;
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
			{
				n_flag = 0;
				break ;
			}
			j++;
		}
		if (!n_flag)
			break ;
		newline = 0;
		i++;
	}
	while (cmd[i] != NULL)
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

// void	exec_cd(char **cmd)
// {
// 	if (cmd[1] == NULL)
// 	{
// 		ft_putstr_fd("\n", 2);
// 		return ;
// 	}
// 	if (chdir(cmd[1]) == -1)
// 		exit(0); // error code noch platzieren so wie bash es macht
// }