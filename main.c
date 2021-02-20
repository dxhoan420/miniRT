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
	void    *mlx_win;

	if (argc == 3)
	{
		printf("Resolution : %d x %s\n", atoi(argv[1]), argv[2]);
		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx, atoi(argv[1]), atoi(argv[2]), argv[0]);
		for (int i = 100; i < 300; i++)
			for (int j = 100; j < 150; j++)
				mlx_pixel_put(mlx, mlx_win, i, j, 16777215);
		mlx_loop(mlx);
	}
	return (0);
}

void init_all (t_all *scene)
{
	scene->x_resolution		= -1;
	scene->y_resolution		= -1;
	scene->ambient			= -1;
	scene->color			= -1;
	scene->cameras			= NULL;
	scene->lights			= NULL;
	scene->figures			= malloc(sizeof(t_all_figures));
	scene->figures->type	= '\0';
	scene->figures->current	= NULL;
	scene->figures->next	= NULL;
}

