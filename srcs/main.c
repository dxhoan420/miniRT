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

#include "miniRT.h"

int	main (int argc, char **argv)
{
	void		*mlx;
	void		*window;
	t_all		scene;
	t_cameras	*cameras = NULL;

	if (argc > 1)
		parser(&scene, &cameras, argv[1]);
	mlx = mlx_init();
	scene.camera = *cameras;
	window = mlx_new_window(mlx, scene.x_res, scene.y_res, "OK");
	render_scene(mlx, window, scene);
	mlx_loop(mlx);
	return (0);
}
