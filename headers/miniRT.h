//
// Created by Demeter Xhoan on 2/20/21.
//

#ifndef MINIRT_MINIRT_H
#define MINIRT_MINIRT_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct 	s_point
{
	float x;
	float y;
	float z;
}				t_point;

typedef struct		s_camera
{
	t_point			coordinates;
	t_point			norma_vector;
	int				field_of_view;
	struct s_camera	*next;
}					t_cameras;

typedef struct		s_light
{
	t_point			coordinates;
	float			brightness;
	int 			color;
	struct s_light	*next;
}					t_lights;

typedef struct		s_sphere
{
	t_point			coordinates;
	float			diameter;
	int				color;
//	struct s_sphere	*next;
}					t_sphere;

typedef struct		s_plane
{
	t_point			coordinates;
	t_point			norma_vector;
	int 			color;
//	struct s_plane	*next;
}					t_plane;

typedef struct		s_square
{
	t_point			coordinates;
	t_point			norma_vector;
	int				size;
	int 			color;
//	struct s_square	*next;
}					t_square;

typedef struct			s_cylinder
{
	t_point				coordinates;
	t_point				norma_vector;
	int 				diameter;
	int 				height;
	int					color;
//	struct s_cylinder	*next;
}						t_cylinder;

typedef struct 			s_triangle
{
	t_point				one;
	t_point				two;
	t_point				three;
	int 				color;
//	struct s_triangle	*next;
}						t_triangle;

typedef struct			s_figures
{
	char 				type;
//	int					color;
	void 				*current;
	struct s_figures	*next;
}						t_all_figures;

typedef struct		s_all
{
	int				x_resolution;
	int				y_resolution;
	float			ambient;
	int				color;
	t_cameras		*cameras;
	t_lights		*lights;
	t_all_figures	*figures;
}					t_all;

#endif //MINIRT_MINIRT_H
