/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dxhoan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:15:06 by dxhoan            #+#    #+#             */
/*   Updated: 2020/11/24 14:15:12 by dxhoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Was shit, will candy!
*/

int	get_next_line(int fd, char **line)
{
	static char	*buffer;
	int			have_nl;
	ssize_t		len;

	if (line == NULL)
		return (ERROR);
	*line = NULL;
	have_nl = buff_n_line_init(&buffer, line);
	if (have_nl == ERROR || fd < 0)
		return (ERROR);
	if (have_nl == FIND_NEW_LINE)
		return (FIND_NEW_LINE);
	len = read(fd, buffer, BUFFER_SIZE);
	while (len)
	{
		buffer[len] = '\0';
		have_nl = buff_n_line_init(&buffer, line);
		if (have_nl != END_OF_BUFFER)
			return (have_nl);
		len = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	buffer = NULL;
	return (END_OF_STREAM);
}

int	buff_n_line_init(char **buff, char **line)
{
	int	test;

	test = BUFFER_SIZE;
	if (test < 1)
		return (ERROR);
	if (*line == NULL)
	{
		*line = malloc(1);
		**line = '\0';
	}
	if (*buff == NULL)
	{
		*buff = malloc(BUFFER_SIZE + SIZE_OF_CHAR);
		if (*buff == NULL)
			return (ERROR);
		else
			return (END_OF_BUFFER);
	}
	if (ft_strchr(*buff, '\n'))
	{
		concat_substr(line, *buff, '\n');
		move_inside_buff(*buff);
		return (FIND_NEW_LINE);
	}
	return (concat_substr(line, *buff, '\0'));
}
