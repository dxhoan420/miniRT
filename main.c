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

#include "./hdrs/miniRT.h"

int main (int argc, char **argv)
{
	void    	*mlx;
	void    	*window;
	t_all 		scene;
	t_cameras	*cameras = NULL;

	if (argc != 3)
		return (1);

	scene.x_resolution = atoi(argv[1]);
	scene.y_resolution = atoi(argv[2]);
	scene.ambient_rgb_norm = create_rgb_norm(255, 255, 255, 0.3f);
	add_sphere(&scene, create_vector(1, -0.5f, 5), 2,create_rgb(WHITE));
	add_sphere(&scene, create_vector(1, -1, 2), 1,create_rgb(WHITE));
	add_sphere(&scene, create_vector(0, 0, 7), 3,create_rgb(WHITE));
	add_sphere(&scene, create_vector(0, 0, -100), 20,create_rgb(WHITE));
	add_camera(&cameras, create_vector(0, 0, -3),
					create_vector(0, 0, 1), 60);
	add_light(&scene, create_vector(4, -2, 0),
				   create_rgb_norm(255, 255, 255, 0.7f));
//	add_light(&scene, create_vector(-5, 10, 0),
//				   create_rgb_norm(255, 255, 255, 0.3f));
//	add_light(&scene, create_vector(0, 4, -7),
//				   create_rgb_norm(255, 255, 255, 0.3f));
	mlx = mlx_init();
	scene.camera = *cameras;
	window = mlx_new_window(mlx, scene.x_resolution, scene.y_resolution,"OK");
	render_scene(mlx, window, scene);
	mlx_loop(mlx);

	return (0);
}
