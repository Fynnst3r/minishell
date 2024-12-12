/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:10:15 by fforster          #+#    #+#             */
/*   Updated: 2024/12/12 23:29:53 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	printf("last global errcode %i\n", g_signal);
	if (message)
		printf(ANSI_RED"ERROR: %s\n", message);
	if (errcode != 0)
		printf("ERRORCODE: %i\n"ANSI_RESET, errcode);
	if (toktop)
		free_tokens(toktop);
	if (errcode != 0)
	{
		delete_trash();
		ft_bzero(get_workers(), sizeof(t_trashman));
		exit(errcode);
	}
}

int	ft_free_tree(t_cmd *st_node)
{
	t_exec	*free_exec;
	t_red	*free_red;
	// t_herd	*free_herd;
	t_pipe	*free_pipe;
	// static int count = 0;
	
	// count++;
	// printf("count %i\n", count);
	if (st_node->type == EXECUTE)
		return (free_exec = (t_exec *)st_node, free_dp(free_exec->argv),
			ft_free(free_exec), free_exec = NULL, 0);
	if (st_node->type == RED)
		return (free_red = (t_red *)st_node, ft_free_tree(free_red->cmd),
			ft_free(free_red), free_red = NULL, 0);
	if (st_node->type == PIPE)
	{
		free_pipe = (t_pipe *)st_node;
		if (free_pipe->left == PIPE)
			ft_free_tree((t_cmd *)free_pipe->left);
		return (ft_free_tree((t_cmd *)free_pipe->right), ft_free(free_pipe), 0);
	}
	printf("??heredoc not implemented??\n");
	return (1);
}
