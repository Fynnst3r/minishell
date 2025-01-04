/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:49:33 by fforster          #+#    #+#             */
/*   Updated: 2025/01/04 20:43:04 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_relative_path(char *path)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;

	if (!ft_strncmp("./", path, 2))
	{
		tmp = getcwd(NULL, 0);
		ret = ft_strjoin(tmp, &path[1]);
		free(tmp);
		tmp = NULL;
		return (ret);
	}
	if (!ft_strncmp("../", path, 3))
	{
		tmp = getcwd(NULL, 0);
		tmp2 = ft_strjoin(tmp, "/");
		ret = ft_strjoin(tmp2, path);
		free(tmp);
		free(tmp2);
		tmp = NULL;
		tmp2 = NULL;
		return (ret);
	}
	return (NULL);
}

static char	**get_env_path(t_data *data)
{
	char		*path;
	char		**mul;
	t_list		*current;
	t_env_entry	*entry;

	current = data->env_list;
	path = NULL;
	while (current != NULL)
	{
		entry = (t_env_entry *)current->content;
		if (ft_strncmp(entry->name, "PATH", 4) == 0 && entry->value != NULL)
		{
			path = entry->value;
			break ;
		}
		current = current->next;
	}
	if (!path)
		return (NULL);
	mul = ft_split(path, ':');
	return (mul);
}

static char	*find_path_helper(t_data *data, t_exec *st_node, char *cmd)
{
	int		i;
	char	**mul_p;
	char	*full_p;

	mul_p = get_env_path(data);
	i = -1;
	while (mul_p && mul_p[++i] != NULL)
	{
		full_p = ft_strjoin(mul_p[i], cmd);
		if (access(full_p, X_OK) == 0)
		{
			ft_free(cmd);
			free_dp(mul_p);
			return (full_p);
		}
		else
		{
			ft_free(full_p);
		}
	}
	data->e_status = 127;
	print_error("Command not found: ", st_node->argv[0]);
	ft_free(cmd);
	free_dp(mul_p);
	return (0);
}

char	*find_path(t_data *data, t_exec *st_node)
{
	char	*cmd;

	if (!ft_strncmp("./", st_node->argv[0], 2)
		|| !ft_strncmp("../", st_node->argv[0], 3))
		return (get_relative_path(st_node->argv[0]));
	if (st_node->argv[0][0] != '/')
		cmd = ft_strjoin("/", st_node->argv[0]);
	else
	{
		if (access(st_node->argv[0], X_OK) != 0)
			return (data->e_status = 127, perror("YM_FF_SHELL"), NULL);
		else
			return (st_node->argv[0]);
	}
	return (find_path_helper(data, st_node, cmd));
}

void	free_dp(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str && str[i] != NULL)
	{
		ft_free(str[i]);
		i++;
	}
	ft_free(str);
}
