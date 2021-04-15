//
// Created by Demeter Xhoan on 2/24/21.
//

#include "miniRT.h"

typedef struct s_viewport
{
	float	x_size;
	float	y_size;
	float	x_pixel;
	float	y_pixel;
	int		mlx_x;
	int		mlx_y;
	t_vec	dir;
}			t_viewport;

t_viewport	get_viewport(int x_resolution, int y_resolution, float fov)
{
	t_viewport	viewport;
	float		ratio;

	ratio = (float) x_resolution / (float) y_resolution;
	viewport.x_size = (float)(2 * tan(fov / 2 / 180 * M_PI));
	viewport.y_size = viewport.x_size / ratio;
	viewport.x_pixel = viewport.x_size / (float) x_resolution;
	viewport.y_pixel = viewport.y_size / (float) y_resolution;
	viewport.dir.z = 1;
	viewport.dir.y = (float)y_resolution / 2 * viewport.y_pixel;
	return (viewport);
}

t_vec	get_orient_dir(t_vec origin, t_vec tz)
{
	t_vec	tx;
	t_vec	ty;
	t_vec	result_ray;

	tz.x *= -1;
	tz.y *= -1;
	tx = vector_norm(vecs_cross(create_vector(0, 1, 0), tz));
	ty = vector_norm(vecs_cross(tz, tx));
	result_ray.x = origin.x * tx.x + origin.y * tx.y + origin.z * tx.z;
	result_ray.y = origin.x * ty.x + origin.y * ty.y + origin.z * ty.z;
	result_ray.z = origin.x * tz.x + origin.y * tz.y + origin.z * tz.z;
	return (vector_norm(result_ray));
}

void	mlx_or_bmp(t_all scene, t_viewport	viewport, int *picture)
{
	int		color;
	t_ray	ray;

	viewport.dir = get_orient_dir(viewport.dir, scene.cameras->orient);
	ray = create_ray(scene.cameras->point, viewport.dir);
	color = get_pixel_color(scene, ray);
	if (!picture)
		mlx_pixel_put(scene.mlx, scene.win, viewport.mlx_x,
			viewport.mlx_y, color);
	else
		picture[(scene.y_res - viewport.mlx_y) *scene.x_res
			- (scene.x_res - viewport.mlx_x)] = color;
}

void	render_scene(t_all scene, int *picture)
{
	t_viewport	viewport;

	viewport = get_viewport(scene.x_res, scene.y_res, scene.cameras->fov);
	viewport.mlx_y = 0;
	while (viewport.mlx_y < scene.y_res)
	{
		viewport.dir.x = (-(float)scene.x_res / 2) * viewport.x_pixel;
		viewport.mlx_x = 0;
		while (viewport.mlx_x < scene.x_res)
		{
			mlx_or_bmp(scene, viewport, picture);
			viewport.dir.x += viewport.x_pixel;
			viewport.mlx_x++;
		}
		viewport.dir.y -= viewport.y_pixel;
		viewport.mlx_y++;
	}
}
