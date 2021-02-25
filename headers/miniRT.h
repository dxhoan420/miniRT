//
// Created by Demeter Xhoan on 2/20/21.
//

#ifndef MINIRT_MINIRT_H
#define MINIRT_MINIRT_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vector.h"

typedef struct		s_camera
{
	t_vector		coordinates;
	t_vector		norma_vector;
	int				field_of_view;
	struct s_camera	*next;
}					t_cameras;

typedef struct		s_sphere
{
	t_vector		coordinates;
	float			radius;
	int				color;
	struct s_sphere	*next;
}					t_spheres;

typedef struct		s_light
{
	t_vector		coordinates;
	float			brightness;
	int 			color;
	struct s_light	*next;
}					t_lights;

typedef struct		s_plane
{
	t_vector		coordinates;
	t_vector		norma_vector;
	int 			color;
//	struct s_plane	*next;
}					t_plane;

typedef struct		s_square
{
	t_vector		coordinates;
	t_vector		norma_vector;
	int				size;
	int 			color;
//	struct s_square	*next;
}					t_square;

typedef struct			s_cylinder
{
	t_vector			coordinates;
	t_vector			norma_vector;
	int 				diameter;
	int 				height;
	int					color;
//	struct s_cylinder	*next;
}						t_cylinder;

typedef struct 			s_triangle
{
	t_vector			one;
	t_vector			two;
	t_vector			three;
	int 				color;
//	struct s_triangle	*next;
}						t_triangle;

//typedef struct			s_figures
//{
//	char 				type;
//	int					color;
//	void 				*current;
//	struct s_figures	*next;
//}						t_all_figures;

typedef struct		s_all
{
	int				x_resolution;
	int				y_resolution;
	float			ambient;
	int				color;
	t_cameras		*cameras;
	t_lights		*lights;
	t_spheres		*spheres;
}					t_all;

t_all		add_sphere(t_all scene, t_vector coordinates, float diameter,
				 int color);
float		distance_to_sphere(struct s_camera camera, t_vector ray,
		struct s_sphere sphere);
t_all		add_camera(t_all scene, t_vector coordinates, t_vector
				norma_vector,
					  int field_of_view);


typedef struct			s_viewport
{
	float width;
	float height;
	float x_pixel;
	float y_pixel;
}						t_viewport;

t_viewport	get_viewport(int x_resolution, int y_resolution, int fov);
void		super_ray_tracing(void *mlx, void *window, t_all scene);

#endif //MINIRT_MINIRT_H
