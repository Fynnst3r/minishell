/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/12/10 17:30:29 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

void	setting_data(t_data *data)
{
	data->env_list = NULL;
}

void print_env_list(t_list *env_list)
{
    t_list      *current = env_list;
    t_env_entry *entry;

    while (current != NULL)
    {
        entry = (t_env_entry *)current->content;
        // entry->name und entry->value sind nun getrennt
        printf("%s=%s\n", entry->name, entry->value);
        current = current->next;
    }
}

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
	// fill_env(&data, env);
	fill_env_list(&data, env);
	// print_env_list(data.env_list);
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
