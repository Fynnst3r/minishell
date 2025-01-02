/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:32:04 by fforster          #+#    #+#             */
/*   Updated: 2025/01/02 20:33:24 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	check_for_next_pipe(t_token *tmp)
{
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

	// print_token_data(t);
int	scan_cmd_type_pipe(t_token *t)
{
	int	ret;

	ret = EXECUTE;
	while (t)
	{
		if (t->type == PATH)
		{
			if (t->previous->type != T_HERE)
				ret = RED;
			else
				return (HEREDOC);
		}
		if (t->type == T_PIPE)
			break ;
		t = t->next;
	}
	return (ret);
}

t_pipe	*make_pipe_node(t_pipe *last)
{
	t_pipe	*new;

	new = ft_calloc(sizeof(t_pipe), 1);
	new->type = PIPE;
	if (last)
	{
		new->left = (t_cmd *)last;
	}
	return (new);
}

t_cmd	*set_pipe_cmd(t_token *tmp, bool first)
{
	int		cmd_type;

	cmd_type = scan_cmd_type_pipe(tmp);
	// printf("COMMAND TYPE %i\n\n\n", cmd_type);
	if (cmd_type == EXECUTE)
		return ((t_cmd *)make_cmd_node(tmp));
	else if (cmd_type == RED)
		return ((t_cmd *)create_redir_cmd(tmp));
	else if (cmd_type == HEREDOC)
	{
		if (!first)
		{
			printf("YM_FF_SHELL: syntax error near token '|', "
				"pipe heredoc does not work\n");
			return (NULL);
		}
		return ((t_cmd *)make_herd_node(tmp));
	}
	return (NULL);
}

t_pipe	*make_pipe_ast(t_token **toktop)
{
	t_pipe	*pipe;
	int		curr_id;
	t_token	*tmp;

	curr_id = 0;
	tmp = *toktop;
	pipe = make_pipe_node(NULL);
	pipe->left = set_pipe_cmd(tmp, true);
	while (tmp)
	{
		while (tmp->type != T_PIPE)
			tmp = tmp->next;
		curr_id = tmp->id + 1;
		pipe->right = set_pipe_cmd(find_id(*toktop, curr_id), false);
		if (!pipe->right)
			return (ft_free_tree((t_cmd *)pipe), NULL);
		if (check_for_next_pipe(find_id(*toktop, curr_id)) == true)
			pipe = make_pipe_node(pipe);
		else
			break ;
		tmp = tmp->next;
	}
	return (pipe);
}
