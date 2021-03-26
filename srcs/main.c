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

typedef struct s_engine_scene_cams
{
	t_mlx		*engine;
	t_all		*scene;
	t_cameras	*cameras;
}				t_esc;

int	window_close(t_mlx *engine)
{
	mlx_clear_window(engine->mlx, engine->win);
	mlx_destroy_window(engine->mlx, engine->win);
	exit(0);
}

int	key_hook(int keycode, t_mlx *engine)
{
	if (keycode == 53)
		window_close(engine);
	return (keycode);
}

int	main (int argc, char **argv)
{
	t_mlx		engine;
	t_all		scene;
	t_cameras	*cameras = NULL;

	if (argc > 1)
		parser(&scene, &cameras, argv[1]);
	engine.mlx = mlx_init();
	scene.camera = *cameras;
	engine.win = mlx_new_window(engine.mlx, scene.x_res, scene.y_res, "OK");
	render_scene(engine, scene);
	mlx_key_hook(engine.win, key_hook, &engine);
	mlx_hook(engine.win, 17, 0L, window_close, &engine);
	mlx_loop(engine.mlx);
	return (0);
}
