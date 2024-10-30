/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:46:56 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/30 18:12:50 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtins(t_data *data, char **cmd)
{
	data->argc = 3;
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		exec_echo(cmd);
	// else if (ft_strncmp(cmd[0], "cd", 2) == 0)
	// 	exec_cd(data, cmd);
	// else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
	// 	exec_pwd(data, cmd);
	// else if (ft_strncmp(cmd[0], "export", 3) == 0)
	// 	exec_export(data, cmd);
	// else if (ft_strncmp(cmd[0], "env", 3) == 0)
	// 	exec_env(data, cmd);
	// else if (ft_strncmp(cmd[0], "exit", 3) == 0)
	// 	exec_exit(data, cmd);
	else
		return (0);
	return (1);
}

void	exec_echo(char **cmd)
{
	int	i;
	int	j;
	int	newline;
	int	n_flag;

	i = 1;
	newline = 1;
	while (cmd[i][0] == '-' && cmd[i][1] == 'n')
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
		ft_putstr_fd(cmd[i], 2);
		if (cmd[i + 1] != NULL)
			ft_putstr_fd(" ", 2);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 2);
}
