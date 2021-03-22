/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dxhoan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:15:17 by dxhoan            #+#    #+#             */
/*   Updated: 2020/11/24 14:15:20 by dxhoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1024
# define END_OF_BUFFER	0
# define END_OF_STREAM	0
# define FIND_NEW_LINE	1
# define ERROR			-1
# define SIZE_OF_CHAR	1
# include <unistd.h>
# include <stdlib.h>

int			get_next_line(int fd, char **line);
void		move_inside_buff(char *buff);
char		*ft_strchr(const char *s, int c);
int			concat_substr(char **line, char *src, char c);
int			buff_n_line_init(char **buff, char **line);

#endif
