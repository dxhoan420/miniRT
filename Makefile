# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dxhoan <dxhoan@student.21-school.>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 14:23:40 by dxhoan            #+#    #+#              #
#    Updated: 2021/02/20 15:31:21 by dxhoan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

SRCS	= $(addprefix srcs/, main.c camera.c ray_tracing.c color.c bmp.c\
							get_pixel_color.c get_figure.c key_hooks.c\
							$(GEOMETRY) $(PARSER))

PARSER	= $(addprefix parser/, get_next_line.c get_next_line_utils.c parser.c\
								choose_type.c choose_figure.c parser_setters.c)

GEOMETRY= $(addprefix geometry/, vector.c vectors_operation.c sphere.c plane.c\
								triangle.c cylinder.c)

HDRS	= $(addprefix hdrs/, miniRT.h vector.h color.h get_pixel_color.h\
							get_next_line.h parser.h)

OBJS	= $(SRCS:.c=.o)

LIBS	= -lmlx -framework OpenGL -framework AppKit

all		: $(NAME)

CFLAGS =  -I./hdrs -Wall -Wextra -Werror -g ## убрать это -gовно

$(NAME)	: $(OBJS) $(HDRS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

clean	:
	rm -f $(OBJS)

fclean	: clean
	rm -f $(NAME)

re		: fclean all

.PHONY	: all clean fclean re
