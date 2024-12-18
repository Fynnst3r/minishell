/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/12/17 15:36:02 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

// static void	signal_handler(int signum, siginfo_t *info, void *uap)
// {
// 	(void)info;
// 	(void)uap;
// 	if (signum == SIGINT)
// {
// 	ft_error("^C\n", 0, NULL);
// 	main(0, NULL, NULL);
// }
// 	if (signum == SIGQUIT)
// 		ft_error("SIGINT", 1, NULL);
// }

void	setting_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));

	// data->sa.sa_flags = SA_SIGINFO;
	// sigemptyset(&data->sa.sa_mask);
	// data->sa.sa_sigaction = signal_handler;
	// if (sigaction(SIGINT, &data->sa, NULL) == -1)
	// 	ft_error("Error: Could not recieve SIGQUIT!", 1, NULL);

	data->origin_stdin = dup(STDIN_FILENO);
	data->origin_stdout = dup(STDOUT_FILENO);
}

void	print_env_list(t_list *env_list)
{
	t_list		*current = env_list;
	t_env_entry	*entry;

	while (current != NULL)
	{
		entry = (t_env_entry *)current->content;
		// entry->name und entry->value sind nun getrennt
		printf("%s=%s\n", entry->name, entry->value);
		current = current->next;
	}
}

int	main(int ac, char **av, char**env)
{
	t_data		data;
	pid_t		pid;
	int			status;
	static char	**statenv;

	data.argc = ac;
	av = NULL;
	statenv = env;
	init_garbage_collector();
	setting_data(&data);
	fill_env_list(&data, env);
	// print_env_list(data.env_list);
	// fill_test_struct(&data);
	while (1)
	{
		data.input = readline(ANSI_BOLD ANSI_CYAN"YM_FF_SHELL: "ANSI_RESET);
		if (!data.input)
			ft_error("exit", 1, NULL);
		if (!*data.input)
			continue ;
		if (data.input)
		{
			if (start_lexer(data.input, &data))
				continue ;
			pid = fork();
			if (pid == -1)
				exit(1);
			if (pid == 0 && data.st_node != NULL)
			{
				start_exec(&data, data.st_node);
			}
			waitpid(pid, &status, 0);
			g_signal = WIFEXITED(status);
			ft_free_tree(data.st_node);
			// free_tokens(&data.token_top);
			// system("leaks minishell");
		}
		// tokens = NULL;  delete cmd list and maybe other leftover we dont need anymore to reuse for next cmd
	}
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
}
