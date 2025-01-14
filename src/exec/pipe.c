/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:18:53 by ymauk             #+#    #+#             */
/*   Updated: 2025/01/06 15:37:26 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_pipe(t_pipe *st_node, t_data *data, int last)
{
	if (st_node->type == PIPE)
	{
		check_pipe((t_pipe *)st_node->left, data, 0);
		check_pipe((t_pipe *)st_node->right, data, last);
	}
	else
	{
		run_pipe((t_cmd *)st_node, data, last);
		return ;
	}
	return ;
}

void	run_pipe(t_cmd *st_node, t_data *data, int last)
{
	int		pipefd[2];
	int		status;
	pid_t	pid1;

	if (pipe(pipefd) == -1)
		return ;
	pid1 = ft_fork();
	if (pid1 == -1)
		return ;
	if (pid1 == 0)
		child(st_node, data, last, pipefd);
	while (waitpid(pid1, &status, 0) == -1)
		;
	change_e_stat(data, WEXITSTATUS(status));
	close(pipefd[1]);
	if (last == 0)
		dup2(pipefd[0], STDIN_FILENO);
	else
	{
		close(pipefd[0]);
		dup2(data->origin_stdin, STDIN_FILENO);
	}
}

void	child(t_cmd *st_node, t_data *data, int last, int pipefd[2])
{
	close(pipefd[0]);
	if (last == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
	}
	else
		close(pipefd[1]);
	start_exec(data, (t_cmd *)st_node, true);
	clean_exit(data->e_status, false);
}

	// ft_clean("xd", data, &data->token_top);
	// exit(32);
// clean_exit(data->e_status);
// 	// ft_clean("xd", data, &data->token_top);
// 	// exit(32);