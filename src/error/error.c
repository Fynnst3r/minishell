/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:10:15 by fforster          #+#    #+#             */
/*   Updated: 2025/01/04 16:47:52 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_exit(int errnum)
{
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(errnum);
}

void	ft_clean(char *message, t_data *data, t_token **toktop)
{
	if (message)
		printf("YM_FF_SHELL: %s\n", message);
	if (data)
	{
		if (data->input)
			ft_free(data->input);
		data->input = NULL;
		if (data->st_node)
			ft_free_tree(data->st_node);
		data->st_node = NULL;
	}
	if (toktop)
		free_tokens(toktop);
}

void	free_tokens(t_token **t)
{
	t_token	*tmp;

	if (!*t)
		return ;
	tmp = *t;
	while (tmp->next != NULL)
	{
		ft_free(tmp->str);
		tmp->str = NULL;
		tmp = tmp->next;
		ft_free(tmp->previous);
	}
	ft_free(tmp);
	tmp = NULL;
	*t = NULL;
	t = NULL;
}

void	ft_error(char *message, int errcode, t_token **toktop)
{
	if (message)
		printf("%s\n", message);
	if (toktop)
		free_tokens(toktop);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(errcode);
}

int	ft_free_herd(t_cmd *node)
{
	t_herd	*free_herd;

	if (!node)
		return (1);
	if (node->type == HEREDOC)
	{
		free_herd = (t_herd *)node;
		ft_free_tree(free_herd->cmd);
		ft_free(free_herd->del);
		ft_free(free_herd->cmd);
		free_herd->del = NULL;
		free_herd->cmd = NULL;
		free_herd = NULL;
		return (1);
	}
	return (1);
}

	// static int count = 0;
	// count++;
	// printf("count %i\n", count);
	// printf("type %i\n", st_node->type);
