/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:15:30 by fforster          #+#    #+#             */
/*   Updated: 2025/01/04 15:56:14 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_exec(t_exec *cmd)
{
	size_t	i;

	i = 0;
	printf("EXECUTE\n");
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
		if (pipe->right->type == EXECUTE)
			print_exec((t_exec *)pipe->right);
		else if (pipe->right->type == PIPE)
			printf("THISBITCHEMPTY\n");
		if (pipe->left->type == EXECUTE)
			print_exec((t_exec *)pipe->left);
		else if (pipe->left->type == PIPE)
			print_pipe_ast((t_pipe *)pipe->left);
	}
	printf("finished pipe print\n");
}

void	print_red(t_red *red)
{
	static int	i = 0;

	printf("red num %i\n\n", i);
	i++;
	if (red)
	{
		printf("filename = %s\n", red->file);
		printf("cmd type = %i\n", red->type);
		printf("red mode = %i\n", red->mode);
		printf("fd = %i\n", red->fd);
		if (red->cmd && red->cmd->type == RED)
		{
			print_red((t_red *)red->cmd);
		}
	}
}

t_exec	*make_cmd_node(t_token *t)
{
	t_exec	*exec;
	t_token	*tmp;
	size_t	count;

	count = count_cmd_args(t);
	tmp = t;
	exec = ft_calloc(sizeof(t_exec), 1);
	exec->type = EXECUTE;
	exec->argv = ft_calloc(sizeof(char *), count + 1);
	tmp = t;
	count = 0;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type == WORD && tmp->str != NULL)
		{
			exec->argv[count] = tmp->str;
			count++;
		}
		tmp = tmp->next;
	}
	exec->argv[count] = NULL;
	return (exec);
}

static void	make_red_node(t_red **top, int type, char *filename)
{
	t_red	*new;
	t_red	*last;

	new = ft_calloc(sizeof(t_red), 1);
	new->type = RED;
	new->file = filename;
	set_red_type(&new, type);
	if (*top == NULL)
	{
		*top = new;
		return ;
	}
	last = find_last_red(*top);
	last->cmd = (t_cmd *)new;
	return ;
}
