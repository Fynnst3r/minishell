/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:58:19 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/12 23:17:19 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_path(t_data *data, t_exec *st_node)
{
	int		i;
	char	**mul_p;
	char	*cmd;
	char	*full_p;

	cmd = ft_strjoin("/", st_node->argv[0]);
	mul_p = find_path_help(data);
	i = -1;
	while (mul_p[++i] != NULL)
	{
		full_p = ft_strjoin(mul_p[i], cmd);
		if (access(full_p, X_OK) == 0)
		{
			free(cmd);
			free_dp(mul_p);
			return (full_p);
		}
		else
			free(full_p);
	}
	free(cmd);
	free_dp(mul_p);
	return (0);
}

char	**find_path_help(t_data *data)
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

void	free_dp(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_free(str[i]);
		str[i] = NULL;
		i++;
	}
	ft_free(str);
	str = NULL;
}

int	write_in_file(int fd, t_herd *st_node)
{
	ssize_t	bytes;
	char	buffer[1024];

	while (1)
	{
		write(STDERR_FILENO, "heredoc> ", 9);
		bytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			if (ft_strncmp(buffer, st_node->del, 3) == 0)
			{
				break ;
			}
			write (fd, buffer, bytes);
		}
	}
	return (fd);
}
