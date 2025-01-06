/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:10:15 by fforster          #+#    #+#             */
/*   Updated: 2025/01/04 22:01:59 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_exit(int errnum, bool printperror)
{
	if (printperror)
		perror("YM_FF_SHELL");
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(errnum);
}

void	ft_clean(char *message, t_data *data, t_token **toktop)
{
	if (message)
		printf("YM_FF_SHELL: %s\n", message);
	if (data)
	{
		if (data->input)
			ft_free(data->input);
		data->input = NULL;
		if (data->st_node)
			ft_free_tree(data->st_node);
		data->st_node = NULL;
	}
	if (toktop)
		free_tokens(toktop);
}

void	ft_error(char *message, int errcode, t_token **toktop)
{
	if (message)
		printf("%s\n", message);
	if (toktop)
		free_tokens(toktop);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(errcode);
}
