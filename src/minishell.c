/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/12/10 19:13:02 by fforster         ###   ########.fr       */
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
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i] != NULL)
		i++;
	data->env = (char **)ft_malloc((i + 1) * (sizeof(char *)));
	if (!data->env)
		printf("error!");
	j = 0;
	while (j < i)
	{
		data->env[j] = ft_strdup(env[j]);
		j++;
	}
	data->env[i] = NULL;
}
int	main(int ac, char **av, char**env)
{
	t_data	data;
	pid_t	pid;
	int		status;

	data.argc = ac;
	av = NULL;
	// setting_data(&data);
	// fill_env(&data, env);
	fill_env_list(&data, env);
	data.st_node = NULL;
	// print_env_list(data.env_list);
	fill_test_struct(&data);
	data.origin_stdin = dup(STDIN_FILENO);
	data.origin_stdout = dup(STDOUT_FILENO);
	data.exit_status = 0; //needs to be 0 at start, must be changed after each input
	while (1)
	{
		data.input = readline(ANSI_BOLD ANSI_CYAN"YM_FF_SHELL: "ANSI_RESET);
		if (!data.input)
			exit(1); //unfinished needs to free potential AST
		if (!*data.input)
			continue ;
		if (data.input)
		{
			init_garbage_collector();
			if (start_lexer(data.input, &data))
				continue ;
			if (pid == -1)
				exit(1);
			if (pid == 0 && data.st_node != NULL)
			{
				start_exec(&data, data.st_node);
			}
			waitpid(pid, &status, 0);
			g_signal = WIFEXITED(status);
			delete_trash();
			ft_bzero(get_workers(), sizeof(t_trashman));
			// system("leaks minishell");
		}
		// tokens = NULL;  delete cmd list and maybe other leftover we dont need anymore to reuse for next cmd
	}
	// free_tokens(&tokens);
}
