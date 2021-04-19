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

char	*check_n_set_filename(int argc, char **argv)
{
	char	*filename;

	if (argc < 2)
	{
		printf("Need *.rt file in first argument for successful launch");
		exit (-1);
	}
	filename = argv[1];
	while (*filename)
		filename++;
	if (*--filename == 't')
		if (*--filename == 'r')
			if (*--filename == '.')
				if (*--filename != '\0')
					return (argv[1]);
	error("WRONG FILE EXTENSION: need *.rt files", argv[1]);
	return (NULL);
}

int	main (int argc, char **argv)
{
	t_all		scene;
	int			width;
	int			height;

	scene = init_scene(check_n_set_filename(argc, argv));
	parser(&scene);
	if (argc > 2)
		start_bmp_n_exit(argv[1], argv[2], scene);
	mlx_get_screen_size(&width, &height);
	if (scene.x_res > width)
		scene.x_res = width;
	if (scene.y_res > height)
		scene.y_res = height;
	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx,
			scene.x_res, scene.y_res, "miniRT");
	render_scene(scene, NULL);
	mlx_key_hook(scene.win, key_hook, &scene);
	mlx_hook(scene.win, 17, 0L, window_close, &scene);
	mlx_loop(scene.mlx);
	return (0);
}

int	window_close(t_all *scene)
{
	mlx_clear_window(scene->mlx, scene->win);
	mlx_destroy_window(scene->mlx, scene->win);
	exit(0);
}

void	error(char *message, char *place)
{
	printf("Error\n%s\nHERE: %s\n", message, place);
	exit(-1);
}

t_all	init_scene(char *filename)
{
	t_all	scene;

	scene.filename = filename;
	scene.x_res = -1;
	scene.y_res = -1;
	scene.ambient_rgb_norm = create_rgb_norm(0, 0, 0, 0);
	scene.cameras = NULL;
	scene.lights = NULL;
	scene.figures = NULL;
	scene.step_size = 1;
	return (scene);
}
