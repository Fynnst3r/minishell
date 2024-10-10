/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:24:39 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/10 16:34:32 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_test_struct(t_data *data)
{
	 t_exec *exec_node = malloc(sizeof(t_exec));
    exec_node->type = EXECUTE;

    // Argumente für das Kommando 'ls' setzen
    exec_node->argv = malloc(2 * sizeof(char *));
    if (!exec_node->argv)
    {
        perror("malloc failed");
        free(exec_node);
        exit(EXIT_FAILURE);
    }
    exec_node->argv[0] = strdup("ls");
    if (!exec_node->argv[0])
    {
        perror("strdup failed");
        free(exec_node->argv);
        free(exec_node);
        exit(EXIT_FAILURE);
    }
    exec_node->argv[1] = NULL;

    // Den exec_node zum st_node hinzufügen
    data->st_node = (t_cmd *)exec_node;
}

void	start_exec(t_data *data)
{
	fill_test_struct(data);
	if (data->st_node->type == EXECUTE)
	{
		t_exec *st_node = (t_exec *)data->st_node;
		exec_execu(st_node, data);
		// exec_execu(argv, data);
	}
}

void	exec_execu(t_exec *st_node, t_data *data)
{
	pid_t	pid;
	char	*cmd_path;

	cmd_path = find_path(data, st_node);
	pid = fork();
	if (pid == -1)
		printf("Error!");
	else if (pid == 0)
	{
		if (execve(cmd_path, st_node->argv, data->env) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		// Elternprozess wartet auf den Kindprozess
		int status;
		waitpid(pid, &status, 0);
	}
	free (cmd_path);
}
