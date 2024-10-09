/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:24:39 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/08 15:32:47 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	start_exec(void)
{
	t_shell	elements;

	if (elements.type == PIPE)
	{
		exec_pipe(&elements);
	}
	else if (elements.type == RED)
	{
		exec_redirection();
	}
	else if (elements.type == HEREDOC)
	{
		exec_heredoc(&elements);
	}
	else if (elements.type == EXECUTE)
	{
		exec_exec(&elements);
	}
}

void	exec_pipe(t_shell *elements)
{
	int	pipefd[2];
	int	pid1;

	pid1 = fork();
	if (pipe(pipefd) == -1)
		error_handling(elements);
	if (pid1 == -1)
		error_handling(elements);
	

}
