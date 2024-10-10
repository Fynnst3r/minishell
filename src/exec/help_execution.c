/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:58:19 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/10 16:31:57 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_path(t_data *data, t_exec *st_node)
{
	int		i;
	char	*path;
	char	**mul_p;
	char	*cmd;
	char	*full_p;

	full_p = NULL;
	i = 0;
	cmd = ft_strjoin("/", st_node->argv[0]);
	path = ft_strchr(data->env[4], '/');
	mul_p = ft_split(path, ':');
	while (i++ <= 6)
	{
		full_p = ft_strjoin(mul_p[i], cmd);
		if (access(full_p, X_OK) == 0)
		{
			return (full_p);
		}
		else
			free(full_p);
	}
	free(cmd);
	free_dp(mul_p);
	return (0);
}

void	free_dp(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free (str);
}
