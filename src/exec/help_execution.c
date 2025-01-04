/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:58:19 by ymauk             #+#    #+#             */
/*   Updated: 2025/01/04 20:32:50 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//wont find path for current dir? try : ./minishell			it wont find it...

void	expand_heredoc(int fd, char *buffer, t_data *data)
{
	char	*exit_status;
	char	*expan;
	t_lexer	lex;

	lex = init_lex(NULL);
	lex.ignore_quotes = true;
	buffer[ft_strlen(buffer) - 1] = 0;
	exit_status = ft_itoa(data->e_status);
	expan = get_exp_str(buffer, exit_status, &lex, data);
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
	const	ssize_t	to_read = sizeof buffer - 2;

	bytes = -1;
	write(STDERR_FILENO, "heredoc> ", 9);
	while (1)
	{
		if (g_signal == SIGINT)
			return (1);
		if (bytes > 0)
		{
			if (buffer[bytes -1] != '\n')
				write(STDERR_FILENO, "\n", 1);
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
		bytes = read(STDIN_FILENO, buffer, to_read);
		while (bytes > 0 && bytes < to_read && buffer[bytes - 1] != '\n')
			bytes += read(STDIN_FILENO, buffer + bytes, to_read - bytes);
		if (bytes == 0)
		{
			write(2, "bash: warning: here-document delimited by end-of-file\n", ft_strlen("bash: warning: here-document delimited by end-of-file\n"));
			break ;
		}
	}
	return (0);
}

void	check_env_builtins(t_data *data, char **cmd)
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

char	**init_env_array(t_list *env_list)
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
