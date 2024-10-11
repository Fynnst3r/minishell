/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/10/11 17:29:35 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data		data;
	const char	*prompt;

	prompt = "YM_FF_SHELL: ";
	data.argc = ac;
	av = NULL;
	// setting_data(&data);
	fill_env(&data, env);
	fill_test_struct(&data);
	while (1)
	{
		data.input = readline(prompt);
		start_exec(&data);
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
