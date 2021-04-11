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

enum e_direction {
	BACKWARD,
	FORWARD
};

int	window_close(t_all *scene)
{
	mlx_clear_window(scene->engine.mlx, scene->engine.win);
	mlx_destroy_window(scene->engine.mlx, scene->engine.win);
	exit(0);
}

int	change_camera(t_all *scene, enum e_direction direction)
{
	if (scene->cameras->next == NULL || scene->cameras->prev == NULL)
		return (-1);
	if (direction == FORWARD)
		scene->cameras = scene->cameras->next;
	if (direction == BACKWARD)
		scene->cameras = scene->cameras->prev;
	render_scene(*scene);
	return (direction);
}

int	key_hook(int keycode, t_all *scene)
{
	if (keycode == 53)
		window_close(scene);
	if (keycode == 124 || keycode == 125)
		change_camera(scene, FORWARD);
	if (keycode == 123 || keycode == 126)
		change_camera(scene, BACKWARD);
	return (keycode);
}

int	main (int argc, char **argv)
{
	t_all		scene;

	if (argc > 1)
		parser(&scene, argv[1]);
	scene.engine.mlx = mlx_init();
	scene.engine.win = mlx_new_window(scene.engine.mlx,
									scene.x_res, scene.y_res, "miniRT");
	render_scene(scene);
	mlx_key_hook(scene.engine.win, key_hook, &scene);
	mlx_hook(scene.engine.win, 17, 0L, window_close, &scene);
	mlx_loop(scene.engine.mlx);
	return (0);
}
