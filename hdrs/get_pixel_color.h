//
// Created by Demeter Xhoan on 3/14/21.
//

#ifndef MINIRT_GET_PIXEL_COLOR_H
#define MINIRT_GET_PIXEL_COLOR_H

#include "../hdrs/miniRT.h"
# define SHINE	250
//100000 minimum for dark scene
# define SHADOW_NOISE_REDUCTION	100000

struct s_figure	*get_figure(t_ray ray, t_figures *figures, int first_or_closer);
void			set_values(struct s_figure *figure, float dist, t_ray ray);

#endif //MINIRT_GET_PIXEL_COLOR_H
