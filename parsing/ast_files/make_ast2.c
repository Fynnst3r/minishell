/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:15:30 by fforster          #+#    #+#             */
/*   Updated: 2024/11/30 22:39:36 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_pipe	*find_last_pipe(t_pipe *p)
{
	t_pipe	*last;

	if (!p)
		return (NULL);
	last = p;
	while (last->left && last->left->type == PIPE)
		last = (t_pipe *)last->left;
	return (last);
}

size_t	count_pipes(t_token *t)
{
	t_token	*tmp;
	size_t	count_p;

	tmp = t;
	count_p = 0;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			count_p++;
		tmp = tmp->next;
	}
	return (count_p);
}

void	new_pipe_node(t_pipe **ptop)
{
	t_pipe	*pnew;
	t_pipe	*last_pipe;

	if (!ptop)
		return ;
	pnew = ft_calloc(sizeof(t_pipe), 1);
 	pnew->type = PIPE;
	if (*ptop == NULL)
	{
		*ptop = pnew;
		return ;
	}
	last_pipe = find_last_pipe(*ptop);
	last_pipe->left = (t_cmd *)pnew;
}

void	loop_pipes(t_token **toktop, t_pipe **pipetop, size_t p_count)
{
	t_pipe	*p;

	p = *pipetop;
	p_count--;
	if (p->left && p->left->type == PIPE && p_count != 0)
		loop_pipes(toktop, (t_pipe **)&p->left, p_count);
	p->left = (t_cmd *)check_cmd_type(*toktop);
	if (p_count == 0)
		p->left = move_tok_to_curr_pipe(toktop, p_count);
	else
		p->left = move_tok_to_curr_pipe(toktop, p_count);
}

t_cmd	*move_tok_to_curr_pipe(t_token **toktop, size_t p_count)
{
	t_token	*tmp;
	t_cmd	*cmd;

	tmp = *toktop;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			p_count--;
		if (p_count <= 0)
			break ;
	}
	tmp = tmp->next;
	if (tmp && tmp->type == WORD)
		cmd = check_cmd_type(tmp);
	// else
		// syntax error?
	return (cmd);
}

// t_red	*create_redir_node(t_token *tmp, int start_id)
// {
// 	t_red	*red;

// 	red = ft_calloc(sizeof(t_red), 1);
// 	while (tmp || tmp->type != T_PIPE)
// 	{
// 		if (tmp->type == T_OUT)
// 	}
// }

t_cmd	*check_cmd_type(t_token *tmp)
{
	t_cmd	*cmd;

	cmd = NULL;
	// print_token_data(tmp);
	while (tmp)
	{
		if (tmp->type == T_OUT || tmp->type == T_APP || tmp->type == T_IN)
			cmd = create_redir_node(tmp, tmp->id);
	}
	return (cmd);
}

t_pipe	*start_pipe_ast(t_token **toktop, size_t p_count)
{
	t_pipe	*pipetop;

	pipetop = NULL;
	while (p_count != 0)
	{
		new_pipe_node(&pipetop);
		p_count--;
	}
	loop_pipes(toktop, &pipetop, count_pipes(*toktop));
	return (pipetop);
}

void	make_ast2(t_data *data, t_token **toktop)
{
	size_t	pipe_count;

	pipe_count = count_pipes(*toktop);
	if (pipe_count != 0)
		data->st_node = (t_cmd *)start_pipe_ast(toktop, pipe_count);
}
