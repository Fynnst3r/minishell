/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/12/10 15:46:44 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_data		data;
	pid_t		pid;
	int			status;
	const char	*prompt;

	prompt = "YM_FF_SHELL: ";
	data.argc = ac;
	av = NULL;
	// setting_data(&data);
	fill_env(&data, env);
	fill_env_list(&data, env);
	fill_test_struct(&data);
	data.origin_stdin = dup(STDIN_FILENO);
	data.origin_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		data.input = readline(prompt);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			start_exec(&data, data.st_node);
		}
		waitpid(pid, &status, 0);
		g_signal = WIFEXITED(status);
	}
	return (0);
}

// void	setting_data(t_data *data)
// {
// 	data->env_list = NULL;
// }

// #include <stdio.h> // Für printf
// #include "libft.h" // Falls t_list dort definiert ist

// void print_env_list(t_list *env_list)
// {
//     t_list *current = env_list;

//     while (current != NULL)
//     {
//         // Da content ein char* ist, kann es direkt als String ausgegeben werden
//         printf("%s\n", (char *)current->content);
//         current = current->next;
//     }
// }
