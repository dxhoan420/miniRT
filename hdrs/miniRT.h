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
# include <fcntl.h>
# include <unistd.h>

# include "vector.h"
# include "color.h"

# define SHINE	250
//Set next macro 100000 minimum for dark scene
# define SHADOW_NOISE_REDUCTION	100000
# define PROGRESS_BAR_SCALE	50

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
	t_vec			point;
	t_vec			orient;
	float			fov;
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
	float			rad_or_size;
	float			height;
	t_vec			hit;
	t_vec			normal;
	t_side			side;
	float			(*get_distance)(t_ray ray, struct s_figure *figure);
	struct s_figure	*next;
}				t_figures;

typedef struct s_all
{
	char		*filename;
	int			x_res;
	int			y_res;
	t_rgb		ambient_rgb_norm;
	t_cameras	*cameras;
	t_lights	*lights;
	t_figures	*figures;
	void		*mlx;
	void		*win;
	float		step_size;
}				t_all;

void		render_scene(t_all scene, int *picture);
int			get_pixel_color(t_all scene, t_ray ray);
t_figures	*get_last_figure_of_scene(t_all *scene, t_rgb rgb);
void		parser (t_all *scene);
void		error(char *message, char *place);
int			key_hook(int keycode, t_all *scene);
int			window_close(t_all *scene);
t_all		init_scene(char *filename);
void		start_bmp_n_exit(char *rt_filename, char *save, t_all scene);
void		mlx_get_screen_size(int *width, int *height);
#endif
