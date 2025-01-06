/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens_and_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:01:44 by fforster          #+#    #+#             */
/*   Updated: 2025/01/04 22:03:54 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tokens(t_token **t)
{
	t_token	*tmp;

	if (!*t)
		return ;
	tmp = *t;
	while (tmp->next != NULL)
	{
		ft_free(tmp->str);
		tmp->str = NULL;
		tmp = tmp->next;
		ft_free(tmp->previous);
	}
	ft_free(tmp);
	tmp = NULL;
	*t = NULL;
	t = NULL;
}

int	ft_free_herd(t_cmd *node)
{
	t_herd	*free_herd;

	if (!node)
		return (1);
	if (node->type == HEREDOC)
	{
		free_herd = (t_herd *)node;
		ft_free_tree(free_herd->cmd);
		ft_free(free_herd->del);
		ft_free(free_herd->cmd);
		free_herd->del = NULL;
		free_herd->cmd = NULL;
		free_herd = NULL;
		return (1);
	}
	return (1);
}

int	ft_free_tree(t_cmd *st_node)
{
	t_exec	*free_exec;
	t_red	*free_red;
	t_pipe	*free_pipe;

	if (!st_node)
		return (1);
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
	if (st_node->type == HEREDOC)
		ft_free_herd(st_node);
	return (1);
}
		// printf("%s%d freed left pipe\n", __FILE__, __LINE__);
	// static int count = 0;
	// count++;
	// printf("count %i\n", count);
	// printf("type %i\n", st_node->type);
