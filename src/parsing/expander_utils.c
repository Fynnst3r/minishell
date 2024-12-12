/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:39:42 by fforster          #+#    #+#             */
/*   Updated: 2024/12/12 15:47:16 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*keep_expanding(char *s, char *ret, t_lexer *l, t_list *env)
{
	char	*val;
	char	*exit_status;

	l->keepempty = true;
	l->position++;
	exit_status = ft_itoa(g_signal);
	while (s[l->position] != '\"' && s[l->position])
	{
		if (s[l->position] == '$' && s[l->position + 1] == '?')
			ret = ft_strjoin_at(ret, exit_status, l, true);
		if (s[l->position] == '$')
		{
			val = check_val(s, l, env);
			if (val)
				ret = ft_strjoin_at(ret, val, l, false);
			l->position = l->read;
		}
		else
		{
			ret = add_char(ret, s[l->position], &l->position);
		}
	}
	l->position++;
	ft_free(exit_status);
	return (ret);
}

char	*stop_expanding(char *s, char *ret, t_lexer *l)
{
	l->position++;
	while (s[l->position] != '\'' && s[l->position])
	{
		ret = add_char(ret, s[l->position], &l->position);
	}
	return (ret);
}

char	*ft_getenv(char *tolook, t_list *env)
{
	t_list		*curr;
	t_env_entry	*enventry;

	curr = env;
	if (!env)
		return (NULL);
	while (curr)
	{
		enventry = (t_env_entry *)curr->content;
		if (!ft_strncmp(tolook, enventry->name, ft_strlen(enventry->name) + 1))
		{
			return (enventry->value);
		}
		curr = curr->next;
	}
	return (NULL);
}
