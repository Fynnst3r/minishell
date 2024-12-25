/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:58:19 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/25 22:04:58 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//wont find path for current dir? try : ./minishell			it wont find it...
char	*find_path(t_data *data, t_exec *st_node)
{
	int		i;
	char	**mul_p;
	char	*cmd;
	char	*full_p;

	if (st_node->argv[0][0] != '/')
	{
		cmd = ft_strjoin("/", st_node->argv[0]);
	}
	else
	{
		if (access(st_node->argv[0], X_OK) != 0)
			return (perror("YM_FF_SHELL"), NULL);
		else
			return (st_node->argv[0]);
	}
	mul_p = find_path_help(data);
	i = -1;
	while (mul_p && mul_p[++i] != NULL)
	{
		full_p = ft_strjoin(mul_p[i], cmd);
		if (access(full_p, X_OK) == 0)
		{
			ft_free(cmd);
			free_dp(mul_p);
			return (full_p);
		}
		else
		{
			ft_free(full_p);
		}
	}
	perror("YM_FF_SHELL");
	ft_free(cmd);
	free_dp(mul_p);
	return (0);
}

char	**find_path_help(t_data *data)
{
	char		*path;
	char		**mul;
	t_list		*current;
	t_env_entry	*entry;

	current = data->env_list;
	path = NULL;
	while (current != NULL)
	{
		entry = (t_env_entry *)current->content;
		if (ft_strncmp(entry->name, "PATH", 4) == 0 && entry->value != NULL)
		{
			path = entry->value;
			break ;
		}
		current = current->next;
	}
	if (!path)
		return (NULL);
	mul = ft_split(path, ':');
	return (mul);
}

void	free_dp(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str && str[i] != NULL)
	{
		ft_free(str[i]);
		i++;
	}
	ft_free(str);
}

void	expand_heredoc(int fd, char *buffer, t_data *data)
{
	char	*exit_status;
	char	*expan;
	t_lexer	lex;

	lex = init_lex(NULL);
	lex.ignore_quotes = true;
	buffer[ft_strlen(buffer) - 1] = 0;
	exit_status = ft_itoa(g_signal);
	expan = get_exp_str(buffer, exit_status, &lex, data->env_list);
	if (expan[0] == 0)
		write(fd, "\n", 1);
	else
	{
		write(fd, expan, ft_strlen(expan));
		write(fd, "\n", 1);
	}
	ft_free(expan);
	ft_free(exit_status);
}

int	write_in_file(int fd, t_herd *st_node, t_data *data)
{
	ssize_t	bytes;
	char	buffer[1024];

	bytes = -1;
	write(STDERR_FILENO, "heredoc> ", 9);
	while (1)
	{
		if (bytes > 0)
		{
			buffer[bytes - 1] = '\n';
			buffer[bytes] = '\0';
			if (!ft_strncmp(buffer, st_node->del, ft_strlen(st_node->del)))
				break ;
			write(STDERR_FILENO, "heredoc> ", 9);
			if (ft_strchr(buffer, '\'')
				|| ft_strchr(buffer, '\"') || ft_strchr(buffer, '$'))
				expand_heredoc(fd, buffer, data);
			else
				write(fd, buffer, bytes);
		}
		bytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	}
	return (fd);
}
