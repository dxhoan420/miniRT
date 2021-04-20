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

typedef struct	s_checker
{
	int		line_counter;
	char	letter_a;
	char	letter_r;
}				t_count;

void	add_sphere(t_all *scene, t_vec center, float diameter, t_rgb rgb);
void	add_plane(t_all *scene, t_vec point, t_vec norm, t_rgb rgb);
void	add_triangle(t_all *scene, t_vec one, t_ray two_three, t_rgb rgb);
void	add_square(t_all *scene, t_ray cntr_n_nrm, float size, t_rgb rgb);
void	add_cylinder(t_all *scene, t_ray one_two, t_vec d_n_h, t_rgb rgb);
void	add_camera(t_all *scene, t_vec point, t_vec normal, float fov);
void	add_light(t_all *scene, t_vec coordinates, t_rgb rgb_norm);
char	*set_vector(char *string, t_vec *vector, t_vector_type type);
char	*set_float(char *str, float *result);
char	*set_rgb(char *string, t_rgb *rgb);
void	parse_screen_resolution(t_all *scene, char *string, t_count *checks);
void	parse_ambient(t_all *scene, char *line, t_count *checks);
void	parse_camera(t_all *scene, char *line);
void	parse_light(t_all *scene, char *line);
void	parse_sphere(t_all *scene, char *line);
void	parse_plane(t_all *scene, char *line);
void	parse_square(t_all *scene, char *line);
void	parse_cylinder(t_all *scene, char *line);
void	parse_triangle(t_all *scene, char *line);
void	parser_error(char *message, int number);
int		is_start(char **string, char first, char second);
int		skip_space(char **string);
int		skip_space_comma(char **string);

#endif
