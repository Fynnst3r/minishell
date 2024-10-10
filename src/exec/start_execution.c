/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:24:39 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/09 16:38:12 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	start_exec(t_data *data)
{
	t_shell	elements;
	elements.type = EXECUTE;
	elements.command.execu.argv = (char **)malloc(2 * sizeof(char *));
	if (!elements.command.execu.argv) {
		printf("failed");
	}
	elements.command.execu.argv[0] = strdup("ls");
	elements.command.execu.argv[1] = NULL;
	if (elements.type == EXECUTE)
	{
		exec_exec(&elements, data);
	}
	free(elements.command.execu.argv[0]);
	free(elements.command.execu.argv);
	// else if (elements.type == PIPE)
	// {
	// 	exec_pipe(&elements);
	// }
	// else if (elements.type == RED)
	// {
	// 	exec_redirection();
	// }
	// else if (elements.type == HEREDOC)
	// {
	// 	exec_heredoc(&elements);
	// }
}

void	exec_exec(t_shell *elements, t_data *data)
{
	pid_t	pid;
	data = NULL;

	elements->type = EXECUTE;
	pid = fork();
	if (pid == -1)
		printf("Error!");
	// else if (pid == 0)
	// {
	// 	execve(path_name, argv, env)
	// }
}
