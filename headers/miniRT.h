//
// Created by Demeter Xhoan on 2/20/21.
//

#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "vector.h"

typedef enum			e_id
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
	TRIANGLE
}						t_id;

typedef struct			s_camera
{
	t_vector		coordinates;
	t_vector		norma_vector;
	int				field_of_view;
	struct s_camera	*next;
}					t_cameras;

typedef struct			s_light
{
	t_vector		coordinates;
	float			brightness;
	int 			color;
	struct s_light	*next;
}						t_lights;

typedef struct			s_figure
{
	int				color;
	t_vector		first_or_center;
	t_vector		second_or_norma;
	t_vector		third;
	float			radius_or_size;
	float			height;
	t_id 			id;

	struct s_figure	*next;
}						t_figures;

typedef struct		s_all
{
	int				x_resolution;
	int				y_resolution;
	float			ambient;
	int				color;
	t_cameras		*cameras;
	t_lights		*lights;
	t_figures		*figures;
}					t_all;


t_all		add_sphere(t_all scene, t_vector coordinates, float diameter,
				 int color);
float		distance_to_sphere(struct s_camera camera, t_vector ray,
		struct s_figure sphere);
t_all		add_camera(t_all scene, t_vector coordinates, t_vector
				norma_vector,
					  int field_of_view);


typedef struct			s_viewport
{
	float x_size;
	float y_size;
	float x_pixel;
	float y_pixel;
}						t_viewport;

t_viewport			get_viewport(int x_resolution, int y_resolution, int fov);
void				super_ray_tracing(void *mlx, void *window, t_all scene);
//void				new_ray_tracing(void *mlx, void *window, t_all scene);

#endif //MINIRT_MINIRT_H
