/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:58:19 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/29 17:52:04 by fforster         ###   ########.fr       */
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

	if (!ft_strncmp("./", st_node->argv[0], 2))
		return (ft_strjoin(getcwd(NULL, 0), &st_node->argv[0][1]));
	if (!ft_strncmp("../", st_node->argv[0], 3))
		return (ft_strjoin(getcwd(NULL, 0), &st_node->argv[0][2]));
	if (st_node->argv[0][0] != '/')
		cmd = ft_strjoin("/", st_node->argv[0]);
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
