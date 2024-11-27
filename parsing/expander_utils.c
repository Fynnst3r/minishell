/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:39:42 by fforster          #+#    #+#             */
/*   Updated: 2024/11/27 19:02:04 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*keep_expanding(char *s, char *ret, t_lexer *l, int type)
{
	char	*val;

	l->position++;
	while (s[l->position] != '\"' && s[l->position])
	{
		if (s[l->position] == '$' && type != SINGLE_Q)
		{
			val = check_val(s, l);
			if (val)
				ret = ft_strjoin_at(ret, val, l);
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

char	*stop_expanding(char *s, char *ret, t_lexer *l, int type)
{
	l->position++;
	while (s[l->position] != '\'' && s[l->position])
	{
		ret = add_char(ret, s[l->position], &l->position);
	}
	return (ret);
}
