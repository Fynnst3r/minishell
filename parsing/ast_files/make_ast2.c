/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:15:30 by fforster          #+#    #+#             */
/*   Updated: 2024/12/03 21:30:41 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_exec(t_exec *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->argv[i])
	{
		printf("arg[%zu] = %s\n", i, cmd->argv[i]);
		i++;
	}
}

// t_pipe	*find_last_pipe(t_pipe *p)
// {
// 	t_pipe	*last;

// 	if (!p)
// 		return (NULL);
// 	last = p;
// 	while (last->left && last->left->type == PIPE)
// 		last = (t_pipe *)last->left;
// 	return (last);
// }

// size_t	count_pipes(t_token *t)
// {
// 	t_token	*tmp;
// 	size_t	count_p;

// 	tmp = t;
// 	count_p = 0;
// 	while (tmp)
// 	{
// 		if (tmp->type == T_PIPE)
// 			count_p++;
// 		tmp = tmp->next;
// 	}
// 	return (count_p);
// }

// void	new_pipe_node(t_pipe **ptop)
// {
// 	t_pipe	*pnew;
// 	t_pipe	*last_pipe;

// 	if (!ptop)
// 		return ;
// 	pnew = ft_calloc(sizeof(t_pipe), 1);
//  	pnew->type = PIPE;
// 	if (*ptop == NULL)
// 	{
// 		*ptop = pnew;
// 		return ;
// 	}
// 	last_pipe = find_last_pipe(*ptop);
// 	last_pipe->left = (t_cmd *)pnew;
// }

// void	loop_pipes(t_token **toktop, t_pipe **pipetop, size_t p_count)
// {
// 	t_pipe	*p;

// 	p = *pipetop;
// 	p_count--;
// 	if (p->left && p->left->type == PIPE && p_count != 0)
// 		loop_pipes(toktop, (t_pipe **)&p->left, p_count);
// 	// p->left = (t_cmd *)check_cmd_type(*toktop);
// 	if (p_count == 0)
// 		p->left = move_tok_to_curr_pipe(toktop, p_count);
// 	else
// 		p->left = move_tok_to_curr_pipe(toktop, p_count);
// }

// t_cmd	*move_tok_to_curr_pipe(t_token **toktop, size_t p_count)
// {
// 	t_token	*tmp;
// 	t_cmd	*cmd;

// 	tmp = *toktop;
// 	while (tmp)
// 	{
// 		if (tmp->type == T_PIPE)
// 			p_count--;
// 		if (p_count <= 0)
// 			break ;
// 	}
// 	tmp = tmp->next;
// 	if (tmp && tmp->type == WORD)
// 		// cmd = check_cmd_type(tmp);
// 	// else
// 		// syntax error?
// 	return (cmd);
// }

// t_red	*create_redir_node(t_token *tmp, int start_id)
// {
// 	t_red	*red;

// 	red = ft_calloc(sizeof(t_red), 1);
// 	while (tmp || tmp->type != T_PIPE)
// 	{
// 		if (tmp->type == T_OUT)
// 	}
// }

// t_cmd	*check_cmd_type(t_token *tmp)
// {
// 	t_cmd	*cmd;

// 	cmd = NULL;
// 	// print_token_data(tmp);
// 	while (tmp)
// 	{
// 		if (tmp->type == T_OUT || tmp->type == T_APP || tmp->type == T_IN)
// 			cmd = create_redir_node(tmp, tmp->id);
// 	}
// 	return (cmd);
// }

// t_pipe	*start_pipe_ast(t_token **toktop, size_t p_count)
// {
// 	t_pipe	*pipetop;

// 	pipetop = NULL;
// 	while (p_count != 0)
// 	{
// 		new_pipe_node(&pipetop);
// 		p_count--;
// 	}
// 	loop_pipes(toktop, &pipetop, count_pipes(*toktop));
// 	return (pipetop);
// }

int	scan_cmd_type(t_token *t)
{
	while (t)
	{
		if (t->type == PATH)
		{
			if (t->previous->type != T_HERE)
				return (RED);
			else
				return (HEREDOC);
		}
		if (t->type == T_PIPE)
			return (PIPE);
		t = t->next;
	}
	return (EXECUTE);
}

t_exec	*make_cmd_node(t_token *t)
{
	t_exec	*exec;
	size_t	count;
	t_token	*tmp;

	count = 0;
	tmp = t;
	exec = ft_calloc(sizeof(t_exec), 1);
	exec->type = EXECUTE;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->str != NULL)
			count++;
		tmp = tmp->next;
	}
	exec->argv = ft_calloc(sizeof(char *), count + 1);
	tmp = t;
	count = 0;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->str != NULL)
		{
			exec->argv[count] = tmp->str;
			// printf("node str %s\n", exec->argv[count]);
			count++;
			// ft_free(tmp->str);? will get freed after ast creation.
		}
		tmp = tmp->next;
	}
	return (exec);
}

static void	set_red_type(t_red **red, int type)
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

t_red	*make_red_node(t_token *t)
{
	t_red	*red;
	t_token	*tmp;

	tmp = t;
	red = ft_calloc(sizeof(t_red), 1);
	red->type = RED;
	while (tmp)
	{
		if (tmp->type == PATH)
		{
			red->file = tmp->str;
			// ft_free(tmp->str);?
			set_red_type(&red, tmp->previous->type);
		}
		tmp = tmp->next;
	}
	red->cmd = (t_cmd *)make_cmd_node(t);
	return (red);
}

void	make_ast2(t_data *data, t_token **toktop)
{
	// size_t	pipe_count;
	int		cmd_type;

	cmd_type = scan_cmd_type(*toktop);
	if (cmd_type == EXECUTE)
		data->st_node = (t_cmd *)make_cmd_node(*toktop);
	else if (cmd_type == RED)
		data->st_node = (t_cmd *)make_red_node(*toktop);
	else
		ft_error("Not implemented", 4, toktop);
	// else if (cmd_type == RED)
	// 	make_red_node(toktop);
	// else if (cmd_type == HEREDOC)
	// 	make_here_node(toktop);
	// pipe_count = count_pipes(*toktop);
	// if (pipe_count != 0)
	// 	data->st_node = (t_cmd *)start_pipe_ast(toktop, pipe_count);
	
}
