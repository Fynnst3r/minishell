/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:59:04 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/10 15:37:46 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	fill_env_list(t_data *data, char **env)
{
	int		i;
	t_list	*new_node;

	data->env_list = NULL;
	i = 0;
	while (env[i])
	{
		new_node = ft_lstnew(ft_strdup(env[i]));
		if (!new_node)
		{
			exit(1);
		}
		ft_lstadd_back(&data->env_list, new_node);
		i++;
	}
}
