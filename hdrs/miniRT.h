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

# define CLOSER	0
# define FIRST	1

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
	t_vector		coordinates;
	t_vector		norma_vector;
	int				field_of_view;
	struct s_camera	*next;
	struct s_camera	*prev;

}				t_cameras;

typedef struct s_light
{
	t_vector		src;
	t_rgb			rgb_norm;
	struct s_light	*next;
}				t_lights;

typedef struct s_figure
{
	t_rgb			rgb;
	t_vector		first;
	t_vector		second;
	t_vector		third;
	float			radius_or_size;
	float			height;
	float			dist;
	t_vector		hit;
	t_vector		normal;
	t_type			type;
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

void	add_sphere(t_all *scene, t_vector center, float diameter, t_rgb rgb);
void	add_plane(t_all *scene, t_vector coordinates, t_vector norm, t_rgb rgb);
void	add_triangle(t_all *scene, t_vector first, t_ray sec_n_thr, t_rgb rgb);
void	add_camera(t_cameras **cameras, t_vector coordinates,
						t_vector norma_vector, int field_of_view);
void	add_light(t_all *scene, t_vector coordinates, t_rgb rgb_norm);
void	render_scene(void *mlx, void *window, t_all scene);
int		get_pixel_color(t_all scene, t_ray ray);
#endif
