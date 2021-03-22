/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dxhoan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:15:29 by dxhoan            #+#    #+#             */
/*   Updated: 2020/11/24 14:15:31 by dxhoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ft_s;

	ft_s = (char *)s;
	while (*ft_s != '\0')
	{
		if (*ft_s == (char) c)
			return (ft_s);
		else
			ft_s++;
	}
	if ((char)c == '\0')
		return (ft_s);
	return (NULL);
}

int	concat_substr(char **line, char *src, char c)
{
	char	*result;
	size_t	src_len;
	size_t	line_len;
	size_t	i;

	src_len = (ft_strchr(src, c) - src);
	if (*line)
		line_len = ft_strchr(*line, '\0') - *line;
	else
		line_len = 0;
	result = malloc(src_len + line_len + SIZE_OF_CHAR);
	if (result == NULL)
		return (ERROR);
	i = 0;
	while (i < line_len)
	{
		result[i] = (*line)[i];
		i++;
	}
	free(*line);
	while (src_len-- > 0)
		result[i++] = *src++;
	result[i] = '\0';
	*line = result;
	return (END_OF_BUFFER);
}

void	move_inside_buff(char *buff)
{
	char	*src;

	src = ft_strchr(buff, '\n') + SIZE_OF_CHAR;
	while (*src != '\0')
		*buff++ = *src++;
	*buff = '\0';
}
