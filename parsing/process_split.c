/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:30:09 by fforster          #+#    #+#             */
/*   Updated: 2024/10/23 16:44:58 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *str, size_t l)
{
	char	*env_start;
	char	*tmp;
	char	*val;
	char	*ret;
	size_t	k;

	env_start = ft_substr(str, l, ft_strlen(str) - l);
	ret = ft_strdup("");
	l = 0;
	k = 0;
	while (env_start[l])
	{
		if (env_start[l] == '$')
		{
			tmp = ft_strdup(&env_start[++l]);
			val = getenv(tmp);
			ret = ft_strjoin(ret, val);
		}
	}
	return (ret);
}

int	quote_status(char c, int ignore)
{
	if (c == '\'' && ignore == 0)
		ignore = 1;
	else if (c == '\"' && ignore == 0)
		ignore = 2;
	else if (c == '\'' && ignore == 1)
		ignore = 0;
	else if (c == '\"' && ignore == 2)
		ignore = 0;
	printf("ignore level %d\n", ignore);
	return (ignore);
}

int	process_split(char **split)
{
	size_t	i;
	size_t	l;
	int		ignore;
	char	*value;

	i = 0;
	l = 0;
	ignore = 0;
	value = NULL;
	while (split[i])
	{
		while (split[i][l])
		{
			ignore = quote_status(split[i][l], ignore);

			if (split[i][l] == '$' && (ignore == 0 || ignore == 2))
				value = get_env_value(split[i], l);
			l++;
		}
		i++;
		printf("i++\n");
	}
	return (0);
}

// int main ()
// {
// 	char *s = "hey$USER$PATH";
// 	char *ret;
// 	int i = 0;
// 	while (s[i] && s[i] != '$')
// 		i++;
// 	ret = get_env_value(s, i);
// 	printf("%s", ret);
// 	// printf("HEY%s", ft_strdup(&s[i]));
// 	// printf("gettest %s\n", getenv("\'USER\'"));
// }
