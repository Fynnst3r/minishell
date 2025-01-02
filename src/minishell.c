/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2025/01/02 22:40:45 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

// static long	ft_atol(char *str)
// {
// 	long	res;
// 	int		minus;

// 	minus = 1;
// 	if (*str == '-')
// 	{
// 		minus = -1;
// 		str++;
// 	}
// 	while (*str)
// 	{
// 		res = res * 10;
// 		res = res + *str - '0';
// 		str++;
// 	}
// 	if (res > INTMAX_MAX)
// 		return (2);
// 	return (res * minus);
// }

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
int	main(int ac, char **av, char **env)
{
	t_data		data;

	init_garbage_collector();
	init_data(&data, ac, av, env);
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
