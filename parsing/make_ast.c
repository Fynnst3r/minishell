/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:17:36 by fforster          #+#    #+#             */
/*   Updated: 2024/11/27 15:31:53 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_pipe(t_token *t)
{
	t_token	*tmp;

	tmp = t;
	while (tmp)
	{
		if (tmp->next->type == T_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*set_cmd_name(char *s, int type)
{
	char	*ret;
	// if (type == DOUBLE_Q || type == SINGLE_Q)
	// {
	// 	ret = s;
	// 		printf(ANSI_BG_CYAN"Conversion of $ here\n"ANSI_RESET);
	// }
	ret = s;
	return (ret);
}

size_t	count_args(t_token *t)
{
	t_token	*tmp;
	size_t	count;

	tmp = t;
	count = 0;
	while (tmp)
	{
		if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	printf(ANSI_BLUE"arg count %zu\n"ANSI_RESET, count);
	return (count);
}

	// printf(ANSI_RED"why\n"ANSI_RESET);
void	make_redir_node(t_redir **redirtop, t_token *tok, int type)
{
	t_redir	*node;
	t_redir	*last_node;

	if (!redirtop)
		return ;
	node = ft_calloc(sizeof(t_redir), 1);
	if (!node)
		return ;
	// print_token_data(tok);
	node->file = NULL;
	node->type = type;
	if (node->type == T_HERE)
		tok->previous->str = node->delimeter;
	else
		node->file = tok->previous->str; // what if there is no follow up string? exit? It should have one
	if (*redirtop == NULL)
	{
		node->next = NULL;
		return ;
	}
	last_node = *redirtop;
	while (last_node)
		last_node = last_node->next;
	node->next = last_node;
}

t_command	*create_cmd_ast(t_token *toktop)
{
	t_command	*cmd;
	t_token		*tok;
	t_redir		*red;
	size_t		i;

	tok = toktop;
	cmd = ft_calloc(sizeof(t_command), 1);
	cmd->redirs = NULL;
	cmd->name = set_cmd_name(tok->str, tok->type);
	tok = tok->next;
	cmd->argv = ft_calloc(sizeof(char *), (count_args(tok) + 1)); // NOT NULL TERMINATED!
	red = NULL;
	i = 0;
	while (tok)
	{
		if (tok->type == DOUBLE_Q || tok->type == SINGLE_Q)
			cmd->argv[i++] = tok->str; //Conversion of $ and removal of quotes here
		else if (tok->type == WORD)
			cmd->argv[i++] = tok->str;
		else if (tok->type == PATH)
			make_redir_node(&red, tok, tok->previous->type);
		tok = tok->next;
	}
	cmd->redirs = red;
	return (cmd);
}

t_ast	*create_ast_node(void *data, t_type type)
{
	t_ast	*node;

	node = ft_malloc(sizeof(t_ast));
	ft_bzero(node, sizeof(t_ast));
	node->data = data;
	node->type = type;
	node->right = NULL;
	node->left = NULL;
	return (node);
}
	// t_ast	*test;
	// test = ft_malloc(sizeof(t_ast));
	// test->type = OTHER;
	// node->left = test;
	// printf("pointer %p, pointer %p, pointer %p type %i\n", node->data, node->left, node->right, node->type);
	// printf("test %i\n", test->type);
	// test->type = PIPE;
	// node->left = test;
	// printf("test2 %i\n", node->left->type);

t_ast	*make_ast(t_token **toktop)
{
	t_ast		*ast;
	t_command	*cmd;
	t_token		*tokentmp;
	int			id;

	tokentmp = *toktop;
	id = 0;
	// if (has_pipe(*toktop))
		// ast = create_pipe_ast(toktop);
	// else
	cmd = create_cmd_ast(tokentmp);
	// while (tokentmp != 0)
	// {
		
	// 	tokentmp = find_id(*toktop, id);
	// }
	printf(ANSI_BRIGHT_MAGENTA"NAME = %s\n"ANSI_RESET, cmd->name);
	while (cmd->argv[id])
	{
		printf("argv = %s\n", cmd->argv[id]);
		id++;
	}
	if (cmd->redirs)
		printf("filename %s\n", cmd->redirs->file);
	ast = 0;
	return (ast);
}
// redirs not working putting in data correctly yet