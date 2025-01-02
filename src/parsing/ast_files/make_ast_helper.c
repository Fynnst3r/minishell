/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:25:40 by fforster          #+#    #+#             */
/*   Updated: 2025/01/02 20:26:16 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	scan_cmd_type(t_token *t)
{
	int	ret;

	ret = EXECUTE;
	while (t)
	{
		if (t->type == PATH)
		{
			if (t->previous->type != T_HERE && ret != HEREDOC)
				ret = RED;
			else
				ret = HEREDOC;
		}
		if (t->type == T_PIPE)
			return (PIPE);
		t = t->next;
	}
	return (ret);
}

void	set_red_type(t_red **red, int type)
{
	if (type == T_OUT)
	{
		(*red)->fd = STDOUT_FILENO;
		(*red)->mode = O_WRONLY | O_CREAT | O_TRUNC;
	}
	if (type == T_APP)
	{
		(*red)->fd = STDOUT_FILENO;
		(*red)->mode = O_WRONLY | O_CREAT | O_APPEND;
	}
	if (type == T_IN)
	{
		(*red)->fd = STDIN_FILENO;
		(*red)->mode = O_RDONLY;
	}
}

t_red	*find_last_red(t_red *top)
{
	while (top->cmd != NULL)
	{
		top = (t_red *)top->cmd;
	}
	return (top);
}

t_token	*scan_last_heredoc(t_token *t, t_herd *herd)
{
	t_token	*last;
	t_token	*tmp;

	last = NULL;
	tmp = t;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			break ;
		if (tmp->type == PATH && tmp->previous->type == T_HERE)
			last = tmp;
		tmp = tmp->next;
	}
	while (t)
	{
		if (t->type == T_HERE)
			herd->last_redir = true;
		if (t->type == T_IN)
			herd->last_redir = false;
		t = t->next;
	}
	return (last);
}

size_t	count_cmd_args(t_token *tmp)
{
	size_t	count;

	count = 0;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->str != NULL)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
