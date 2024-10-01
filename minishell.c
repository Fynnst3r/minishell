/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/10/01 20:08:44 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	fake_exec(t_token *t)
// {
// 	char	*ret;

// 	if (!t)
// 		return ;
// 	if (t->flag == BUILTIN)
// 	{
// 		if (ft_strncmp(t->str, "pwd", 4) == 0)
// 		{
// 			// printf("pwd ATTEMPT\n");
// 			ret = getcwd(NULL, 0);
// 			printf("%s\n", ret);
// 			free(t->str);
// 			// printf("pwd end\n");
// 		}
// 	}
// 	else
// 	{
// 		// printf("STR ATTEMPT\n");
// 		printf("%s", t->str);
// 		free(t->str);
// 		// printf("STR end\n");
// 	}
// }

size_t	token_len(t_token *t, char *input)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	while (input[i] != 0 && !ft_isspace(input[i]))
	{
		l++;
	}
}

static void	start_lexer(const char *input)
{
	t_token	*token;
	t_token	*token_top;

	token = NULL;
	add_history(input);
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		token = new_token();
		token->str = ft_strdup(input);
		token->type = set_type();
		token_add_back(&token_top, token);
	}
}

int	main(int ac, char **av)
{
	const char	*input;

	(void)ac, (void)av;
	while (1)
	{
		input = readline("YM_FF_SHELL: ");
		if (!input)
			exit(1); //unfinished
		if (!*input)
			continue ;
		if (input)
		{
			scan_lexer(input);
			// fake_exec(tokens);
		}
		// tokens = NULL;  delete cmd list and maybe other leftover we dont need anymore data
	}
	// free_tokens(&tokens);
}
// printf("kill3\n");


// scan input and split into raw tokens
// analyse token content and assign token type
