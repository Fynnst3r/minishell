/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/10/30 16:07:40 by ymauk            ###   ########.fr       */
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

//filling the data->env variable with the content of char **env
void	fill_env(t_data *data, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] != NULL)
		i++;
	data->env = (char **) malloc ((i + 1) * (sizeof(char *)));
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
