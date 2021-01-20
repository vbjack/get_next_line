/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrey <andrey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:45:49 by andrey            #+#    #+#             */
/*   Updated: 2020/12/03 23:08:36 by andrey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	free_mem(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (-1);
}

static int	next_line(int fd, char **line, char **s_tail, char *tmp)
{
	char	*buf;
	char	*c;
	int		size_read;

	c = NULL;
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!c && (size_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[size_read] = '\0';
		if ((c = ft_strchr(buf, '\n')))
		{
			*c++ = '\0';
			if (*c)
				*s_tail = ft_strdup(c);
		}
		if (!(tmp = ft_strjoin(*line, buf)))
			return (free_mem(*line, tmp));
		free(*line);
		*line = tmp;
	}
	free(buf);
	if (size_read == -1)
		return (free_mem(*s_tail, *s_tail));
	return ((*s_tail || size_read) ? 1 : 0);
}

static int	tail_line(int fd, char **line, char **s_tail)
{
	char	*c;
	char	*tmp;

	tmp = NULL;
	if (*s_tail && (c = ft_strchr(*s_tail, '\n')))
	{
		*c++ = '\0';
		tmp = *s_tail;
		free(*line);
		*line = ft_strdup(*s_tail);
		if (!(*line) || (!(*s_tail = ft_strdup(c))))
			return (free_mem(*s_tail, *line));
		free(tmp);
		return (1);
	}
	else if (*s_tail)
	{
		free(*line);
		if (!(*line = ft_strdup(*s_tail)))
			return (-1);
		free(*s_tail);
		*s_tail = NULL;
	}
	return (next_line(fd, line, s_tail, tmp));
}

int			get_next_line(int fd, char **line)
{
	static char	*s_tail;

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) < 0)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char))))
		return (-1);
	**line = '\0';
	return (tail_line(fd, line, &s_tail));
}
