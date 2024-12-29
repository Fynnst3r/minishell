/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:15:30 by fforster          #+#    #+#             */
/*   Updated: 2024/12/29 18:21:30 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_exec(t_exec *cmd)
{
	size_t	i;

	i = 0;
	printf("EXECUTE\n");
	if (cmd->argv[0] == NULL)
		printf(ANSI_RED"EMPTY PIPE COMMAND\n"ANSI_RESET);
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
			// printf("next type %i\n", red->cmd->type);
			print_red((t_red *)red->cmd);
		}
	}
}

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

t_exec	*make_cmd_node(t_token *t)
{
	t_exec	*exec;
	t_token	*tmp;
	size_t	count;

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
	exec->argv[count] = NULL;
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

static t_red	*find_last_red(t_red *top)
{
	while (top->cmd != NULL)
	{
		top = (t_red *)top->cmd;
	}
	return (top);
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

t_red	*create_redir_cmd(t_token *t)
{
	t_red	*red;
	t_red	*last;
	t_token	*tmp;

	red = NULL;
	tmp = t;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			break ;
		if (tmp->type == PATH && tmp->previous->type != T_HERE)
		{
			make_red_node(&red, tmp->previous->type, tmp->str);
		}
		tmp = tmp->next;
	}
	last = find_last_red(red);
	last->cmd = (t_cmd *)make_cmd_node(t);
	return (red);
}

t_token	*scan_last_heredoc(t_token *tmp)
{
	t_token	*last;

	last = NULL;
	while (tmp)
	{
		// if (tmp->type == T_PIPE)
		// 	return (NULL);
		if (tmp->type == PATH && tmp->previous->type == T_HERE)
			last = tmp;
		tmp = tmp->next;
	}
	return (last);
}

t_herd	*make_herd_node(t_token *t)
{
	t_herd	*herd;
	t_token	*last_herd_tok;
	t_token	*tmp;

	last_herd_tok = scan_last_heredoc(t);
	if (last_herd_tok == NULL)
		return (NULL);
	herd = ft_calloc(sizeof(t_herd), 1);
	herd->type = HEREDOC;
	herd->del = ft_strjoin(last_herd_tok->str, "\n");
	ft_free(last_herd_tok->str);
	last_herd_tok->str = herd->del;
	tmp = t;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			break ;
		if (tmp->type == PATH && tmp->previous->type != T_HERE)
			herd->cmd = (t_cmd *)create_redir_cmd(t);
		tmp = tmp->next;
	}
	if (herd->cmd == NULL)
		herd->cmd = (t_cmd *)make_cmd_node(t);
	return (herd);
}
// t_herd	*make_herd_node(t_token *t)
// {
// 	t_herd	*herd;
// 	t_token	*tmp;

// 	tmp = t;
// 	herd = ft_calloc(sizeof(t_herd), 1);
// 	herd->type = HEREDOC;
// 	while (tmp)
// 	{
// 		if (tmp->type == PATH && tmp->previous->type == T_HERE)
// 			herd->del = tmp->str;
// 		tmp = tmp->next;
// 	}
// 	herd->cmd = (t_cmd *)make_cmd_node(t);
// 	return (herd);
// }

void	make_ast2(t_data *data, t_token **toktop)
{
	int		cmd_type;

	cmd_type = scan_cmd_type(*toktop);
	// printf("cmd type %i\n", cmd_type);
	if (cmd_type == EXECUTE)
		data->st_node = (t_cmd *)make_cmd_node(*toktop);
	else if (cmd_type == RED)
	{
		data->st_node = (t_cmd *)create_redir_cmd(*toktop);
		// print_red((t_red *)data->st_node);
	}
	else if (cmd_type == HEREDOC)
		data->st_node = (t_cmd *)make_herd_node(*toktop);
	else
	{
		data->st_node = (t_cmd *)make_pipe_ast(toktop);
		// print_pipe_ast((t_pipe *)data->st_node);
	}
}
