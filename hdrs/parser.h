//
// Created by Demeter Xhoan on 3/22/21.
//

#ifndef PARSER_H
# define PARSER_H

# include "get_next_line.h"
# include "miniRT.h"
# include <fcntl.h>

typedef enum e_vector_type
{
	POINT,
	NORMAL
}			t_vector_type;

typedef enum e_color_type
{
	LIGHT,
	FIGURE
}			t_color_type;

void	set_other(char *string, t_all *scene);
char	*set_vector(char *string, t_vec *vector, t_vector_type type);
char	*set_float(char *str, float *result);
void	error(char *message, char *place);
void	set_sphere(char *string, t_all *scene);
void	set_plane(char *string, t_all *scene);
void	set_triangle(char *string, t_all *scene);
void	set_square(char *string, t_all *scene);
void	set_cylinder(char *string, t_all *scene);
void	set_camera(char *string, t_all *scene);
char	*set_rgb(char *string, t_rgb *rgb, t_color_type type);

#endif
