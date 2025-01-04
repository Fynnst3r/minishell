/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2025/01/04 18:43:38 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

void	check_exit(t_cmd *cmd)
{
	t_exec		*exec;
	size_t		i;
	int			exit_num;

	i = 0;
	exit_num = 0;
	if (cmd->type == EXECUTE)
	{
		exec = (t_exec *)cmd;
		while (exec->argv[i])
			i++;
		if (i > 1)
		{
			exit_num = (ft_atoi(exec->argv[1]));
			while (exit_num < 0 && exit_num < 256)
				exit_num += 256;
		}
		if (ft_strncmp(exec->argv[0], "exit", 5) == 0)
		{
			printf("exit\n");
			ft_error(NULL, exit_num, NULL);
		}
	}
}

static void	init_data(t_data *data, int ac, char **av, char **env)
{
	ft_bzero(data, sizeof(t_data));
	(void)av;
	data->argc = ac;
	prepare_signal(data, signal_handler);
	fill_env_list(data, env);
	data->origin_stdin = dup(STDIN_FILENO);
	data->origin_stdout = dup(STDOUT_FILENO);
}

// cat << end < 1				it should use 1 as input not heredoc
// cat < 1 <<end				it should use heredoc as input not 1
//env[0] = 0;
int	main(int ac, char **av, char **env)
{
	t_data		data;

	init_garbage_collector();
	init_data(&data, ac, av, env);
	while (1)
	{
		data.input = readline("YM_FF_SHELL: ");
		g_signal = 0;
		if (!data.input)
			ft_error("exit", 0, NULL);
		if (!*data.input)
			continue ;
		if (data.input)
		{
			if (start_lexer(data.input, &data))
				continue ;
			check_exit(data.st_node);
			if (data.st_node != NULL)
				start_exec(&data, data.st_node);
		}
		ft_clean(NULL, &data, &data.token_top);
	}
}
// printf("%d\n", g_signal);
// free(data.input);
// system("leaks minishell");
