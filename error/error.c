/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:10:15 by fforster          #+#    #+#             */
/*   Updated: 2024/11/29 16:51:40 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token **t)
{
	t_token	*tmp;
	int		count;

	count = 0;
	if (!*t)
		return ;
	// printf("free start\n");
	tmp = *t;
	while (tmp->next != NULL)
	{
		// printf("id %i\n", tmp->id);
		ft_free(tmp->str);
		tmp->str = NULL;
		tmp = tmp->next;
		ft_free(tmp->previous);
	}
	// printf("id %i\n", tmp->id);
	// printf("free end\n");
	ft_free(tmp);
	tmp = NULL;
	*t = NULL;
	t = NULL;
}

void	ft_error(char *message, int errcode, t_token **toktop)
{
	if (message)
		printf(ANSI_RED"ERROR: %s\n", message);
	printf("ERRORCODE: %i\n"ANSI_RESET, errcode);
	free_tokens(toktop);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	if (errcode != 0)
		exit(errcode);
}
