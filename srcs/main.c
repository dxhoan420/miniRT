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

#include "../hdrs/miniRT.h"

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
	scene.ambient_rgb_norm = create_rgb_norm(255, 255, 255, 0.2f);
//	add_sphere(&scene, create_vector(-2, 1, 4), 1,create_rgb(WHITE));
//	add_sphere(&scene, create_vector(1, -0.9f, 5), 2,create_rgb(WHITE));
//	add_sphere(&scene, create_vector(0, 0, 7), 3,create_rgb(WHITE));
//	add_sphere(&scene, create_vector(10, 0, 20), 20,create_rgb(WHITE));
	add_plane(&scene, create_vector(0, 0, 200), create_vector(0, 0, -0.5f),
		   create_rgb(RED));
//	add_plane(&scene, create_vector(60, 0, 0), create_vector(1, 0.1f, 0),
//		   create_rgb(GREEN));
//	add_plane(&scene, create_vector(0, 1, 0), create_vector(0, -1, 0),
//		   create_rgb(BLUE));
//	add_plane(&scene, create_vector(0, -60, 0), create_vector(0, 1, 0.1f),
//		   create_rgb(WHITE));
	add_camera(&cameras, create_vector( 0, 0, -10),
					create_vector(0, 0, 1), 90);
//	add_light(&scene, create_vector(0, 2, 1),
//				   create_rgb_norm(255, 255, 255, 0.4f));
	add_light(&scene, create_vector(3, 0, -1),
				   create_rgb_norm(255, 255, 255, 0.4f));
//	add_light(&scene, create_vector(-5, 10, 0),
//				   create_rgb_norm(255, 255, 255, 0.2f));
//	add_light(&scene, create_vector(0, 4, -7),
//				   create_rgb_norm(255, 255, 255, 0.2f));
//	add_sphere(&scene, create_vector(1, 0, 6), 2,create_rgb(RED));
//	add_sphere(&scene, create_vector(0, 0, 0), 500,create_rgb(BLUE));
//	add_sphere(&scene, create_vector(1, -1, 5), 1,create_rgb(255, 255, 0));
//	add_sphere(&scene, create_vector(-1, 1, 6), 2,create_rgb(255, 0, 253));
//	add_sphere(&scene, create_vector(1, 1, 5.5f), 1,create_rgb(GREEN));
//	add_sphere(&scene, create_vector(0, -8.5f, 5), 15,create_rgb(WHITE));
//	add_sphere(&scene, create_vector(1, 0, 3), 0.3f,create_rgb(RED));
//	add_sphere(&scene, create_vector(-1, 0, 3), 0.3f,create_rgb(RED));
//	add_triangle(&scene, create_vector(2, 0, 4),
//create_ray(create_vector(1,1, 4),
//		   create_vector(1, -1, 4)),create_rgb(BLUE));
//	add_square(&scene, create_ray(create_vector(0, 0, 4),
//   create_vector(0, 1, 0)), 5, create_rgb(GREEN));
	add_cylinder(&scene, create_ray(create_vector(0, 0, 0),
 create_vector(0.4f, 0,1)), create_vector(3, 4, 42), create_rgb(255,255,
																  255));
//	add_sphere(&scene, create_vector(-2, 1, 4), 0.3f,create_rgb(RED));
//	add_sphere(&scene, create_vector(-2, -1, 4), 0.3f,create_rgb(RED));
//	add_sphere(&scene, create_vector(0, 1, 4), 0.3f,create_rgb(RED));
//	add_sphere(&scene, create_vector(0, -1, 4), 0.3f,create_rgb(RED));
//	add_sphere(&scene, create_vector(2, 0, 3), 0.3f,create_rgb(RED));
//	add_sphere(&scene, create_vector(1.5f, 0, 3), 0.3f,create_rgb(RED));
//	add_sphere(&scene, create_vector(0.5f, 0, 3), 0.3f,create_rgb(RED));
//	add_sphere(&scene, create_vector(0, -0.5f, -5), 15,create_rgb(WHITE));
//	add_sphere(&scene, create_vector(0, 0, 6), 1.5f,create_rgb(WHITE));
//	add_camera(&cameras, create_vector(0, 0, 0),
//					   create_vector(0, 0, 1), 90);
//	add_light(&scene, create_vector(0, 1, 2),
//					  create_rgb_norm(0, 255, 255, 0.3f));
//	add_light(&scene, create_vector(4, 4, -2),
//				   create_rgb_norm(255, 0, 255, 0.3f));
//	add_light(&scene, create_vector(0, 1, 2),
//				   create_rgb_norm(255, 255, 0, 0.3f));
	mlx = mlx_init();
	scene.camera = *cameras;
	window = mlx_new_window(mlx, scene.x_resolution, scene.y_resolution,"OK");
	render_scene(mlx, window, scene);
	mlx_loop(mlx);

	return (0);
}
