/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:13:40 by ymauk             #+#    #+#             */
/*   Updated: 2024/07/04 12:36:44 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *text)
{
	int			text_read;
	char		*part_buffer;

	part_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (part_buffer == NULL)
		return (0);
	text_read = 1;
	while (!ft_strchr_gnl(text, '\n') && text_read != 0)
	{
		text_read = read(fd, part_buffer, BUFFER_SIZE);
		if (text_read == -1)
		{
			free(part_buffer);
			free (text);
			return (NULL);
		}
		part_buffer[text_read] = '\0';
		text = ft_strjoin_gnl(text, part_buffer);
	}
	free (part_buffer);
	return (text);
}

char	*first_and_rest(char **text)
{
	int			i;
	char		*first_line;
	char		*t;

	i = 0;
	if (text[0][0] == '\0')
	{
		return (NULL);
	}
	while (text[0][i] != '\n' && text[0][i] != '\0')
		i++;
	first_line = ft_substr_gnl(*text, 0, i + 1);
	t = ft_substr_gnl(*text, i + 1, ft_strlen_gnl(*text) - i);
	free (*text);
	*text = t;
	return (first_line);
}

char	*get_next_line(int fd)
{
	static char	*text = NULL;
	char		*clean;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) == -1)
	{
		free (text);
		text = NULL;
		return (NULL);
	}
	text = read_line(fd, text);
	if (text == NULL)
		return (NULL);
	clean = first_and_rest(&text);
	if (clean == NULL)
	{
		if (text != NULL)
		{
			free (text);
			text = NULL;
		}
		return (NULL);
	}
	return (clean);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*filename;
// 	char	*next_line;
// 	int		count;

// 	count = 0;
// 	filename = "textfile1.txt";
// 	fd = open(filename, O_RDONLY);
// 	next_line = get_next_line(fd);
// 	printf("%s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("%s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("%s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("%s", next_line);
// 	free(next_line);
// 	close(fd);
// 	return (0);
// }
