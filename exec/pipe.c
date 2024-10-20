/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:18:53 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/15 10:57:39 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_left(t_exec *st_node_left, int pipefd[2], t_data *data)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_execu(st_node_left, data);
	}
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
}

void	pipe_right(t_exec *st_node_right, int pipefd[2], t_data *data)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exec_execu(st_node_right, data);
	}
	close(pipefd[0]);
	waitpid(pid2, NULL, 0);
}
