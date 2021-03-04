/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dxhoan <dxhoan@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:48:52 by dxhoan            #+#    #+#             */
/*   Updated: 2021/02/20 15:16:14 by dxhoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/miniRT.h"

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int main (int argc, char **argv)
{
	void    *mlx;
	void    *window;
	t_all 	scene;

	if (argc != 3)
		return (1);

	scene.x_resolution = atoi(argv[1]);
	scene.y_resolution = atoi(argv[2]);
	scene = add_sphere(scene, get_new_vector(0, 0, -3), 1,
					create_rgb(200,0,0));
//	scene = add_sphere(scene, get_new_vector(-1, -1, -5), 1,
//					   create_rgb(0,0,200));
//	scene = add_sphere(scene, get_new_vector(1, -1, -5), 1,
//					create_rgb(200,200,0));
//	scene = add_sphere(scene, get_new_vector(-1, 1, -5), 1,
//					   create_rgb(0,200,200));
//	scene = add_sphere(scene, get_new_vector(1, -1, -6), 2,
//					create_rgb(250,250,250));
	scene = add_sphere(scene, get_new_vector(0, 0, -2), 4,
					   create_rgb(250,250,250));

	//printf("Just add first sphere.\n");
	scene = add_camera(scene, get_new_vector(0, 0, 0),
					   get_new_vector(0, 0, -1), 50);
	//printf("Just add camera.\n");

	//printf("Resolution : %d x %s\n", atoi(argv[1]), argv[2]);
	mlx = mlx_init();
	window = mlx_new_window(mlx, scene.x_resolution, scene.y_resolution,
							"TEST EBAT!11odin");
//	for (int i = 100; i < 300; i++)
//		for (int j = 100; j < 150; j++)
//			mlx_pixel_put(mlx, window, i, j, 16777215);
	super_ray_tracing(mlx, window, scene);
	mlx_loop(mlx);

	return (0);
}

//void init_all (t_all *scene)
//{
//	scene->x_resolution		= -1;
//	scene->y_resolution		= -1;
//	scene->ambient			= -1;
//	scene->color			= -1;
//	scene->cameras			= NULL;
//	scene->lights			= NULL;
//	scene->spheres			= NULL;
//}
