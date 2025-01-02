/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:17:46 by fforster          #+#    #+#             */
/*   Updated: 2025/01/01 16:24:04 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	check_n_flag(char **cmd, size_t *i)
{
	size_t	j;
	bool	n_flag;
	bool	newline;

	newline = 1;
	while (cmd[*i] && cmd[*i][0] == '-' && cmd[*i][1] == 'n')
	{
		j = 2;
		n_flag = 1;
		while (cmd[*i][j])
		{
			if (cmd[*i][j] != 'n')
			{
				n_flag = 0;
				break ;
			}
			j++;
		}
		if (!n_flag)
			break ;
		newline = 0;
		(*i)++;
	}
	return (newline);
}

void	exec_echo(t_data *data, char **cmd)
{
	size_t	i;
	bool	newline;

	i = 1;
	newline = check_n_flag(cmd, &i);
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	data->e_status = 0;
}
