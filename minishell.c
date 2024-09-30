/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/09/30 18:34:37 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fake_exec(t_token *t)
{
	char	*ret;

	if (!t)
		return ;
	if (t->flag == BUILTIN)
	{
		if (ft_strncmp(t->str, "pwd", 4) == 0)
		{
			// printf("pwd ATTEMPT\n");
			ret = getcwd(NULL, 0);
			printf("%s\n", ret);
			free(t->str);
			// printf("pwd end\n");
		}
	}
	else
	{
		// printf("STR ATTEMPT\n");
		printf("%s", t->str);
		free(t->str);
		// printf("STR end\n");
	}
}

void	assign_token_type(char *solo_split, t_token **t)
{
	size_t	i = 0;
	size_t	l = 0;
	int		flag;

	flag = OTHER;
	while (solo_split[i])
	{
		if (solo_split[i] == '(')
			flag = O_PARANT;
		if (solo_split[i] == ')')
			flag = C_PARANT;
		if (solo_split[i] == '|')
			flag = PIPE;
		if (ft_isdigit(solo_split[i]))
			flag = NUMBER;
		
	}
		make_token(t, solo_split, flag, i);
}

void	scan_start(const char *input, t_token **token)
{
	size_t	i;
	char	**split;

	i = 0;

	split = ft_split(input, ' ');
	while (split[i])
	{
		assign_token_type(split[i], token)
	}
	
}

int	main(int ac, char **av)
{
	const char	*input;
	t_token		*tokens;

	(void)ac, (void)av;
	tokens = NULL;
	while (1)
	{
		input = readline("YM_FF_SHELL: ");
		if (!input)
			exit(1); //unfinished
		if (!*input)
			continue ;
		if (input)
		{
			scan_start(input, &tokens);
			fake_exec(tokens);
		}
		tokens = NULL; // delete cmd list and maybe other leftover we dont need anymore data
	}
	// free_tokens(&tokens);
}
// printf("kill3\n");


// scan input and split into raw tokens
// analyse token content and assign token type
