/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:40:34 by fforster          #+#    #+#             */
/*   Updated: 2024/12/21 21:53:58 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// This function checks basic syntax errors
int	evaluator(t_token *toktop)
{
	t_token	*tmp;

	tmp = toktop;
	while (tmp)
	{
		if (tmp->type == T_PIPE && ((tmp->next == NULL || tmp->previous == NULL)
				|| (tmp->type == T_PIPE && tmp->next->type == T_PIPE)))
			return (printf("YM_FF_SHELL: syntax error near token '%s'\n",
					tmp->str), 1);
		else if (tmp->type == T_OUT || tmp->type == T_APP || tmp->type == T_IN
			|| tmp->type == T_HERE)
		{
			if (tmp->next == NULL)
				return (printf("YM_FF_SHELL: syntax error near token '%s'\n",
						tmp->str), 1);
			if (tmp->next->type != PATH)
				return (printf("YM_FF_SHELL: syntax error near token '%s'\n"
						, tmp->next->str), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
