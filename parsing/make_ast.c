/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:17:36 by fforster          #+#    #+#             */
/*   Updated: 2024/11/17 22:02:46 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*init_ast_node(void)
{
	t_ast	*node;
	// t_ast	*test;

	node = ft_malloc(sizeof(t_ast));
	// test = ft_malloc(sizeof(t_ast));
	// test->type = OTHER;
	ft_bzero(node, sizeof(t_ast));
	node->type = OTHER;
	// node->left = test;
	// printf("pointer %p, pointer %p, pointer %p type %i\n", node->data, node->left, node->right, node->type);
	// printf("test %i\n", test->type);
	// test->type = PIPE;
	// node->left = test;
	// printf("test2 %i\n", node->left->type);
	return (node);
}

// t_ast	*scan_for_cmd(t_ast *ast, t_token *tokentmp, int *id)
// {
// 	t_command	*cmd;
// 	t_lexer		lex;

// 	if (ft_strchr(tokentmp->str, '|'))
// 		printf("return a ast pipenodeXDDDD\n");
// 		// return (append_pipe_ast)
// 	lex = init_lex(NULL);
// 	while (tokentmp)
// 	{
// 		break ;
// 	}
// 	return (cmd);
// }

t_ast	*make_ast(t_token **toktop)
{
	t_ast	*ast;
	t_token	*tokentmp;
	int		id;

	tokentmp = *toktop;
	ast = init_ast_node();
	id = 0;
	while (tokentmp != 0)
	{
		// ast = scan_for_cmd(ast, tokentmp, &id);
		tokentmp = find_id(*toktop, id);
	}
	return (ast);
}
