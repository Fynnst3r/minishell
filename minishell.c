/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/11/17 19:09:18 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char**env)
{
	char	*input;
	// t_data	data;

	// data.argc = ac;
	(void)av;
	while (1)
	{
		input = readline("YM_FF_SHELL: ");
		if (!input)
			exit(1); //unfinished
		if (!*input)
			continue ;
		if (input)
		{
			init_garbage_collector();
			start_lexer(input);
			// fake_exec(tokens);
			// free(input);
			delete_trash();
			ft_bzero(get_workers(), sizeof(t_trashman));
			// system("leaks minishell");
		}
		// tokens = NULL;  delete cmd list and maybe other leftover we dont need anymore to reuse for next cmd
	}
	// free_tokens(&tokens);
}

// void	fill_env(t_data *data, char **env)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (env[i] != NULL)
// 		i++;
// 	data->env = (char **)ft_malloc((i + 1) * (sizeof(char *)));
// 	if (!data->env)
// 		printf("error!");
// 	j = 0;
// 	while (j < i)
// 	{
// 		data->env[j] = ft_strdup(env[j]);
// 		j++;
// 	}
// 	data->env[i] = NULL;
// }