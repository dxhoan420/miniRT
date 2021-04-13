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
	render_scene(*scene, NULL);
	return (direction);
}

int	key_hook(int keycode, t_all *scene)
{
	if (keycode == 53)
		window_close(scene);
	if (keycode == 124 || keycode == 125)
		return (change_camera(scene, FORWARD));
	if (keycode == 123 || keycode == 126)
		return (change_camera(scene, BACKWARD));
	return (keycode);
}

int has_rt(char *filename)
{
	while (*filename)
		filename++;
	if (*--filename == 't')
		if (*--filename == 'r')
			if (*--filename == '.')
				if (*--filename != '\0')
					return (1);
	return (0);
}

int	main (int argc, char **argv)
{
	t_all		scene;

	if (argc < 2)
		return (0);
	if (!has_rt(argv[1]))
		error("WRONG FILE EXTENSION: need *.rt files", argv[1]);
	parser(&scene, argv[1]);
	if (argc > 2)
		start_bmp_n_exit(argv[1], argv[2], scene);
	if (scene.x_res > WIDTH)
		scene.x_res = WIDTH;
	if (scene.y_res > HEIGHT)
		scene.y_res = HEIGHT;
	scene.engine.mlx = mlx_init();
	scene.engine.win = mlx_new_window(scene.engine.mlx,
									scene.x_res, scene.y_res, "miniRT");
	render_scene(scene, NULL);
	mlx_key_hook(scene.engine.win, key_hook, &scene);
	mlx_hook(scene.engine.win, 17, 0L, window_close, &scene);
	mlx_loop(scene.engine.mlx);
	return (0);
}
