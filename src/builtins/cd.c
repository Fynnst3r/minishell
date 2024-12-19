/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:34:33 by fforster          #+#    #+#             */
/*   Updated: 2024/12/19 20:03:02 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_cd_error(char *path)
{
	if (errno == EACCES)
		printf("Search permission is denied for one of the components of %s.\n",
			path);
	if (errno == EFAULT)
		printf("%s points outside your accessible address space.\n", path);
	if (errno == EIO)
		printf("An I/O error occurred.\n");
	if (errno == ELOOP)
		printf("Too many symbolic links were encountered in resolving%s.\n",
			path);
	if (errno == ENAMETOOLONG)
		printf("%s is too long.\n", path);
	if (errno == ENOENT)
		printf("The directory specified in %s does not exist.\n", path);
	if (errno == ENOMEM)
		printf("Insufficient kernel memory was available.\n");
	if (errno == ENOTDIR)
		printf("A component of %s is not a directory.\n", path);
}

static int	check_cd_arg(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i <= 1)
		return (1);
	if (i > 2)
		return (printf("YM_FF_SHELL: too many arguments\n"), 1);
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
	if (check_cd_arg(cmd))
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
