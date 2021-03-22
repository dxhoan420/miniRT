//
// Created by Demeter Xhoan on 2/20/21.
//

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <float.h>

# include "vector.h"
# include "color.h"

# define SHINE	250
//100000 minimum for dark scene
# define SHADOW_NOISE_REDUCTION	100000

typedef enum e_type
{
	SPHERE,
	PLANE,
	TRIANGLE,
	SQUARE,
	CYLINDER
}			t_type;

typedef enum e_side
{
	INNER,
	OUTER
}			t_side;

typedef struct s_camera
{
	t_vec			coordinates;
	t_vec			norma_vector;
	float			field_of_view;
	struct s_camera	*next;
	struct s_camera	*prev;

}				t_cameras;

typedef struct s_light
{
	t_vec			src;
	t_vec			dir;
	t_rgb			rgb_norm;
	struct s_light	*next;
}				t_lights;

typedef struct s_figure
{
	t_type			type;
	t_rgb			rgb;
	t_vec			first;
	t_vec			second;
	t_vec			third;
	float			radius_or_size;
	float			height;
	t_vec			hit;
	t_vec			normal;
	t_side			side;
	float			(*get_distance)(t_ray ray, struct s_figure *figure);
	struct s_figure	*next;
}				t_figures;

typedef struct s_all
{
	int				x_resolution;
	int				y_resolution;
	t_rgb			ambient_rgb_norm;
	t_cameras		camera;
	t_lights		*lights;
	t_figures		*figures;
}				t_all;

void		add_sphere(t_all *scene, t_vec center, float diameter, t_rgb rgb);
void		add_plane(t_all *scene, t_vec point, t_vec norm, t_rgb rgb);
void		add_triangle(t_all *scene, t_vec one, t_ray two_three, t_rgb rgb);
void		add_square(t_all *scene, t_ray cntr_n_nrm, float size, t_rgb rgb);
void		add_cylinder(t_all *scene, t_ray one_two, t_vec d_n_h, t_rgb rgb);
void		add_camera(t_cameras **cams, t_vec point, t_vec normal, float fov);
void		add_light(t_all *scene, t_vec coordinates, t_rgb rgb_norm);
void		render_scene(void *mlx, void *window, t_all scene);
int			get_pixel_color(t_all scene, t_ray ray);
t_figures	*get_last_figure_of_scene(t_all *scene, t_rgb rgb);
void		parser (t_all *scene, t_cameras **cameras, char *filename);
#endif
