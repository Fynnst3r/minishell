/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:39:42 by fforster          #+#    #+#             */
/*   Updated: 2024/12/09 20:23:30 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*keep_expanding(char *s, char *ret, t_lexer *l, char *exit_status)
{
	char	*val;

	l->keepempty = true;
	l->position++;
	while (s[l->position] != '\"' && s[l->position])
	{
		if (s[l->position] == '$' && s[l->position + 1] == '?')
			ret = ft_strjoin_at(ret, exit_status, l, true);
		if (s[l->position] == '$')
		{
			val = check_val(s, l);
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
