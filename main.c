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

int main (int argc, char **argv)
{
	void    *mlx;
	void    *window;
	t_all 	scene;

	if (argc != 3)
		return (1);

	scene.x_resolution = atoi(argv[1]);
	scene.y_resolution = atoi(argv[2]);
	scene.ambient_ratio = 0.9999f;
	scene.color = color_to_rgb();
	scene.ambient_g = 255;
	scene.ambient_b = 255;
	scene = add_sphere(scene, get_new_vector(1, 0, -4), 1,
					create_rgb(255,0,0));
	scene = add_sphere(scene, get_new_vector(-1, -1, -5), 1,
					   create_rgb(0,0,255));
	scene = add_sphere(scene, get_new_vector(1, -1, -5), 1,
					create_rgb(255,255,0));
	scene = add_sphere(scene, get_new_vector(-1, 1, -5), 1,
					   create_rgb(255,0,253));
	scene = add_sphere(scene, get_new_vector(1, 1, -6), 1,
					create_rgb(0,250,0));
	scene = add_sphere(scene, get_new_vector(-1, 0, -5), 1,
					   create_rgb(255,255,255));
	scene = add_camera(scene, get_new_vector(0, 0, 0),
					   get_new_vector(0, 0, -1), 50);
	scene = add_light(scene, get_new_vector(2, 2, 2), 0.999f,
				   create_rgb(255,255,255));
	mlx = mlx_init();
	window = mlx_new_window(mlx, scene.x_resolution, scene.y_resolution,
							"TEST EBAT!11odin");
	super_ray_tracing(mlx, window, scene);
	mlx_loop(mlx);

	return (0);
}
