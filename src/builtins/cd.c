/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:34:33 by fforster          #+#    #+#             */
/*   Updated: 2024/12/21 16:53:54 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

		// printf("cdm0 = '%s'\ncmd1 = '%s'\n", cmd[0][0], cmd[0][1]);
		// return (cd_home(data, cmd), 1);
static int	check_cd_arg(t_data *data, char **cmd)
{
	size_t	i;
	char	**newcmd;

	i = 0;
	while (cmd[i])
		i++;
	if (i < 1)
		return (1);
	if (i > 2)
		return (printf("YM_FF_SHELL: too many arguments\n"), 1);
	if (i == 1)
	{
		free_dp(cmd);
		newcmd = ft_malloc(sizeof(char *) * 3);
		newcmd[0] = ft_strdup("cd");
		newcmd[1] = ft_getenv("HOME", data->env_list);
		newcmd[2] = NULL;
		exec_cd(data, newcmd);
		return (1);
	}
	return (0);
}

int	exec_cd(t_data *data, char **cmd)
{
	char	*cwd;
	char	*newcwd;
	char	*oldpwd;
	int		ret;

	cwd = NULL;
	newcwd = NULL;
	oldpwd = NULL;
	if (check_cd_arg(data, cmd))
		return (1);
	cwd = getcwd(cwd, MAXPATHLEN);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	add_or_replace_entry(data, oldpwd, ft_strchr(oldpwd, '='));
	ft_free(oldpwd);
	ret = chdir(cmd[1]);
	free(cwd);
	cwd = NULL;
	if (ret < 0)
		return (print_cd_error(cmd[1]), 1);
	cwd = getcwd(cwd, MAXPATHLEN);
	newcwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	cwd = NULL;
	add_or_replace_entry(data, newcwd, ft_strchr(newcwd, '='));
	return (ft_free(newcwd), 0);
}