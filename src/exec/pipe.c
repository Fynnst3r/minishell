/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:18:53 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/29 15:14:20 by ymauk            ###   ########.fr       */
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
	pid_t	pid1;

	if (pipe(pipefd) == -1)
		exit(-1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
		child(st_node, data, last, pipefd);
	if (pid1 > 0)
	{
		waitpid(pid1, NULL, 0);
		close(pipefd[1]);
		if (last == 0)
			dup2(pipefd[0], STDIN_FILENO);
		else
		{
			close(pipefd[0]);
			dup2(data->origin_stdin, STDIN_FILENO);
		}
	}
	return ;
}

void	child(t_cmd *st_node, t_data *data, int last, int pipefd[2])
{
	data->argc = 4;
	close(pipefd[0]);
	if (last == 0)
		dup2(pipefd[1], STDOUT_FILENO);
	else
	{
		close(pipefd[1]);
	}
	start_exec(data, (t_cmd *)st_node);
}
