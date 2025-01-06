/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:51:05 by fforster          #+#    #+#             */
/*   Updated: 2025/01/05 19:41:29 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error(char *message, char *path)
{
	write(STDERR_FILENO, "YM_FF_SHELL: ", ft_strlen("YM_FF_SHELL: "));
	ft_putstr_fd(message, 2);
	if (path)
		write(2, path, ft_strlen(path));
	write(STDERR_FILENO, "\n", 1);
}

void	change_e_stat(t_data *data, int new)
{
	if (data->e_status == 0)
		data->e_status = new;
}

// static void	print_access_error2(char *path)
// {
// 	if (errno == ENOTDIR)
// 		printf("A component used as a directory in `%s' is not, "
// 			"in fact, a directory.\n", path);
// 	if (errno == EPERM)
// 		printf("Write permission was requested to a file that has the "
// 			"immutable flag set.\n");
// 	if (errno == EROFS)
// 		printf("Write permission was requested for a file "
// 			"on a read-only filesystem.\n");
// 	if (errno == ETXTBSY)
// 		printf("Write access was requested to an executable which is being "
// 			"executed.\n");
// 	if (errno == ENOMEM)
// 		printf("Insufficient kernel memory was available.\n");
// }
// void	print_access_error(char *path, int mode)
// {
// 	printf("YM_FF_SHELL: ");
// 	if (errno == EACCES)
// 		printf("The requested access would be denied to the file, "
// 			"or search permission is denied for one of the directories "
// 			"in the path prefix of `%s'.\n", path);
// 	if (errno == EFAULT)
// 		printf("`%s' points outside your accessible address space.\n", path);
// 	if (errno == EINVAL)
// 		printf("MODE `%d' was incorrectly specified, "
// 			"or PATH was unset.\n", mode);
// 	if (errno == EIO)
// 		printf("An I/O error occurred.\n");
// 	if (errno == ELOOP)
// 		printf("Too many symbolic links were encountered in resolving `%s'.\n",
// 			path);
// 	if (errno == ENAMETOOLONG)
// 		printf("`%s' is too long.\n", path);
// 	if (errno == ENOENT)
// 		printf("A component of `%s' does not exist or "
// 			"or is a dangling symbolic link.\n", path);
// 	print_access_error2(path);
// }
// void	print_cd_error(char *path)
// {
// 	printf("YM_FF_SHELL: ");
// 	if (errno == EACCES)
// 		printf("Search permission is denied for one of the components of %s.\n",
// 			path);
// 	if (errno == EFAULT)
// 		printf("%s points outside your accessible address space.\n", path);
// 	if (errno == EIO)
// 		printf("An I/O error occurred.\n");
// 	if (errno == ELOOP)
// 		printf("Too many symbolic links were encountered in resolving%s.\n",
// 			path);
// 	if (errno == ENAMETOOLONG)
// 		printf("%s is too long.\n", path);
// 	if (errno == ENOENT)
// 		printf("The directory specified in %s does not exist.\n", path);
// 	if (errno == ENOMEM)
// 		printf("Insufficient kernel memory was available.\n");
// 	if (errno == ENOTDIR)
// 		printf("A component of %s is not a directory.\n", path);
// }
// void	print_open_error(char *path, int flags)
// {
// 	if (errno == EACCES)
// 		printf("The requested access to the file is not allowed,"
// 			" or search permission is denied for `%s'. More in man\n", path);
// 	if (errno == EFAULT)
// 		printf("`%s' points outside your accessible address space.\n",
// 			path);
// 	if (errno == EOVERFLOW)
// 		printf("`%s' refers to a regular file that is too large "
// 			"to be opened. See more in man\n", path);
// 	if (errno == EINVAL)
// 		printf("Invalid value in flag `%d'.\n", flags);
// 	if (errno == EISDIR)
// 		printf("`%s' refers to a directory and the access requested "
// 			"involved writing (that is, O_WRONLY or O_RDWR is set).\n", path);
// 	if (errno == ENAMETOOLONG)
// 		printf("`%s' was too long.\n", path);
// 	if (errno == ENFILE)
// 		printf("The system-wide limit on the total number of open files"
// 			"has been reached.\n");
// 	if (errno == ENOENT)
// 		printf("O_CREAT is not set and the named file does not exist.\n");
// 	if (errno == ETXTBSY)
// 		printf("`%s' refers to an executable image which is currently "
// 			"being executed and write access was requested.\n", path);
// }