/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:27 by fforster          #+#    #+#             */
/*   Updated: 2024/09/25 12:43:06 by fforster         ###   ########.fr       */
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

void	scan_start(const char *input, t_token **token)
{
	size_t	i;
	size_t	l;
	// char	**split;

	i = 0;
	l = 0;

	if (ft_strncmp(input, "pwd", 4) == 0)
	{
		make_token(token);
		// printf("kill\n");
		(*token)->flag = BUILTIN;
		(*token)->str = (char *)input;
	}
	else
	{
		// printf("kill else\n");
		make_token(token);
		(*token)->str = (char *)input;
	}
}

int	main(int ac, char **av)
{
	const char	*prompt;
	const char	*input;
	t_token		*tokens;

	prompt = "YM_FF_SHELL: ";
	input = NULL;
	tokens = NULL;
	while (1)
	{
		input = readline(prompt);
		scan_start(input, &tokens);
		fake_exec(tokens);
		start_exec();
		tokens = NULL;
	}
	free_tokens(&tokens);
}
// printf("kill3\n");
