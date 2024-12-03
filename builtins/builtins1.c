/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:46:56 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/03 23:02:10 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtins(t_data *data, char **cmd)
{
	data->argc = 3;
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		exec_echo(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		exec_pwd(data);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		exec_env(data);
	// else if (ft_strncmp(cmd[0], "cd", 3) == 0)
	// 	exec_cd(cmd);
	// else if (ft_strncmp(cmd[0], "export", 7) == 0)
	// 	exec_export(data, cmd);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		exec_exit(cmd);
	else
		return (0);
	return (1);
}

void	exec_exit(char **cmd) // unklar ob das stimmt
{
	if (cmd[1] == NULL)
        exit(0);
}

void	exec_env(t_data *data) // nochmal abchecken ob mein ergebnis korrekt ist. evt müssen umgebungsvariablem vererbt werden
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		ft_putstr_fd(data->env[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}

void	exec_pwd(t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	while (data->env[i] != ft_strnstr(data->env[i], "PWD=/", 5))
	{
		i++;
		path = ft_strchr(data->env[i], '/');
	}
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

// bool	check_n_flag(char **cmd, size_t *i)
// {
// 	size_t	j;
// 	bool	newline;
// 	bool	n_flag;

// 	newline = 1;
// 	if (strnstr)
// 	return (newline);
// }

bool	check_n_flag(char **cmd, size_t *i)
{
	size_t	j;
	bool	newline;
	bool	n_flag;

	newline = 1;
	while (cmd[*i][0] == '-' && cmd[*i][1] == 'n')
	{
		j = 2;
		n_flag = 1;
		while (cmd[*i][j])
		{
			if (cmd[*i][j] != 'n')
			{
				n_flag = 0;
				break ;
			}
			j++;
		}
		if (!n_flag)
			break ;
		newline = 0;
		(*i)++;
	}
	return (newline);
}

size_t	echo_argc(char **cmd, bool newline)
{
	size_t	argc;

	argc = 1;
	while (cmd[argc])
	{
		argc++;
	}
	if (!newline)
		argc -= 1;
	// printf("argc %zu\n", argc);
	return (argc);
}


void	exec_echo(char **cmd)
{
	size_t	i;
	bool	newline;
	size_t	argc;

	i = 1;
	if (cmd[1])
		newline = check_n_flag(cmd, &i);
	if (cmd[i])
		argc = echo_argc(cmd, newline);
	if (!cmd[i])
	{
		ft_putstr_fd("\n", 2);
		return ;
	}
	while (cmd[i] != NULL)
	{
		ft_putstr_fd(cmd[i], 2);
		if (i != argc)
			ft_putstr_fd(" ", 2);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 2);
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