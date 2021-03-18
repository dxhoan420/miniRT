//
// Created by Demeter Xhoan on 3/14/21.
//

#ifndef GET_PIXEL_COLOR_H
# define GET_PIXEL_COLOR_H

# include "../hdrs/miniRT.h"
# define CLOSER	0
# define FIRST	1

struct s_figure	*get_figure(t_ray ray, t_figures *figures, int first_or_closer);
void			set_values(struct s_figure *figure, float dist, t_ray ray);

#endif //MINIRT_GET_PIXEL_COLOR_H
