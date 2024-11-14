/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:41:49 by fforster          #+#    #+#             */
/*   Updated: 2024/11/14 18:55:01 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_str(t_lexer *lex)
{
	char	*ret;
	char	*value;
	char	*tmp;
	size_t	l;
	char	*getenvalue;

	l = lex->position;
	ret = NULL;
	printf("get_str sutaato\n position %zu\n", l);
	while (lex->str[l])
	{
		lex->read_cursor = l;
		lex->curr_c = lex->str[l];
		if (lex->str[l] == '\'' || lex->str[l] == '\"')
			skip_quote(lex->str, &l);
		lex->last_c = lex->str[l];
		l++;
		// printf("HUH?!?\n c = %c\n", lex->str[l]);
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

void	start_lexer(char *input)
{
	t_token	*token_top;
	size_t	i;
	t_lexer	lexer;

	token_top = NULL;
	add_history(input);
	i = 0;
	lexer = init_lex(input);
	while (input[i])
	{
		i = lexer.position;
		make_token(&token_top, &lexer);
	}
	printf("*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n");
	print_token_data(token_top);
	printf("*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n");
	token_top = NULL;
}

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
