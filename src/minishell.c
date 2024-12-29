/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/12/29 18:28:02 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

// static void	signal_handler(int signum, siginfo_t *info, void *uap)
// {
// 	(void)info;
// 	(void)uap;
// 	if (signum == SIGINT)
// 	{
// 		ft_error("^C\n", 0, NULL);
// 		main(0, NULL, NULL);
// 	}
// 	if (signum == SIGQUIT)
// 		ft_error("SIGINT", 1, NULL);
// }

static void	init_data(t_data *data, int ac, char **av, char **env)
{
	ft_bzero(data, sizeof(t_data));
	(void)av;
	data->argc = ac;

	// data->sa.sa_flags = SA_SIGINFO;
	// sigemptyset(&data->sa.sa_mask);
	// data->sa.sa_sigaction = signal_handler;
	// if (sigaction(SIGINT, &data->sa, NULL) == -1)
	// 	ft_error("Error: Could not recieve SIGQUIT!", 1, NULL);
	fill_env_list(data, env);
	data->origin_stdin = dup(STDIN_FILENO);
	data->origin_stdout = dup(STDOUT_FILENO);
}

void	check_exit(t_cmd *cmd)
{
	t_exec	*exec;
	size_t	i;

	i = 0;
	if (cmd->type == EXECUTE)
	{
		exec = (t_exec *)cmd;
		while (exec->argv[i])
			i++;
		if (i > 1)
			return ;
		if (ft_strncmp(exec->argv[0], "exit", 5) == 0)
		{
			printf("exit\n");
			ft_error(NULL, 1, NULL);
		}
	}
}

// cat << end < 1				it should use 1 as input not heredoc
int	main(int ac, char **av, char **env)
{
	t_data		data;

	init_garbage_collector();
	init_data(&data, ac, av, env);
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
			check_exit(data.st_node);
			if (data.st_node != NULL)
			{
				start_exec(&data, data.st_node);
			}
			ft_free_tree(data.st_node);
			free_tokens(&data.token_top);
			free(data.input);
			// system("leaks minishell");
		}
	}
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
}
