//
// Created by Demeter Xhoan on 2/20/21.
//

#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <float.h>

# include "vector.h"
# include "color.h"

# define SHINE	50
# define SHADOW_NOISE_REDUCTION	10000
# define CLOSER	0
# define FIRST	1

typedef enum			e_id
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
	TRIANGLE
}						t_id;

typedef enum 			e_side
{
	INNER,
	OUTER
}						t_side;

typedef struct			s_camera
{
	t_vector		coordinates;
	t_vector		norma_vector;
	int				field_of_view;
	struct s_camera	*next;
}					t_cameras;

typedef struct			s_light
{
	t_vector		src;
	t_rgb			rgb_norm;
	struct s_light	*next;
}						t_lights;

typedef struct			s_figure
{
	t_rgb 			rgb;
	t_vector		first_or_center;
	t_vector		second;
	t_vector		third;
	float			radius_or_size;
	float			height;
	float			dist;
	t_vector		crossing;
	t_vector		normal;
	t_id 			id;
	t_side			side;

	struct s_figure	*next;
}						t_figures;

typedef struct		s_all
{
	int				x_resolution;
	int				y_resolution;
	t_rgb			ambient_rgb_norm;
	t_cameras		camera;
	t_lights		*lights;
	t_figures		*figures;
}					t_all;


void		add_sphere(t_all *scene, t_vector center, float diameter,
					   t_rgb rgb);
void		add_plane(t_all *scene, t_vector coordinates, t_vector norm,
				t_rgb rgb);
float		distance_to_plane(t_ray ray, struct s_figure *plane);
float		distance_to_sphere(t_ray ray, struct s_figure *sphere);
void		add_camera(t_cameras **cameras, t_vector coordinates,
				   t_vector norma_vector,int field_of_view);
void		add_light(t_all *scene, t_vector coordinates, t_rgb rgb_norm);

typedef struct			s_viewport
{
	float x_size;
	float y_size;
	float x_pixel;
	float y_pixel;
}						t_viewport;

void		render_scene(void *mlx, void *window, t_all scene);

#endif //MINIRT_MINIRT_H
