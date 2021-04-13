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
	viewport.mlx_y = 0;
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

int	mlx_or_bmp(t_all scene, t_vec cam_dir)
{
	int color;

	cam_dir = get_orient_dir(cam_dir, scene.cameras->orient);
	color = get_pixel_color(scene, create_ray(scene.cameras->point, cam_dir));
	return (color);
}

void	render_scene(t_all scene, int bmp, int *picture)
{
	t_viewport	viewport;
	int			color;

	viewport = get_viewport(scene.x_res, scene.y_res, scene.cameras->fov);
	while (viewport.mlx_y < scene.y_res)
	{
		viewport.dir.x = (-(float)scene.x_res / 2) * viewport.x_pixel;
		viewport.mlx_x = 0;
		while (viewport.mlx_x < scene.x_res)
		{
			color = mlx_or_bmp(scene, viewport.dir);
			if (!bmp)
				mlx_pixel_put(scene.engine.mlx, scene.engine.win,
								 viewport.mlx_x, viewport.mlx_y,color);
			else
				picture[viewport.mlx_x + viewport.mlx_y * scene.x_res] = color;
			viewport.dir.x += viewport.x_pixel;
			viewport.mlx_x++;
		}
		viewport.dir.y -= viewport.y_pixel;
		viewport.mlx_y++;
	}
}
