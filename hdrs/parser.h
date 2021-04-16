//
// Created by Demeter Xhoan on 3/22/21.
//

#ifndef PARSER_H
# define PARSER_H

# include "get_next_line.h"
# include "miniRT.h"

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

void	add_sphere(t_all *scene, t_vec center, float diameter, t_rgb rgb);
void	add_plane(t_all *scene, t_vec point, t_vec norm, t_rgb rgb);
void	add_triangle(t_all *scene, t_vec one, t_ray two_three, t_rgb rgb);
void	add_square(t_all *scene, t_ray cntr_n_nrm, float size, t_rgb rgb);
void	add_cylinder(t_all *scene, t_ray one_two, t_vec d_n_h, t_rgb rgb);
void	add_camera(t_all *scene, t_vec point, t_vec normal, float fov);
void	add_light(t_all *scene, t_vec coordinates, t_rgb rgb_norm);
void	set_other(char *string, t_all *scene);
char	*set_vector(char *string, t_vec *vector, t_vector_type type);
char	*set_float(char *str, float *result);
void	set_sphere(char *string, t_all *scene);
void	set_plane(char *string, t_all *scene);
void	set_triangle(char *string, t_all *scene);
void	set_square(char *string, t_all *scene);
void	set_cylinder(char *string, t_all *scene);
void	set_camera(char *string, t_all *scene);
char	*set_rgb(char *string, t_rgb *rgb, t_color_type type);

#endif
