/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:15:30 by fforster          #+#    #+#             */
/*   Updated: 2024/12/10 16:12:33 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_exec(t_exec *cmd)
{
	size_t	i;

	i = 0;
	printf("EXECUTE\n");
	if (cmd->argv[0] == NULL)
		printf("AHAHAHAHAH NOTHING YOU LOOOOOOSER\n");
	while (cmd->argv[i])
	{
		printf("arg[%zu] = %s\n", i, cmd->argv[i]);
		i++;
	}
}

void	print_pipe_ast(t_pipe *pipe)
{
	static int	i = 0;

	printf("recursive %i\n\n", i);
	i++;
	if (pipe)
	{
		printf(ANSI_RED"PIPE RIGHT\n"ANSI_RESET);
		if (pipe->right->type == EXECUTE)
			print_exec((t_exec *)pipe->right);
		else if (pipe->right->type == PIPE)
			printf("THISBITCHEMPTY\n");
		printf(ANSI_GREEN"PIPE LEFT\n"ANSI_RESET);
		if (pipe->left->type == EXECUTE)
			print_exec((t_exec *)pipe->left);
		else if (pipe->left->type == PIPE)
			print_pipe_ast((t_pipe *)pipe->left);
	}
	printf("finished pipe print\n");
}

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
	while (tmp && tmp->type != T_PIPE)
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
			set_red_type(&red, tmp->previous->type);
		}
		tmp = tmp->next;
	}
	red->cmd = (t_cmd *)make_cmd_node(t);
	return (red);
}

t_herd	*make_herd_node(t_token *t)
{
	t_herd	*herd;
	t_token	*tmp;

	tmp = t;
	herd = ft_calloc(sizeof(t_herd), 1);
	herd->type = HEREDOC;
	while (tmp)
	{
		if (tmp->type == PATH && tmp->previous->type == T_HERE)
			herd->del = tmp->str;
		tmp = tmp->next;
	}
	herd->cmd = (t_cmd *)make_cmd_node(t);
	return (herd);
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
	else if (cmd_type == HEREDOC)
		data->st_node = (t_cmd *)make_herd_node(*toktop);
	else
	{
		data->st_node = (t_cmd *)make_pipe_ast(toktop);
		print_pipe_ast((t_pipe *)data->st_node);
	}
}
