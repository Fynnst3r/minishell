/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:41:49 by fforster          #+#    #+#             */
/*   Updated: 2024/11/18 19:03:52 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

		// printf("HUH?!?\n c = %c\n", lex->str[l]);
	// printf("get_str sutaato\n position %zu\n", l);
char	*get_str(t_lexer *lex)
{
	char	*ret;
	size_t	l;

	l = lex->position;
	ret = NULL;
	while (lex->str[l])
	{
		lex->read_cursor = l;
		lex->curr_c = lex->str[l];
		if (lex->str[l] == '\'' || lex->str[l] == '\"')
			skip_quote(lex->str, &l);
		lex->last_c = lex->str[l];
		l++;
		if (is_special_char(lex->str[l]) || ft_isspace(lex->str[l]))
		{
			printf("BREAK ; \n");
			break ;
		}
	}
	if (!ret && l != lex->position)
		ret = ft_substr(lex->str, lex->position, l - lex->position);
	while (ft_isspace(lex->str[l]))
		l++;
	lex->position = l;
	return (ret);
}

t_lexer	init_lex(char *input)
{
	t_lexer	lex;

	lex.str = input;
	lex.position = 0;
	lex.read_cursor = 0;
	lex.last_c = 0;
	lex.curr_c = 0;
	return (lex);
}

t_ast	*start_lexer(char *input)
{
	t_token	*token_top;
	t_lexer	lexer;
	t_ast	*ast;
	bool	skip;

	token_top = NULL;
	add_history(input);
	lexer = init_lex(input);
	skip = false;
	while (input[lexer.position])
	{
		while (is_special_char(input[lexer.position]))
		{
			skip = true;
			if (handle_special(input, &lexer, &token_top, lexer.position))
				printf(ANSI_RED"!!!!!!!!HANDLE ERROR!!!!!!!!!\n"ANSI_RESET);
		}
		while (ft_isspace(input[lexer.position]))
			lexer.position++;
		if (!skip)
			make_token(&token_top, &lexer);
		skip = false;
	}
	set_token_id(token_top);
	print_token_data(token_top);
	ast = make_ast(&token_top);
	token_top = NULL; //put at end of token use (and free them)
	return (ast);
}
	// start makin ast nodes "s_node"
	// scan for pipes
	// assign type and scan for args and redirs
	// convert $
	// ?check syntax?

// int main()
// {
// 	char	*str;

// 	init_garbage_collector();
// 	while (1)
// 	{
// 		str = readline("FILLMEUPDADDY: ");
// 		add_history(str);
// 		// str = "WHY ARE YOU DOING THIS TO ME";
// 		if (str)
// 		{
// 		// str = ft_strdup("Hey $USER");
// 			start_lexer(str);
// 			free(str);
// 			str = NULL;
// 			delete_trash();
// 			ft_bzero(get_workers(), sizeof(t_trashman));
// 		}
// 	}
// }
