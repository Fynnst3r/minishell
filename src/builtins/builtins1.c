/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:46:56 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/10 18:01:44 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtins(t_data *data, char **cmd)
{
	data->argc = 3;
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		exec_echo(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
	{
		exec_pwd(data);
	}
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		exec_env(data);
	// else if (ft_strncmp(cmd[0], "unset", 3) == 0)
	// 	exec_unset(data, cmd);
	// else if (ft_strncmp(cmd[0], "cd", 2) == 0)
	// 	exec_cd(cmd);
	// else if (ft_strncmp(cmd[0], "export", 3) == 0)
	// 	exec_export(data, cmd);
	// else if (ft_strncmp(cmd[0], "exit", 3) == 0)
	// 	exec_exit(cmd);
	else
		return (0);
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
	free(pwd);
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