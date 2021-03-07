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
	scene.ambient_rgb_norm = create_rgb_norm(255, 255, 255, 0.999f);
	scene = add_sphere(scene, create_vector(1, 0, -6), 2,
					   create_rgb(RED));
	scene = add_sphere(scene, create_vector(-1, -1, -5), 1,
					   create_rgb(BLUE));
	scene = add_sphere(scene, create_vector(1, -1, -5), 1,
					   create_rgb(255, 255, 0));
	scene = add_sphere(scene, create_vector(-1, 1, -5), 2,
					   create_rgb(255, 0, 253));
	scene = add_sphere(scene, create_vector(1, 1, -6), 1,
					   create_rgb(GREEN));
	scene = add_sphere(scene, create_vector(-1, 0, -5), 1,
					   create_rgb(WHITE));
	scene = add_camera(scene, create_vector(0, 0, 0),
					   create_vector(0, 0, -1), 50);
	scene = add_light(scene, create_vector(0, -4, 2),
					  create_rgb_norm(255, 255, 255, 0.99f));
	mlx = mlx_init();
	window = mlx_new_window(mlx, scene.x_resolution, scene.y_resolution,
							"MiniRT");
	super_ray_tracing(mlx, window, scene);
	mlx_loop(mlx);

	return (0);
}
