/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:24:39 by ymauk             #+#    #+#             */
/*   Updated: 2025/01/04 20:31:21 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	start_exec(t_data *data, t_cmd *cmd)
{
	if (cmd->type == EXECUTE)
	{
		exec_execu((t_exec *)cmd, data);
	}
	if (cmd->type == PIPE)
	{
		exec_pipe((t_pipe *)cmd, data);
	}
	if (cmd->type == RED)
	{
		exec_red((t_red *)cmd, data);
	}
	if (cmd->type == HEREDOC)
	{
		exec_heredoc((t_herd *)cmd, data);
	}
}

void	exec_heredoc(t_herd *st_node, t_data *data)
{
	int		fd;
	pid_t	pid;
	int		status;

	prepare_signal(data, signal_handler2);
	pid = ft_fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		fd = open("heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			clean_exit(1, true);
		if (write_in_file(fd, (t_herd *)st_node, data) == 1)
			return (unlink("heredoc.txt"), close(fd), clean_exit(0, false));
		close (fd);
		fd = open("heredoc.txt", O_RDONLY);
		if (dup2(fd, STDIN_FILENO) == -1)
			clean_exit(1, true);
		close(fd);
		if (st_node->cmd->type == RED)
			start_exec(data, st_node->cmd);
		else if (st_node->cmd->type == EXECUTE)
			exec_execu((t_exec *)st_node->cmd, data);
		unlink("heredoc.txt");
		clean_exit(0, false);
	}
	while (waitpid(pid, &status, 0) == -1)
		;
	prepare_signal(data, signal_handler);
	data->e_status = WEXITSTATUS(status);
	extra_exec(data, data->st_node);
}

void	exec_red(t_red *st_node, t_data *data)
{
	int		fd_orig;
	int		saved_fd;
	pid_t	pid;
	int		status;

	prepare_signal(data, signal_handler2);
	pid = ft_fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (st_node->fd != STDIN_FILENO)
			fd_orig = open(st_node->file, st_node->mode, 0644);
		else
			fd_orig = open(st_node->file, st_node->mode);
		saved_fd = dup(st_node->fd);
		if (fd_orig == -1)
			clean_exit(1, true);
		if (dup2(fd_orig, st_node->fd) == -1)
			clean_exit(1, true);
		close(fd_orig);
		if (st_node->cmd->type == RED)
			start_exec(data, st_node->cmd);
		else if (st_node->cmd->type == EXECUTE)
			exec_execu((t_exec *)st_node->cmd, data);
		if (st_node->fd != STDIN_FILENO)
			dup2(saved_fd, STDOUT_FILENO);
		else
			dup2(saved_fd, STDIN_FILENO);
		close(saved_fd);
		clean_exit(0, false);
	}
	while (waitpid(pid, &status, 0) == -1)
		;
	prepare_signal(data, signal_handler);
	data->e_status = WEXITSTATUS(status);
	extra_exec(data, data->st_node);
}

void	exec_execu(t_exec *st_node, t_data *data)
{
	pid_t		pid;
	int			status;

	if (check_builtins(data, st_node->argv) == 0)
	{
		prepare_signal(data, signal_handler2);
		pid = ft_fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			data->cmd_path = find_path(data, st_node);
			if (data->cmd_path == 0)
				clean_exit(127, false);
			data->env = env_list_to_array(data);
			if (execve(data->cmd_path, st_node->argv, data->env) == -1)
				clean_exit(127, true);
		}
		while (waitpid(pid, &status, 0) == -1)
			;
		prepare_signal(data, signal_handler);
		data->e_status = WEXITSTATUS(status);
	}
}

void	exec_pipe(t_pipe *st_node, t_data *data)
{
	check_pipe((t_pipe *)st_node->left, data, 0);
	dup2(data->origin_stdout, STDOUT_FILENO);
	run_pipe((t_cmd *)st_node->right, data, 1);
}
	// printf("pipe done\n");
	// exit(0);
