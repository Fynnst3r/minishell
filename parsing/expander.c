/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:11:54 by fforster          #+#    #+#             */
/*   Updated: 2024/11/30 20:36:01 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_char(char *ret, char add, size_t *position)
{
	char	*added;
	size_t	i;

	added = ft_calloc(ft_strlen(ret) + 2, 1);
	i = 0;
	if (!added)
		return (NULL);
	if (!ret)
		added[0] = add;
	while (ret[i])
	{
		added[i] = ret[i];
		i++;
	}
	added[i] = add;
	ft_free(ret);
	ret = NULL;
	(*position)++;
	return (added);
}

char	*ft_strjoin_at(char *s1, char *s2, t_lexer *l, bool print_exit)
{
	size_t	i;
	size_t	x;
	char	*join;

	i = -1;
	x = 0;
	if (!s1 || !s2)
		return (NULL);
	join = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[++i])
		join[i] = s1[i];
	while (s2[x])
		join[i++] = s2[x++];
	ft_free(s1);
	if (print_exit)
		l->position += 2;
	else
		l->position = l->read;
	s1 = NULL;
	s2 = NULL;
	return (join);
}

char	*check_val(char *s, t_lexer *l)
{
	char	*sub;
	char	*val;

	l->read = l->position + 1;
	while (s[l->read] != '$' && s[l->read] != ' ' && s[l->read] != 0
		&& s[l->read] != '\'' && s[l->read] != '\"')
	{
		l->read++;
	}
	sub = ft_substr(s, l->position + 1, l->read - l->position - 1);
	val = getenv(sub);
	ft_free(sub);
	sub = NULL;
	if (val == NULL)
		return (NULL);
	return (val);
}

static char	*get_exp_str(char *s, char *exit_status)
{
	t_lexer	l;
	char	*val;
	char	*ret;

	l = init_lex(s);
	ret = ft_strdup("");
	while (s[l.position])
	{
		if (s[l.position] == '\"')
			ret = keep_expanding(s, ret, &l, exit_status);
		else if (s[l.position] == '\'')
			ret = stop_expanding(s, ret, &l);
		else if (s[l.position] == '$' && s[l.position + 1] == '?')
			ret = ft_strjoin_at(ret, exit_status, &l, true);
		else if (s[l.position] == '$')
		{
			val = check_val(s, &l);
			if (val)
				ret = ft_strjoin_at(ret, val, &l, false);
		}
		else
			ret = add_char(ret, s[l.position], &l.position);
	}
	return (ret);
}

void	expand_tokens(t_token **toktop, int exit_status)
{
	t_token	*tmp;
	char	*exit_num_str;

	tmp = *toktop;
	exit_num_str = ft_itoa(exit_status);
	while (tmp)
	{
		if (tmp->type == WORD || PATH)
			tmp->str = get_exp_str(tmp->str, exit_num_str);
		if (tmp->str)
			tmp->len = ft_strlen(tmp->str);
		tmp = tmp->next;
	}
	ft_free(exit_num_str);
}

// int main()
// {
// 	init_garbage_collector();
// 	char	*test = ft_strdup(" 9$US 0ER");
// 	// t_lexer l = init_lexs(test);
// 	get_exp_str(test, DOUBLE_Q);
// 	delete_trash();
// 	ft_bzero(get_workers(), sizeof(t_trashman));
// 	// printf("test %s\n",  expand_quote(test, DOUBLE_Q));
// }
		// printf(ANSI_GREEN"l.pos = %zu\n", l->position);
		// printf("l.read = %zu\n"ANSI_RESET, l->read);